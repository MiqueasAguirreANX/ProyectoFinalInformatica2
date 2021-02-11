#pragma once

#include "lista.h"

class Lista;

class BD {

    private:
        Lista *lista;
        FILE *fp;

    public:
        BD();
        ~BD();
        Lista *getLista();
        void setLista(Lista *);
        void guardarDatos();
        void sacarDatos();
        void BorrarDatos();

};
