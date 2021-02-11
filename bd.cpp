#include "lista.h"
#include "bd.h"
#include <stdio.h>
#include <stdlib.h>

#define N 50

#include <iostream>
#include <string>

using namespace std;

void BD::sacarDatos(){  // Guarda los datos del archivo en la lista
    fp = fopen("Articulos.txt", "r");
    if (!fp) {
        // Archivo no existe
        fclose(fp);
        return;
    }

    // Archivo existe
    // Algoritmo para extraer toda la lista de un archivo
    int _id, _cantidad;
    float _precio;

    char _nombre[N], _categoria[N], _proveedor[N];

    while ( feof(fp) == 0 ) {
        fscanf(fp, "%d\n", &_id );
        fscanf(fp , "%s\n", _nombre);
        fscanf(fp , "%s\n", _categoria);
        fscanf(fp , "%s\n", _proveedor);
        string _nombreStr(_nombre), _categoriaStr(_categoria), _proveedorStr(_proveedor);
        cout << _nombreStr << endl;
        cout << _categoriaStr << endl;
        cout << _proveedorStr << endl;

        fscanf(fp, "%f\n", &_precio );
        fscanf(fp, "%d\n", &_cantidad );
        lista->Agregar(new Nodo(new Articulo(_id, _nombreStr, _categoriaStr, _proveedorStr, _precio, _cantidad)));
    }

    fclose(fp);

}

void BD::guardarDatos(){    // Guarda los datos en el archivo
    fp = fopen("Articulos.txt", "w");
    printf("\nGuardando datos");
    Nodo *ptrn;
    ptrn = lista->inicio;
    char BUFFER[N];

    while (ptrn) {
        fprintf(fp, "%d\n", ptrn->art->getID());
        strcpy(BUFFER, ptrn->art->getNombre().c_str());
        cout << BUFFER << endl;
        fprintf(fp, "%s\n", BUFFER);
        strcpy(BUFFER, ptrn->art->getCategoria().c_str());
        cout << BUFFER << endl;
        fprintf(fp, "%s\n", BUFFER);
        strcpy(BUFFER, ptrn->art->getProveedor().c_str());
        cout << BUFFER << endl;
        fprintf(fp, "%s\n", BUFFER);
        fprintf(fp, "%f\n", ptrn->art->getPrecio());
        fprintf(fp, "%d\n", ptrn->art->getCantidad());

        ptrn = ptrn->sig;
    }
    fclose(fp);
}

BD::BD() {  // instancia la lista y le agrega los datos
    lista = new Lista();
    sacarDatos();
}

BD::~BD(){
    printf("\nBorrando base de datos");
    guardarDatos();
    delete lista;
}

Lista *BD::getLista() {
    return lista;
}

void BD::setLista(Lista *_lista) {
    lista = _lista;
}

void BD::BorrarDatos() {    // Borra todos los datos
    fp = fopen("Articulos.txt", "w");
    fclose(fp);
    delete lista;
    lista = new Lista;
}
