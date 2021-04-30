#include "Empleado.h"
#include <iostream>
using namespace std;

Empleado :: Empleado(string nombre, string direccion, string tel, string fechaN, string sexo, int cargo) : Persona(nombre, direccion, tel, fechaN, sexo) {
    this->cargo = cargo;
}

Empleado :: Empleado() {
    this->cargo = 0;
}