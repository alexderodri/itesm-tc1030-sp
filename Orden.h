#ifndef ORDEN_H
#define ORDEN_H
#include "Cliente.h"
#include "Sucursal.h"

class Orden {
    private:
        int id, length, *idProducto, *cantidadProducto;    // ID de orden, no. de productos distintos, arreglo
        float total;
        string formaPago;
        Empleado *empleado; // &
        Cliente  *cliente;  // &
        Sucursal *sucursal; // &
        bool isEmpleado, isCliente, isSucursal; // comprobar asignación
    public:
        Orden(int, string);
        Orden();
        void Imprimir();
        void DatosCliente();
        void CalcularTotal();
        void AgregarProducto(int, int);
        void BorrarProducto(int, int);
        void AsignarEmpleado(Empleado&);
        void AsignarCliente(Cliente&);
        void AsignarSucursal(Sucursal&);
        // getters
        int getLength() {return length;}
};
#endif