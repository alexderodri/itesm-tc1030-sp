#include "Sucursal.h"
#include <iostream>
using namespace std;

Sucursal :: Sucursal(Inventario &inventario) {
    this->cantidadEmpleado  = 0;
    this->inventario        = &inventario;
    this->length            = inventario.getLength();
    this->cantidadCliente   = 0;
    if (length > 0) {
        this->idProducto        = inventario.getId();
        this->cantidadProducto  = new int[this->length];
        for (int i = 0; i < this->length; i++) {
            cantidadProducto[i] = 0;
        }
    }
    inventario.AgregarSucursal(*this);
}
Sucursal :: Sucursal() {
    this->cantidadEmpleado  = 0;
    this->length            = 0;
    this-> cantidadCliente  = 0;
}
void Sucursal :: EditarCantidad(int id, int cantidad) {
    bool isContained = false;
    int idx;
    // int length = inventario->getLength();

    // comprobar si el producto existe en la copia local del inventario
    for (int i = 0; i < length; i++) {
        if (id == idProducto[i]) {
            isContained = true;
            idx = i;
        }
    }

    if (isContained) {
        this->cantidadProducto[idx] = cantidad;
    } else {
        cout << "No existe un producto con el codigo " << id << " en el inventario. No se hicieron modificaciones." << endl;
    }
};
void Sucursal :: AgregarCliente(Cliente cliente) {
    bool isNew              = true;
    string rfc              = cliente.getRfc();
    int newCantidadCliente  = cantidadCliente + 1;

    // comprobar si el producto existe en el inventario
    for (int i = 0; i < cantidadCliente; i++) {
        if (rfc == this->cliente[i].getRfc()) {
            isNew = false;
        }
    }

    if (isNew) {
        // asignar memoria
        Cliente *tmpCliente   = new Cliente[newCantidadCliente];

        // copiar elementos
        for (int i = 0; i < cantidadCliente; i++) {
            tmpCliente[i] = this->cliente[i];
        }

        // agregar nuevo elemento
        tmpCliente[cantidadCliente] = cliente;

        // asignar a variables del objeto
        this->cliente = tmpCliente;
        cantidadCliente = newCantidadCliente;
    } else {
        cout << "Ya existe un cliente con RFC " << rfc << " en la sucursal. No se hicieron modificaciones." << endl;
    }
}
void Sucursal :: ModificarCliente(string rfc, string atributo, string valor) {
    bool isContained = false;
    bool isAttribute = false;
    int idxC, idxA;

    // comprobar si el cliente existe
    for (int i = 0; i < cantidadCliente; i++) {
        if (rfc == cliente[i].getRfc()) {
            isContained = true;
            idxC = i;
        }
    }

    // comprobar si el atributo existe
    for (int i = 0; i < 6; i++) {
        if (atributo == atributoCliente[i]) {
            isAttribute = true;
            idxA = i;
        }
    }
    
    if (isContained) {
        if (isAttribute) {
            switch (idxA) {
                case 0:
                    cliente[idxC].setNombre(valor);
                    break;
                case 1:
                    cliente[idxC].setDireccion(valor);
                    break;
                case 2:
                    cliente[idxC].setTel(valor);
                    break;
                case 3:
                    cliente[idxC].setFechaN(valor);
                    break;
                case 4:
                    cliente[idxC].setSexo(valor);
                    break;
                case 5:
                    cliente[idxC].setRfc(valor);
                    break;
            }
        } else {
            cout << "No existe un atributo \"" << atributo << "\". Los posibles atributos son ";
            for (int i = 0; i < 6; i++) {
                cout << "\"" << this->atributoCliente[i] << "\", ";
            }
            cout << "con la misma capitalizacion. No se hicieron modificaciones." << endl;
        }
    } else {
        cout << "No existe un cliente con RFC " << rfc << " en la sucursal. No se hicieron modificaciones." << endl;
    }
}
void Sucursal :: BorrarCliente(string rfc) {
    bool isContained = false;
    int idx;
    int newCantidadCliente = cantidadCliente - 1;

    // comprobar si el producto existe en el inventario
    for (int i = 0; i < cantidadCliente; i++) {
        if (rfc == this->cliente[i].getRfc()) {
            isContained = true;
            idx = i;
        }
    }

    if (isContained) {
        // declaracion
        Cliente *tmpCliente;

        // inventario vacio
        if (newCantidadCliente == 0) {
            this->cliente = tmpCliente;
        }

        // inventario no vacio
        else {
            // asignar memoria
            tmpCliente = new Cliente[newCantidadCliente];

            // copiar elementos que preceden al elemento borrado
            for (int i = 0; i < idx; i++) {
                tmpCliente[i] = this->cliente[i];
            }

            // elementos que suceden al elemento borrado
            for (int i = idx; i < newCantidadCliente; i++) {
                tmpCliente[i] = this->cliente[i + 1];
            }

            // asignar a variables del objeto
            cliente = tmpCliente;
            cantidadCliente = newCantidadCliente;
        }        
    } else {
        cout << "No existe un cliente con RFC " << rfc << " en la sucursal. No se hicieron modificaciones." << endl;
    }
}
void Sucursal :: AgregarEmpleado(Empleado empleado) {
    int newCantidadEmpleado = cantidadEmpleado + 1;

    // asignar memoria
    Empleado *tmpEmpleado = new Empleado[newCantidadEmpleado];

    // copiar elementos
    for (int i = 0; i < cantidadEmpleado; i++) {
        tmpEmpleado[i] = this->empleado[i];
    }

    // agregar nuevo elemento
    tmpEmpleado[cantidadEmpleado] = empleado;

    // asignar a variables del objeto
    this->empleado = tmpEmpleado;
    cantidadEmpleado = newCantidadEmpleado;
}
void Sucursal :: BorrarEmpleado(int idEmpleado) {
    if (idEmpleado < cantidadEmpleado) {
        int newCantidadEmpleado = cantidadEmpleado - 1;

        // nueva variable temporal
        Empleado *tmpEmpleado;

        // cero empleados
        if (newCantidadEmpleado == 0) {
            empleado = tmpEmpleado;
        }

        // uno o mas empleados
        else {
            // asignar memoria
            tmpEmpleado = new Empleado[newCantidadEmpleado];

            // copiar empleados que preceden al empleado borrado
            for (int i = 0; i < idEmpleado; i++) {
                tmpEmpleado[i] = empleado[i];
            }

            // empleados que suceden al empleado borrado
            for (int i = idEmpleado; i < newCantidadEmpleado; i++) {
                tmpEmpleado[i] = empleado[i + 1];
            }

            // asignar a variable del objeto
            empleado = tmpEmpleado;
        }
        cantidadEmpleado = newCantidadEmpleado;
    } else {
        cout << "El empleado con ID " << idEmpleado << " no existe." << endl;
    }
}
void Sucursal :: TransferirEmpleado(int idEmpleado, Sucursal &sucursal) {
    if (idEmpleado < cantidadEmpleado) {
        sucursal.AgregarEmpleado(empleado[idEmpleado]);
        BorrarEmpleado(idEmpleado);
    } else {
        cout << "El empleado con ID " << idEmpleado << " no existe." << endl;
    }
}
void Sucursal :: setNewCodigo(int idx, int newCodigo) { // para
        this->idProducto[idx] = newCodigo;
}
float Sucursal :: getPrecioV(int id) {
    return (*inventario).getPrecioV(id);
}
string Sucursal :: getNombre(int id) {
    return (*inventario).getNombre(id);
}

// BORRAR
void Sucursal :: MostrarEmpleados() {
    cout << "Empleados de Sucursal:" << endl;
    for (int i = 0; i < cantidadEmpleado; i++) {
        cout << " " << i << ". " << empleado[i].getNombre() << " (" << empleado[i].getNombreCargo() << ")" << endl;
        cout << "    " << empleado[i].getTel() << " - " << empleado[i].getDireccion() << " - " << empleado[i].getFechaN() << endl;
    }
}
void Sucursal :: MostrarClientes() {
    cout << "Clientes de Sucursal:" << endl;
    for (int i = 0; i < cantidadCliente; i++) {
        cout << " " << i << ". " << cliente[i].getNombre() << " (" << cliente[i].getRfc() << ")" << endl;
        cout << "    " << cliente[i].getTel() << " - " << cliente[i].getDireccion() << " - " << cliente[i].getFechaN() << endl;
    }
}
void Sucursal :: MostrarInventario() {
    cout << "Inventario de Sucursal: " << endl;
    for (int i = 0; i < length; i++) {
        cout << "    ID " << idProducto[i] << " : " << cantidadProducto[i] << " disponible(s)" << endl;
    }
}