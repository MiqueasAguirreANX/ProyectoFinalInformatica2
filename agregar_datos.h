#pragma once

#include <QApplication>
#include <QPushButton>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QGridLayout>

#include "bd.h"

class BD;

class AgregarDatos : public QWidget {

    Q_OBJECT

    private:
        // Layouts
        QGridLayout *principal;
        QVBoxLayout *inputs;
        QVBoxLayout *view;
        QHBoxLayout *botones;

        // Tabla de datos
        QTableWidget *tablaArticulos;

        // Labels
        QLabel *lblId;
        QLabel *lblNombre;
        QLabel *lblCategoria;
        QLabel *lblProveedor;
        QLabel *lblPrecio;
        QLabel *lblCantidad;

        // Inputs
        QLineEdit *txtId;
        QLineEdit *txtNombre;
        QLineEdit *txtCategoria;
        QLineEdit *txtProveedor;
        QLineEdit *txtPrecio;
        QLineEdit *txtCantidad;

        //Botones
        QPushButton *btnAgregar;
        QPushButton *btnResetear;

        void Actualizar();

    public:
        BD *bd;
        AgregarDatos(QWidget *parent = 0);
        ~AgregarDatos();

    public slots:
        void Agregar();
        void Resetear();
        void Guardar();

    signals:
        void Borrado();
        void Vaciado();

};
