#include <stdio.h>
#include <string.h>
#include "articulo.h"
#include <string>

#define N 50

#include <iostream>

using namespace std;

// Clase articulo
Articulo::Articulo (int _id, string  _nombre, string _categoria, string _proveedor, float _precio, int _cantidad){
    id = _id;
    nombre = _nombre;
    categoria = _categoria;
    proveedor = _proveedor;
    precio = _precio;
    cantidad = _cantidad;
}

int Articulo::getID() {
    return id;
}

string Articulo::getNombre() {
    return nombre;
}

string Articulo::getCategoria(){
    return categoria;
}

string Articulo::getProveedor(){
    return proveedor;
}

float Articulo::getPrecio() {
    return precio;
}

int Articulo::getCantidad() {
    return cantidad;
}

float Articulo::getTotal(){
    return (float)cantidad*precio;
}
