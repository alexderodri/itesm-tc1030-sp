#ifndef INVENTARIO_H
#define INVENTARIO_H
#include "Producto.h"
#include "Sucursal.h"

class Sucursal;
class Inventario {
    private:
        // Producto *producto = new Producto[128];
        // Sucursal **sucursal = new Sucursal*[128];
        Producto *producto;
        Sucursal **sucursal;
        int *id, length, cantidadSucursal;
        string atributo[8] = {"codigo", "nombre", "precioC", "precioV", "peso", "alto", "ancho", "largo"};
    public:
        Inventario();
        void Agregar(Producto);                 // agrega el producto
        void Modificar(int, string, string);    // modificar atributo de texto de producto con codigo correspondiente
        void Modificar(int, string, float);     // modificar atributo numerico de producto con codigo correspondiente
        void Borrar(int);                       // borra el producto con el codigo correspondiente
        void AgregarSucursal(Sucursal&);        // para almacenar
        // getters
        int getLength() {return length;}
        int *getId() {return id;}
        float getPrecioV(int);
        string getNombre(int);

        // BORRAR
        void Imprimir();
};
#endif