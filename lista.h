#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "articulo.h"

class Articulo;

class Nodo {
	public:
        Articulo *art;
		Nodo* sig;
		Nodo(Articulo *);
		Nodo();
		~Nodo();   // con alt + 126 se hace el simbolo de complemento a 1
};

class Lista {
    public:
        Nodo* inicio;
		Lista();
		~Lista();
		void Agregar(Nodo *);
		bool Buscar(int);
		Articulo* getArticuloByID(int);
		Articulo* getArticuloByIndex(int);
		void Eliminar(int);
		int Count();
		float Sum();
        float Promedio();
        float Varianza();
        float DesvioStd();
        float Mediana();
        float GananciaPorcentaje(float);
        float Neto(float);
        void EliminarIndex(int);
};
