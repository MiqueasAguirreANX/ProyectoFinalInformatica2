#pragma once

#define N 50
#include <string>

using namespace std;

class Articulo {

    private:

        int id;
        string nombre;
        string categoria;
        string proveedor;
        float precio;
        int cantidad;


    public:
        Articulo(int, string,string,string, float, int);
        int getID();
        string getNombre();
        string getCategoria();
        string getProveedor();
        float getPrecio();
        int getCantidad();
        float getTotal();
        void setNombre(string);
        void setCategoria(string);
        void setProveedor(string);
};
