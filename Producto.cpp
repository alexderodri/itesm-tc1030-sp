#include "Producto.h"
#include <iostream>
using namespace std;

Producto :: Producto(int codigo, string nombre, float precioC, float precioV, float peso, float alto, float ancho, float largo) {
    this->codigo    = codigo;
    this->nombre    = nombre;
    this->precioC   = precioC;
    this->precioV   = precioV;
    this->peso      = peso;
    this->alto      = alto;
    this->ancho     = ancho;
    this->largo     = largo;
}
Producto :: Producto() {
    this->codigo    = 0;
    this->nombre    = "N/A";
    this->precioC   = 0;
    this->precioV   = 0;
    this->peso      = 0;
    this->alto      = 0;
    this->ancho     = 0;
    this->largo     = 0;
}