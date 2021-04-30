#include "Orden.h"
#include <iostream>
using namespace std;

Orden :: Orden(int id, string formaPago){
    this->id        = id;
    this->length    = 0;
    this->total     = 0;
    this->formaPago = formaPago;
}
Orden :: Orden(){
    this->id        = 0;
    this->length    = 0;
    this->total     = 0;
    this->formaPago = "efectivo";
}
void Orden :: Imprimir() {
    CalcularTotal();
    int *idInventario = sucursal->getIdProducto();
    int lengthInventario = sucursal->getLength();
    int idx;
    string nombreEmpleado = (*empleado).getNombre();
    string nombreCliente = (*cliente).getNombre();
    for (int i = 0; i < lengthInventario; i++) {
        if (idInventario[i] == id) {
            idx = i;
        }
    }
    cout << "Datos de la Orden no. " << id << ":" << endl
        << "    Total: " << total << " - Forma de pago: " << formaPago << endl
        << "    Empleado: " << nombreEmpleado << " - Cliente: " << nombreCliente << endl
        << "Productos:" << endl;
    for (int i = 0; i < length; i++) {
        cout << "    " << cantidadProducto[i] << " unidad(es) : ID " << idProducto[i] << " : " << sucursal->getNombre(idProducto[i]) << endl;
    }
}
void Orden :: DatosCliente() {
    cout << "Clientes de la Orden " << id << ":" << endl
        << "    "  << (*cliente).getNombre() << " (" << (*cliente).getRfc() << ")" << endl
        << "    " << (*cliente).getTel() << " - " << (*cliente).getDireccion() << " - " << (*cliente).getFechaN() << endl;
}
void Orden :: CalcularTotal(){
    this->total = 0;
    for (int i = 0; i < length;  i++) {
        this->total = this->total + (*sucursal).getPrecioV(idProducto[i]) * cantidadProducto[i];
    }
}
void Orden :: AgregarProducto(int id, int cantidad){
    bool isInInventory = false;
    bool isInOrder = false;
    bool isAvailable;
    int idxI, idxO, available;
    int *idInventario = sucursal->getIdProducto();
    int lengthInventario = sucursal->getLength();
    // comprobar si el producto existe en el inventario
    for (int i = 0; i < lengthInventario; i++) {
        if (idInventario[i] == id) {
            isInInventory = true;
            idxI = i;
            available = sucursal->getCantidadProducto()[idxI];
            isAvailable = available >= cantidad;
        }
    }
    // comprobar si el producto existe en la orden
    for (int i = 0; i < length; i++) {
        if (idProducto[i] == id) {
            isInOrder = true;
            idxO = i;
        }
    }
    // BORRAR
    // cout << "cantidad: " << cantidad << endl
    //     << "available: " << available << endl
    //     <<"isInInventory: " << isInInventory << endl
    //     << "isInOrder: " << isInOrder << endl
    //     << "isAvailable: " << isAvailable << endl
    //     << "idxI: " << idxI << endl
    //     << "idxO: " << idxO << endl
    //     << "length (orden): " << length << endl
    //     << "lengthInventario: " << lengthInventario << endl
    //     << "cantidadProducto (sucursal): " << sucursal->getCantidadProducto()[idxI] << endl;
    if (isInInventory && available > 0) {
        if (isInOrder) {
            // si hay existencia suficiente
            if (isAvailable) {
                cantidadProducto[idxO] = cantidadProducto[idxO] + cantidad;
                int remainder = available - cantidad;
                sucursal->EditarCantidad(id, remainder);
            // si existencia es menor a requerida
            } else {
                cantidadProducto[idxO] = cantidadProducto[idxO] + available;
                sucursal->EditarCantidad(id, 0);
                cout << "No hay " << cantidad << " ejemplares del producto con ID " << id << " en existencia. Se han agregado los " << available << " disponibles." << endl;
            }
        } else {
            int newLength = length + 1;
            int *tmpIdProducto = new int[newLength];
            int *tmpCantidadProducto = new int[newLength];
            // copy order inventory
            for (int i = 0; i < length; i++) {
                tmpIdProducto[i] = idProducto[i];
                tmpCantidadProducto[i] = cantidadProducto[i];
            }
            // si hay existencia suficiente
            if (isAvailable) {
                tmpIdProducto[length] = id;
                tmpCantidadProducto[length] = cantidad;
                int remainder = available - cantidad;
                sucursal->EditarCantidad(id, remainder);
            // si existencia es menor a requerida
            } else {
                tmpIdProducto[length] = id;
                tmpCantidadProducto[length] = available;
                sucursal->EditarCantidad(id, 0);
                cout << "No hay " << cantidad << " ejemplares del producto con ID " << id << " en existencia. Se han agregado los " << available << " disponibles." << endl;
            }
            idProducto = tmpIdProducto;
            cantidadProducto = tmpCantidadProducto;
            length = newLength;

            // // allocate memory
            // int *tmpIdProducto = new int[newLength];
            // int *tmpCantidadProducto = new int[newLength];
            // // copy
            // for (int i = 0; i < length; i++) {
            //     tmpIdProducto[i] = idProducto[i];
            //     tmpCantidadProducto[i] = cantidadProducto[i];
            // }
            // // new element
            // tmpIdProducto[length] = id;
            // tmpCantidadProducto[length] = cantidad;
            // // assign to self
            // idProducto = tmpIdProducto;
            // cantidadProducto = tmpCantidadProducto;
            // length = newLength;
        }
    } else {
        cout << "No hay existencia de un producto con ID " << id << " en el inventario. No se hicieron modificaciones." << endl;
    }
}
void Orden :: BorrarProducto(int id, int cantidad) {
    bool isInInventory      = false;
    bool isInOrder          = false;
    int idxO, idxI;
    int *idInventario       = sucursal->getIdProducto();
    int lengthInventario    = sucursal->getLength();
    // comprobar si el producto existe en el inventario
    for (int i = 0; i < lengthInventario; i++) {
        if (idInventario[i] == id) {
            isInInventory = true;
            idxI = i;
        }
    }
    // comprobar si el producto existe en la orden
    for (int i = 0; i < length; i++) {
        if (idProducto[i] == id) {
            isInOrder = true;
            idxO = i;
        }
    }
    if (isInOrder) {
        int cantidadInventario  = sucursal->getCantidadProducto()[idxI];
        // cout << "fnc: " << cantidad << endl;
        // cout << "inv: " << cantidadInventario << endl;
        int cantidadOrden       = cantidadProducto[idxO];
        // cout << "ord: " << cantidadOrden << endl;
        bool isGreater          = cantidadOrden > cantidad;
        bool isEqual            = cantidadOrden == cantidad;
        if (isGreater) {
            cantidadProducto[idxO] = cantidadProducto[idxO] - cantidad;
            cout << "Se ha(n) eliminado " << cantidad << " producto(s) con ID " << id << " de la orden." << endl;
        } else {
            if (isEqual) {
                cout << "Se ha(n) eliminado " << cantidad << " producto(s) con ID " << id << " de la orden." << endl;
            } else {
                cout << "No hay " << cantidad << " ejemplares del producto con ID " << id << " en la orden, solo " << cantidadOrden << ". Se ha eliminado el producto de la orden." << endl;
            }
            cantidad = cantidadOrden;
            int newLength = length - 1;
            // allocate memory
            int *tmpIdProducto = new int[newLength];
            int *tmpCantidadProducto = new int[newLength];
            // copy
            for (int i = 0; i < idxO; i++) {
                tmpIdProducto[i] = idProducto[i];
                tmpCantidadProducto[i] = cantidadProducto[i];
            }
            for (int i = idxO; i < newLength; i++) {
                tmpIdProducto[i] = idProducto[i + 1];
                tmpCantidadProducto[i] = cantidadProducto[i + 1];
            }
            idProducto = tmpIdProducto;
            cantidadProducto = tmpCantidadProducto;
            length = newLength;
        }
        if (isInInventory) {
            sucursal->EditarCantidad(id, cantidadInventario + cantidad);
        }
    } else {
        cout << "No existe un producto con ID " << id << " en la orden. No se hicieron modificaciones." << endl;
    }
}
void Orden :: AsignarEmpleado(Empleado &empleado) {
    int cargo = empleado.getCargo();
    bool isAllowed = (cargo == 1 || cargo == 2);
    if (isAllowed) {
        isEmpleado = true;
        this->empleado = &empleado;
    } else {
        cout << "El empleado " << empleado.getNombre() << " tiene cargo de " << empleado.getNombreCargo() << ". Solo empleados de logistica y venta pueden ser asignados a ordenes. No se hicieron modificaciones." << endl;
    }
}
void Orden :: AsignarCliente(Cliente &cliente) {
    isCliente = true;
    this->cliente = &cliente;
}
void Orden :: AsignarSucursal(Sucursal &sucursal){
    isSucursal = true;
    this->sucursal = &sucursal;
}