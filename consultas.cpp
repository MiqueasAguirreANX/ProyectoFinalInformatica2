#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QLineEdit>

#include "consultas.h"
#include "bd.h"
#include <string>

using namespace std;

class BD;

Consultas::Consultas (QWidget *parent): QWidget(parent) {

    bd = new BD();

    setGeometry( 350, 100, 480, 480);
    setFixedSize(480,480);

    // Layouts
    vent = new QGridLayout;

    // Labels
    lblId           = new QLabel("Buscar por ID: ", this);
    lblIndex        = new QLabel("Buscar por indice: ", this);
    lblEncontrado   = new QLabel(this);
    resId           = new QLabel(this);
    resNombre       = new QLabel(this);
    resCategoria    = new QLabel(this);
    resProveedor    = new QLabel(this);
    resPrecio       = new QLabel(this);
    resCantidad     = new QLabel(this);

    // TextEdits
    txtId = new QLineEdit(this);
    txtIndex = new QLineEdit(this);


    // Connectar
    btnBuscarId = new QPushButton("Buscar", this);
    btnBuscarIndex = new QPushButton("Buscar", this);
    btnBorrarId = new QPushButton("Borrar", this);
    btnBorrarIndex = new QPushButton("Borrar", this);
    connect(btnBuscarId, SIGNAL(clicked()),this,SLOT(ConsBuscarId()));
    connect(btnBuscarIndex, SIGNAL(clicked()),this,SLOT(ConsBuscarIndex()));
    connect(btnBorrarId, SIGNAL(clicked()),this,SLOT(BorrarPorID()));
    connect(btnBorrarIndex, SIGNAL(clicked()),this,SLOT(BorrarPorIndex()));

    // Agregar Widgets --

        vent->addWidget(lblId, 0, 0);
        vent->addWidget(txtId, 0, 1);
        vent->addWidget(btnBuscarId, 0, 2);
        vent->addWidget(btnBorrarId, 0, 3);
        vent->addWidget(lblIndex, 1, 0);
        vent->addWidget(txtIndex, 1, 1);
        vent->addWidget(btnBuscarIndex, 1, 2);
        vent->addWidget(btnBorrarIndex, 1, 3);

        vent->addWidget(lblEncontrado, 2, 0, 1, 4);
        vent->addWidget(resId, 3, 0, 1, 4);
        vent->addWidget(resNombre, 4, 0, 1, 4);
        vent->addWidget(resCategoria, 5, 0, 1, 4);
        vent->addWidget(resProveedor, 6, 0, 1, 4);
        vent->addWidget(resPrecio, 7, 0, 1, 4);
        vent->addWidget(resCantidad, 8, 0, 1, 4);

    // ------------------

    setLayout(vent);

}

void Consultas::ConsBuscarId() {    // Buscar por ID
    bool flag;
    int _id = txtId->text().toInt(&flag);

    if (flag) {
        if (bd->getLista()->Buscar(_id)){   // Seteo todos los labels si se encontro
            lblEncontrado->setText("Se ha encontrado el articulo");
            QString StrNombre(bd->getLista()->getArticuloByID(_id)->getNombre().c_str());
            QString StrCat(bd->getLista()->getArticuloByID(_id)->getCategoria().c_str());
            QString StrPro(bd->getLista()->getArticuloByID(_id)->getProveedor().c_str());
            resId->setText(txtId->text());
            resNombre->setText(StrNombre);
            resCategoria->setText(StrCat);
            resProveedor->setText(StrPro);
            QString _pre, cant;
            _pre.setNum(bd->getLista()->getArticuloByID(_id)->getPrecio());
            resPrecio->setText(_pre);
            cant.setNum(bd->getLista()->getArticuloByID(_id)->getCantidad());
            resCantidad->setText(cant);
        }
        else {      // Seteo todos los labels si no se encontro
            lblEncontrado->setText("No se ha encontrado el articulo");
            resId->setText("");
            resNombre->setText("");
            resCategoria->setText("");
            resProveedor->setText("");
            resPrecio->setText("");
            resCantidad->setText("");
        }

    }
}

void Consultas::ConsBuscarIndex(){  // Busqueda por indice
    bool flag;
    int index = txtIndex->text().toInt(&flag);

    if (flag) {
        if (bd->getLista()->getArticuloByIndex(index)) {
            lblEncontrado->setText("Se ha encontrado el articulo");
            QString StrNombre(bd->getLista()->getArticuloByIndex(index)->getNombre().c_str());
            QString StrCat(bd->getLista()->getArticuloByIndex(index)->getCategoria().c_str());
            QString StrPro(bd->getLista()->getArticuloByIndex(index)->getProveedor().c_str());
            resId->setText(txtIndex->text());
            resNombre->setText(StrNombre);
            resCategoria->setText(StrCat);
            resProveedor->setText(StrPro);
            QString _pre, cant;
            _pre.setNum(bd->getLista()->getArticuloByIndex(index)->getPrecio());
            resPrecio->setText(_pre);
            cant.setNum(bd->getLista()->getArticuloByIndex(index)->getCantidad());
            resCantidad->setText(cant);
        }
        else {
            lblEncontrado->setText("No se ha encontrado el articulo");
            resId->setText("");
            resNombre->setText("");
            resCategoria->setText("");
            resProveedor->setText("");
            resPrecio->setText("");
            resCantidad->setText("");
        }

    }
}

void Consultas::BorrarPorID() {
    bool flag;
    int id = txtId->text().toInt(&flag);

    if (flag)
        bd->getLista()->Eliminar(id);
}

void Consultas::BorrarPorIndex() {
    bool flag;
    int index = txtId->text().toInt(&flag);

    if (flag && (index <= bd->getLista()->Count()) && index > 0)
        bd->getLista()->EliminarIndex(index);
}

