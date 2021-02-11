#include <QApplication>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QLineEdit>

#include <string.h>
#include "agregar_datos.h"
#include "bd.h"
#include "lista.h"
#include "articulo.h"
#include <iostream>
#include <string>

#define N 50

class BD;
class Nodo;
class Lista;
class Articulo;

using namespace std;

AgregarDatos::AgregarDatos(QWidget *parent) : QWidget(parent) {

    bd = new BD();

    setGeometry( 350, 100, 880, 480);
    setFixedSize(880,480);

    // Inicializacion
    principal = new QGridLayout;
    inputs = new QVBoxLayout;
    view = new QVBoxLayout;
    botones = new QHBoxLayout;

    // Tabla de datos
    tablaArticulos = new QTableWidget(this);
    tablaArticulos->setColumnCount(6);


    lblId = new QLabel(this);
    QString strId = "ID";
    lblId->setText(strId);
    lblNombre = new QLabel(this);
    QString strNombre = "Nombre";
    lblNombre->setText(strNombre);
    lblCategoria = new QLabel(this);
    QString strCat = "Categoria";
    lblCategoria->setText(strCat);
    lblProveedor = new QLabel(this);
    QString strProv = "Provedor";
    lblProveedor->setText(strProv);
    lblPrecio = new QLabel(this);
    QString strPrecio = "Precio";
    lblPrecio->setText(strPrecio);
    lblCantidad = new QLabel(this);
    QString strCant = "Cantidad";
    lblCantidad->setText(strCant);

    // Inputs
    txtId = new QLineEdit(this);
    txtNombre = new QLineEdit(this);
    txtCategoria = new QLineEdit(this);
    txtProveedor = new QLineEdit(this);
    txtPrecio = new QLineEdit(this);
    txtCantidad = new QLineEdit(this);

    //Botones
    btnAgregar = new QPushButton("Agregar", this);
    connect(btnAgregar, SIGNAL(clicked()), this, SLOT(Agregar()));
    btnResetear = new QPushButton("Resetear", this);
    connect(btnResetear, SIGNAL(clicked()), this, SLOT(Resetear()));



    // Agrego los widgets a los layouts

    botones->addWidget(btnAgregar);
    botones->addWidget(btnResetear);

    inputs->addWidget(lblId);
    inputs->addWidget(txtId);
    inputs->addWidget(lblNombre);
    inputs->addWidget(txtNombre);
    inputs->addWidget(lblCategoria);
    inputs->addWidget(txtCategoria);
    inputs->addWidget(lblProveedor);
    inputs->addWidget(txtProveedor);
    inputs->addWidget(lblPrecio);
    inputs->addWidget(txtPrecio);
    inputs->addWidget(lblCantidad);
    inputs->addWidget(txtCantidad);
    inputs->addLayout(botones);

    // Boton para forzar el guardado
    QPushButton *btnGuardar = new QPushButton("Guardar", this);
    connect(btnGuardar, SIGNAL(clicked()), this, SLOT(Guardar()));
    inputs->addWidget(btnGuardar);

    view->addWidget(tablaArticulos);

    principal->addLayout(inputs, 0, 0, 1, 1);
    principal->addLayout(view, 0, 1, 1, 1);
    principal->setColumnMinimumWidth(1, 620);

    connect(this, SIGNAL(Borrado()), tablaArticulos, SLOT(clearContents()));
    connect(this, SIGNAL(Vaciado()), txtId, SLOT(clear()));
    connect(this, SIGNAL(Vaciado()), txtNombre, SLOT(clear()));
    connect(this, SIGNAL(Vaciado()), txtCategoria, SLOT(clear()));
    connect(this, SIGNAL(Vaciado()), txtProveedor, SLOT(clear()));
    connect(this, SIGNAL(Vaciado()), txtPrecio, SLOT(clear()));
    connect(this, SIGNAL(Vaciado()), txtCantidad, SLOT(clear()));
    connect(this, SIGNAL(Vaciado()), txtCantidad, SLOT(setFocus()));

    Actualizar();

    setLayout(principal);

}

void AgregarDatos::Guardar() { // Fuerza el guardado de los datos
    delete bd;
    bd = new BD();
}

void AgregarDatos::Agregar(){ // Obtiene y valida los datos y luego los agrega


    bool flag1, flag2, flag3;
    QString _nombre(txtNombre->text()), _categoria(txtCategoria->text()), _proveedor(txtProveedor->text());
    int _id = txtId->text().toInt(&flag1),  _cantidad = txtCantidad->text().toInt(&flag3);
    float _precio = txtPrecio->text().toFloat(&flag2);
    string v1 = "", v2 = "", v3 = "";

    v1 += _nombre.toStdString();
    v2 += _categoria.toStdString();
    v3 += _proveedor.toStdString();

    if (flag1 && flag2 && flag3) // Las conversiones deben ser validas
    if (!(bd->getLista()->Buscar(_id))) // No se pueden ids repetidos
    if (!(v1.empty()) && !(v2.empty()) && !(v3.empty())) // No dejar vacios
        bd->getLista()->Agregar(new Nodo(new Articulo(_id, v1, v2, v3, _precio, _cantidad)));

    emit Vaciado(); // Emite una señal para vaciar los inputs

    Actualizar();   // Actualiza la tabla
}

AgregarDatos::~AgregarDatos() {
    printf("\nBorrando base de datos");
    delete bd;
}

void AgregarDatos::Resetear() {

    // Resetear datos
    bd->BorrarDatos();
    Actualizar();
}

void AgregarDatos::Actualizar() { // Actualiza la tabla

    printf("\nActualizando la tabla");

    emit Borrado(); // emito la señal de borrar toda la tabla para luego actualizarla
    tablaArticulos->setRowCount(bd->getLista()->Count());

    Nodo *nodoPtr;
    nodoPtr = bd->getLista()->inicio;

    int i = 0;

    while (nodoPtr) {   // Por cada item en la lista, lo agrega a la tabla

        QTableWidgetItem *_id = new QTableWidgetItem();
        QString _strId;
        _strId.setNum(nodoPtr->art->getID());
        _id->setText(_strId);
        tablaArticulos->setItem(i, 0, _id);

        QTableWidgetItem *_nombre = new QTableWidgetItem();
        QString _strNombre(nodoPtr->art->getNombre().c_str());
        _nombre->setText(_strNombre);
        tablaArticulos->setItem(i, 1, _nombre);

        QTableWidgetItem *_categoria = new QTableWidgetItem();
        QString _strCategoria(nodoPtr->art->getCategoria().c_str());
        _categoria->setText(_strCategoria);
        tablaArticulos->setItem(i, 2, _categoria);

        QTableWidgetItem *_proveedor = new QTableWidgetItem();
        QString _strProv(nodoPtr->art->getProveedor().c_str());
        _proveedor->setText(_strProv);
        tablaArticulos->setItem(i, 3, _proveedor);

        QTableWidgetItem *_precio = new QTableWidgetItem();
        QString _strPrecio;
        _strPrecio.setNum(nodoPtr->art->getPrecio());
        _precio->setText(_strPrecio);
        tablaArticulos->setItem(i, 4, _precio);

        QTableWidgetItem *_cantidad = new QTableWidgetItem();
        QString _strCant;
        _strCant.setNum(nodoPtr->art->getCantidad());
        _cantidad->setText(_strCant);
        tablaArticulos->setItem(i, 5, _cantidad);


        i++;
        nodoPtr = nodoPtr->sig;
    }

}
