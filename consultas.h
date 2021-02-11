#pragma once

#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QLineEdit>

#include "bd.h"

class BD;


class Consultas : public QWidget {

    Q_OBJECT

    private:
        QGridLayout *vent;
        QPushButton *btnBuscarId;
        QPushButton *btnBuscarIndex;
        QPushButton *btnBorrarId;
        QPushButton *btnBorrarIndex;
        QLabel *lblId;
        QLineEdit *txtId;
        QLabel *lblIndex;
        QLineEdit *txtIndex;
        // -----------
        QLabel *lblEncontrado;
        QLabel *resId;
        QLabel *resNombre;
        QLabel *resCategoria;
        QLabel *resProveedor;
        QLabel *resPrecio;
        QLabel *resCantidad;
        // -----------
        BD *bd;

    public:
        Consultas(QWidget *parent = 0);

    public slots:
        void ConsBuscarId();
        void ConsBuscarIndex();
        void BorrarPorID();
        void BorrarPorIndex();

};
