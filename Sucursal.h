#ifndef SUCURSAL_H
#define SUCURSAL_H
#include "Empleado.h"
#include "Inventario.h"
#include "Cliente.h"

class Inventario;
class Sucursal {
    private:
        int cantidadEmpleado, *idProducto, *cantidadProducto, length, cantidadCliente; // no. de empleados, codigo de producto, cantidad en existencia, cantidad de elementos en inventario, no. de clientes
        Inventario *inventario;         // puntero a inventario
        Empleado *empleado;             // arreglo de empleados
        Cliente *cliente;               // arreglo de clientes
        string atributoCliente[6] = {"nombre", "direccion", "tel", "fechaN", "sexo", "rfc"};
    public:
        Sucursal(Inventario&);
        Sucursal();
        void EditarCantidad(int, int);
        void AgregarCliente(Cliente);
        void ModificarCliente(string, string, string);
        void BorrarCliente(string);
        void AgregarEmpleado(Empleado);
        void BorrarEmpleado(int);
        void TransferirEmpleado(int, Sucursal&);
        // setters
        void setIdProducto(int *idProducto)             {this->idProducto       = idProducto;}
        void setCantidadProducto(int *cantidadProducto) {this->cantidadProducto = cantidadProducto;}
        void setLength(int length)                      {this->length           = length;}
        void setNewCodigo(int, int);
        // getters
        int *getIdProducto()        {return idProducto;}
        int *getCantidadProducto()  {return cantidadProducto;}
        int getLength()             {return length;}
        float getPrecioV(int);
        string getNombre(int);

        // BORRAR
        void MostrarEmpleados();
        void MostrarClientes();
        void MostrarInventario();
};
#endif