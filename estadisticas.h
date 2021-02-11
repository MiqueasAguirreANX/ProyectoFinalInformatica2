#pragma once

#include <QApplication>
#include <QLabel>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>

#include "bd.h"
#include "lista.h"

/*

Estadisticas a considerar:
Total
Cantidad total
Media
Mediana
Varianza
Desvio std
Neto
Ganancia


*/

class Lista;
class BD;

class Estadisticas : public QWidget {

    Q_OBJECT

    private:
        QGridLayout *mainW;
        QVBoxLayout *stackW;
        QLabel *lblTotal;
        QLabel *verTotal;
        QLabel *lblCantidad;
        QLabel *verCantidad;
        QLabel *lblMedia;
        QLabel *verMedia;
        QLabel *lblMediana;
        QLabel *verMediana;
        QLabel *lblGanancia;
        QLabel *verGanancia;
        QLabel *lblNeto;
        QLabel *verNeto;
        QLabel *lblVarianza;
        QLabel *verVarianza;
        QLabel *lblDesvioStd;
        QLabel *verDesvioStd;
        QLineEdit *txtPorcentajeG;
        QLineEdit *txtPorcentajeN;
        QPushButton *calcG;
        QPushButton *calcN;
        QPushButton *btnImprimirTXT;
        QPushButton *btnImprimirCSV;
        void Actualizar();
        BD *bd;
        FILE *fp;

    public:

        Estadisticas(QWidget *parent = 0);


    public slots:
        void ImprimirTXT();
        void ImprimirCSV();
        void calcularN();
        void calcularG();
};
