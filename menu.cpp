#include <QApplication>
#include <QPushButton>
#include "menu.h"
#include "agregar_datos.h"
#include "consultas.h"
#include "estadisticas.h"

#define ANCHO 130
#define ALTO 50
#define SPACE 10
#define ESPX 60

Menu::Menu (QWidget *parent): QWidget(parent) {

    setGeometry( 100, 100, 250, 200);
    setFixedSize(250, 200);
    btnAgregarDatos = new QPushButton("Agregar datos",this);
    btnAgregarDatos->setGeometry(ESPX, SPACE, ANCHO, ALTO);
    btnEstadisticas = new QPushButton("Estadisticas",this);
    btnEstadisticas->setGeometry(ESPX, SPACE + ALTO + SPACE, ANCHO, ALTO);
    btnConsultas = new QPushButton("Consultas",this);
    btnConsultas->setGeometry(ESPX, SPACE + ALTO + SPACE + ALTO +SPACE, ANCHO, ALTO);

    agregarDatos = NULL;
    estadisticas = NULL;
    consultas = NULL;

    connect(btnAgregarDatos, SIGNAL(clicked()), this, SLOT(MostrarAgregarDatos()));
    connect(btnEstadisticas, SIGNAL(clicked()), this, SLOT(MostrarEstadisticas()));
    connect(btnConsultas, SIGNAL(clicked()), this, SLOT(MostrarConsultas()));


    show();
}

void Menu::MostrarAgregarDatos(){
    if (!agregarDatos) {
        agregarDatos = new AgregarDatos();
    }
    agregarDatos->show();
    connect(btnAgregarDatos, SIGNAL(clicked()), this, SLOT(EsconderAgregarDatos()));
}

void Menu::MostrarEstadisticas() {
    if (!estadisticas){
        estadisticas = new Estadisticas();
    }
    estadisticas->show();
    connect(btnEstadisticas, SIGNAL(clicked()), this, SLOT(EsconderEstadisticas()));
}

void Menu::MostrarConsultas() {
    if (!consultas){
        consultas = new Consultas();
    }
    consultas->show();
    connect(btnConsultas, SIGNAL(clicked()), this, SLOT(EsconderConsultas()));
}

void Menu::EsconderConsultas(){
    consultas->close();
    connect(btnConsultas, SIGNAL(clicked()), this, SLOT(MostrarConsultas()));
}

void Menu::EsconderAgregarDatos(){
    agregarDatos->close();
    connect(btnAgregarDatos, SIGNAL(clicked()), this, SLOT(MostrarAgregarDatos()));
}

void Menu::EsconderEstadisticas(){
    estadisticas->close();
    connect(btnEstadisticas, SIGNAL(clicked()), this, SLOT(MostrarEstadisticas()));
}
