#include <QApplication>
#include <QLabel>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>

#include "estadisticas.h"


Estadisticas::Estadisticas (QWidget *parent): QWidget(parent) {
    //Inicializo la base de datos
    bd = new BD();

    setGeometry( 350, 100, 580, 480);
    setFixedSize(580,480);

    // Layouts
    mainW    = new QGridLayout;
    stackW   = new QVBoxLayout;

    // Titulo
    QLabel *title = new QLabel("ESTADISTICAS", this);

    // Labels
    lblTotal     = new QLabel("Total", this);
    verTotal     = new QLabel(this);
    lblCantidad  = new QLabel("Cantidad", this);
    verCantidad  = new QLabel(this);
    lblMedia     = new QLabel("Media", this);
    verMedia     = new QLabel("Muestro la media",this);
    lblMediana   = new QLabel("Mediana", this);
    verMediana   = new QLabel(this);
    lblVarianza  = new QLabel("Varianza", this);
    verVarianza  = new QLabel(this);
    lblDesvioStd = new QLabel("Desvio Std", this);
    verDesvioStd = new QLabel(this);
    lblGanancia  = new QLabel("Ganancia %", this);
    verGanancia  = new QLabel(this);
    lblNeto      = new QLabel("Neto %", this);
    verNeto      = new QLabel(this);

    // TextEdits
    txtPorcentajeG = new QLineEdit(this);
    txtPorcentajeN = new QLineEdit(this);

    // Buttons
    btnImprimirTXT = new QPushButton("Imprimir estadisticas", this);
    btnImprimirCSV = new QPushButton("Imprimir datos en csv", this);
    calcG = new QPushButton("Calcular", this);
    calcN = new QPushButton("Calcular", this);

    // Conectar
    connect(btnImprimirCSV, SIGNAL(clicked()), this, SLOT(ImprimirCSV()));
    connect(btnImprimirTXT, SIGNAL(clicked()), this, SLOT(ImprimirTXT()));
    connect(calcG, SIGNAL(clicked()), this, SLOT(calcularG()));
    connect(calcN, SIGNAL(clicked()), this, SLOT(calcularN()));

    // Add Layouts
    mainW->addWidget(title, 0,0,1,4);
    mainW->addWidget(lblTotal, 2, 0, 1, 1);
    mainW->addWidget(verTotal, 2, 1,1,3);
    mainW->addWidget(lblCantidad, 3, 0, 1, 1);
    mainW->addWidget(verCantidad, 3, 1,1,3);
    mainW->addWidget(lblMedia, 4, 0, 1, 1);
    mainW->addWidget(verMedia, 4, 1,1,3);
    mainW->addWidget(lblMediana, 5, 0, 1, 1);
    mainW->addWidget(verMediana, 5, 1,1,3);
    mainW->addWidget(lblVarianza, 6, 0, 1, 1);
    mainW->addWidget(verVarianza, 6, 1,1,3);
    mainW->addWidget(lblDesvioStd, 7, 0, 1, 1);
    mainW->addWidget(verDesvioStd, 7, 1,1,3);
    mainW->addWidget(lblGanancia, 8, 0, 1, 1);
    mainW->addWidget(txtPorcentajeG, 8, 1, 1,1);
    mainW->addWidget(calcG, 8, 2, 1,1);
    mainW->addWidget(verGanancia, 8, 3,1,1);
    mainW->addWidget(lblNeto, 9, 0, 1, 1);
    mainW->addWidget(txtPorcentajeN, 9, 1,1,1);
    mainW->addWidget(calcN, 9, 2, 1,1);
    mainW->addWidget(verNeto, 9, 3,1,1);

    stackW->addWidget(btnImprimirTXT);
    stackW->addWidget(btnImprimirCSV);

    mainW->addLayout(stackW, 10, 0, 1, 4);

    Actualizar();

    setLayout(mainW);


}

void Estadisticas::Actualizar() {
    //reinicio las estadisticas
    QString Stotal, Scantidad, Smedia, Smediana, Svarianza, Sdesvio;
    int cantidad;
    float total, media, mediana, varianza, desvio;

    total = bd->getLista()->Sum();
    Stotal.setNum(total);
    verTotal->setText(Stotal);

    cantidad = bd->getLista()->Count();
    Scantidad.setNum(cantidad);
    verCantidad->setText(Scantidad);

    media = bd->getLista()->Promedio();
    Smedia.setNum(media);
    verMedia->setText(Smedia);

    mediana = bd->getLista()->Mediana();
    Smediana.setNum(mediana);
    verMediana->setText(Smediana);

    varianza = bd->getLista()->Varianza();
    Svarianza.setNum(varianza);
    verVarianza->setText(Svarianza);

    desvio = bd->getLista()->DesvioStd();
    Sdesvio.setNum(desvio);
    verDesvioStd->setText(Sdesvio);
}

void Estadisticas::ImprimirTXT() {
    // Manejar la impresion en un txt de toda las estadisticas

    fp = fopen("Estadisticas.txt", "w");

    fprintf(fp, "\t\tEstadisticas\n");
    fprintf(fp, "\tTotal:          %20.4f\n", bd->getLista()->Sum());
    fprintf(fp, "\tCantidad:       %20d\n", bd->getLista()->Count());
    fprintf(fp, "\tMedia:          %20.4f\n", bd->getLista()->Promedio());
    fprintf(fp, "\tMediana:        %20.4f\n", bd->getLista()->Mediana());
    fprintf(fp, "\tVarianza:       %20.4f\n", bd->getLista()->Varianza());
    fprintf(fp, "\tDesvio standar: %20.4f\n", bd->getLista()->DesvioStd());
    fclose(fp);
}

void Estadisticas::ImprimirCSV() {
    // Poner todos los datos en un csv creado por mi

    fp = fopen("Articulos.csv", "w");
    printf("\nGuardando datos");
    Nodo *ptrn;
    ptrn = bd->getLista()->inicio;
    char BUFFER[N];

    while (ptrn) {
        fprintf(fp, "%d,%s,%s,%s,%.4f,%d\n", ptrn->art->getID(),ptrn->art->getNombre().c_str(), ptrn->art->getCategoria().c_str(), ptrn->art->getProveedor().c_str(),ptrn->art->getPrecio(), ptrn->art->getCantidad());
        ptrn = ptrn->sig;
    }
    fclose(fp);

}
void Estadisticas::calcularG() {
    //Calcular ganancia
    bool flag1;
    float porc = txtPorcentajeG->text().toFloat(&flag1);
    QString resStr;

    if (flag1){
        float res = bd->getLista()->GananciaPorcentaje(porc);
        resStr.setNum(res);
        verGanancia->setText(resStr);
    }
}


void Estadisticas::calcularN() {

    //Calcular neto
    bool flag1;
    float porc = txtPorcentajeN->text().toFloat(&flag1);
    QString resStr;

    if (flag1){
        float res = bd->getLista()->Neto(porc);
        resStr.setNum(res);
        verNeto->setText(resStr);
    }
}
