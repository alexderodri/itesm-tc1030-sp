#include "Persona.h"
using namespace std;

Persona :: Persona(string nombre, string direccion, string tel, string fechaN, string sexo) {
    this->nombre    = nombre;
    this->direccion = direccion;
    this->tel       = tel;
    this->fechaN    = fechaN;
    this->sexo      = sexo;
}
Persona :: Persona() {}