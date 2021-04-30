#include "Cliente.h"
using namespace std;

Cliente :: Cliente(string nombre, string direccion, string tel, string fechaN, string sexo, string rfc) : Persona(nombre, direccion, tel, fechaN, sexo) {
    this->rfc = rfc;
}
Cliente :: Cliente() {}