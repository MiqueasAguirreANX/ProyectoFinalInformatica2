#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "articulo.h"
#include "lista.h"
#include <math.h>

class Articulo;

Nodo::Nodo(Articulo *_art) {
    sig = NULL;
    art = _art;
}

Nodo::Nodo(){
    sig = NULL;
}

Nodo::~Nodo(){
    delete art;
    sig = NULL;
}


Lista::Lista(){
    inicio = NULL;
}

Lista::~Lista() {
    Nodo* ant, *dsp;
    ant = inicio;
    dsp = inicio;
    printf("\nBorrando lista");

	inicio = NULL;

	while(dsp){
		ant=dsp;
		dsp=dsp->sig;
		delete ant;
	}
}

// Agrego un nodo al principio
void Lista::Agregar(Nodo* pn){
	pn->sig = inicio;
	inicio = pn;
}

// Obtengo articulo por id
Articulo* Lista::getArticuloByID(int _id){
    if (!Buscar(_id)){
        return NULL;
    }
    else {
        Nodo *pa;
        pa = inicio;
        while(pa){
            if ( (pa->art->getID()) == _id ) return pa->art;
            pa = pa->sig;
        }
    }
}

// Busco un articulo por id y devuelvo un bool
bool Lista::Buscar(int _id) {
    Nodo *pa;
    pa = inicio;
    while(pa){
        if ((pa->art->getID()) == _id ) return true;
        pa = pa->sig;
    }
    return false;
}

// Elimino un articulo por id
void Lista::Eliminar(int _id) {
    Nodo *antes, *mid, *desp;
    antes = inicio;
    mid = inicio;
    desp = inicio;
    int cont = 1;
    while(mid){
        if ((mid->art->getID()) == _id) {
            if (cont == 1) {
                inicio = mid->sig;
                delete mid;
                return;
            }
            if (cont > 1 || cont < Count()) {
                antes->sig = desp;
                delete mid;
            }
            if (cont == Count()) {
                delete desp;
                delete mid;
                antes->sig = NULL;
            }
        }
        antes = mid;
        mid = mid->sig;
        desp = mid->sig;
        cont++;
    }
}

void Lista::EliminarIndex(int _index) {
    Nodo *antes, *mid, *desp;
    antes = inicio;
    mid = inicio;
    desp = inicio;
    int cont = 1;
    while(mid){
        if (cont == _index) {
            if (cont == 1) {
                inicio = mid->sig;
                delete mid;
                return;
            }
            if (cont > 1 || cont < Count()) {
                antes->sig = desp;
                delete mid;
            }
            if (cont == Count()) {
                delete desp;
                delete mid;
                antes->sig = NULL;
            }
        }
        antes = mid;
        mid = mid->sig;
        desp = mid->sig;
        cont++;
    }
}

int Lista::Count() {
    int cont = 0;
    Nodo *pNodo;
    pNodo = inicio;

    while (pNodo) {
        cont++;
        pNodo = pNodo->sig;
    }
    return cont;
}

float Lista::Sum(){
    float suma = 0;
    Nodo *pNodo;
    pNodo = inicio;

    while (pNodo) {
        suma += (pNodo->art->getTotal());
        pNodo = pNodo->sig;
    }
    return suma;
}

float Lista::Promedio() {
    int cont = Count();
    float suma = Sum();

    if (!cont) return 0;
    else return (suma/cont);
}

float Lista::Varianza() {
    float sumador = 0;
    Nodo *pNodo;
    pNodo = inicio;

    while (pNodo) {
        sumador += ((pNodo->art->getTotal() - Promedio())*(pNodo->art->getTotal() - Promedio()));
        pNodo = pNodo->sig;
    }
    if (Count() > 0)
        return sumador/Count();
    else return 0;

}

float Lista::DesvioStd() {
    return sqrt(Varianza());
}

Articulo *Lista::getArticuloByIndex(int index) {

    if (!Count()) return NULL;
    if (index > Count()) return NULL;

    int cont = 0;

    Nodo *pNodo;
    pNodo = inicio;

    while (pNodo) {
        cont++;
        if (cont == index) return pNodo->art;
        pNodo = pNodo->sig;
    }
}

float Lista::Mediana() {

    if (Count() == 0) return 0;

    if (Count() % 2) return getArticuloByIndex((Count()+1)/2)->getTotal();
    else return (getArticuloByIndex(Count()/2)->getTotal() + getArticuloByIndex((Count()/2)+1)->getTotal())/2;

}

float Lista::GananciaPorcentaje(float porc) {
    return Sum()*(1.0+(porc/100));
}

float Lista::Neto(float porc = 0) {
    return GananciaPorcentaje(porc) - Sum();
}

