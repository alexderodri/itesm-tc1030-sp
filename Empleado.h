#ifndef EMPLEADO_H
#define EMPLEADO_H
#include "Persona.h"

class Empleado : public Persona {
    private:
        int cargo;
        string nombreCargo[5] = {"sin asignar", "logistica", "ventas", "administracion", "gerencia"};
    public:
        Empleado(string, string, string, string ,string, int);
        Empleado();
        // getters
        int getCargo()          {return cargo;}
        string getNombreCargo() {return nombreCargo[cargo];}
};
#endif