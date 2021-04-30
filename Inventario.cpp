#include "Inventario.h"
#include <iostream>
using namespace std;

Inventario :: Inventario() {
    this->length = 0;
    this->cantidadSucursal = 0;
}
void Inventario :: Agregar(Producto producto) {
    bool isNew      = true;
    int codigo      = producto.getCodigo();
    int newLength   = length + 1;

    // comprobar si el producto existe en el inventario
    for (int i = 0; i < length; i++) {
        if (codigo == id[i]) {
            isNew = false;
        }
    }

    if (isNew) {
        // asignar memoria
        Producto *tmpProducto   = new Producto[newLength];
        int *tmpId              = new int[newLength];
        // para modificar inventarios locales
        int *cantidadProducto;

        // copiar elementos
        for (int i = 0; i < length; i++) {
            tmpProducto[i] = this->producto[i];
        }
        for (int i = 0; i < length; i++) {
            tmpId[i] = id[i];
        }

        // agregar nuevo elemento
        tmpProducto[length] = producto;
        tmpId[length] = codigo;

        // asignar a variables del objeto
        this->producto = tmpProducto;
        id = tmpId;
        length = newLength;

        // modificar copias locales de inventario en cada sucursal
        for (int i = 0; i < cantidadSucursal; i++) {
            // NOTA: newLength es ahora length, y length es ahora (length - 1)

            // asignar ID y dimension
            sucursal[i]->setLength(length);
            sucursal[i]->setIdProducto(id);

            // copiar cantidades
            cantidadProducto = sucursal[i]->getCantidadProducto();
            sucursal[i]->setCantidadProducto(new int[length]);
            for (int j = 0; j < (length - 1); j++) {
                sucursal[i]->EditarCantidad(id[j], cantidadProducto[j]);
            }

            // asignar nueva cantidad
            sucursal[i]->EditarCantidad(codigo, 0);
        }
    } else {
        cout << "Ya existe un producto con el codigo " << codigo << " en el inventario. No se hicieron modificaciones." << endl;
    }
}
void Inventario :: Modificar(int codigo, string atributo, string valor) {
    bool isContained = false;
    bool isAttribute = false;
    int idxP, idxA;

    // comprobar si el producto existe en el inventario
    for (int i = 0; i < length; i++) {
        if (codigo == id[i]) {
            isContained = true;
            idxP = i;
        }
    }

    // comprobar si el atributo existe
    for (int i = 0; i < 8; i++) {
        if (atributo == this->atributo[i]) {
            isAttribute = true;
            idxA = i;
        }
    }
    
    if (isContained) {
        if (isAttribute) {
            if (idxA == 1) {
                producto[idxP].setNombre(valor);
            } else {
                cout << "El atributo \"" << atributo << "\" es numerico, no de texto. No se hicieron modificaciones." << endl;
            }
        } else {
            cout << "No existe un atributo \"" << atributo << "\". Los posibles atributos son ";
            for (int i = 0; i < 8; i++) {
                cout << "\"" << this->atributo[i] << "\", ";
            }
            cout << "con la misma capitalizacion. No se hicieron modificaciones." << endl;
        }
    } else {
        cout << "No existe un producto con el codigo " << codigo << " en el inventario. No se hicieron modificaciones." << endl;
    }
}
void Inventario :: Modificar(int codigo, string atributo, float valor) {
    bool isContained    = false;
    bool isAttribute    = false;
    bool isInUse        = false;
    int idxP, idxA;

    // comprobar si el producto existe en el inventario
    for (int i = 0; i < length; i++) {
        if (codigo == id[i]) {
            isContained = true;
            idxP = i;
        }
    }

    // comprobar si el atributo existe
    for (int i = 0; i < 8; i++) {
        if (atributo == this->atributo[i]) {
            isAttribute = true;
            idxA = i;
        }
    }
    
    if (isContained) {
        if (isAttribute) {
            switch (idxA) { // asignar nuevo valor a atributo
                case 0:
                    // comprobar si el codigo ya esta en uso
                    for (int i = 0; i < length; i++) {
                        if (valor == id[i]) {
                            isInUse = true;
                        }
                    }
                    if (!isInUse) {
                        producto[idxP].setCodigo((int) valor);
                        id[idxP] = (int) valor;

                        // asignar a variables de sucursales
                        for (int j = 0; j < cantidadSucursal; j++) {
                            sucursal[j]->setNewCodigo(idxP, valor);
                        }
                    } else {
                        cout << "Ya existe un producto con el codigo " << codigo << " en el inventario. No se hicieron modificaciones." << endl;
                    }

                    break;
                case 1:
                    cout << "El atributo \"" << atributo << "\" es de texto, no numerico. No se hicieron modificaciones." << endl;
                    break;
                case 2:
                    producto[idxP].setPrecioC(valor);
                    break;
                case 3:
                    producto[idxP].setPrecioV(valor);
                    break;
                case 4:
                    producto[idxP].setPeso(valor);
                    break;
                case 5:
                    producto[idxP].setAlto(valor);
                    break;
                case 6:
                    producto[idxP].setAncho(valor);
                    break;
                case 7:
                    producto[idxP].setLargo(valor);
                    break;
            } // switch (idxA)
        } else {
            cout << "No existe un atributo \"" << atributo << "\". Los posibles atributos son ";
            for (int i = 0; i < 8; i++) {
                cout << "\"" << this->atributo[i] << "\", ";
            }
            cout << "con la misma capitalizacion. No se hicieron modificaciones." << endl;
        }
    } else {
        cout << "No existe un producto con el codigo " << codigo << " en el inventario. No se hicieron modificaciones." << endl;
    }
}
void Inventario :: Borrar(int codigo) {
    bool isContained = false;
    int idx;
    int newLength = length - 1;

    // comprobar si el producto existe en el inventario
    for (int i = 0; i < length; i++) {
        if (codigo == id[i]) {
            isContained = true;
            idx = i;
        }
    }

    if (isContained) {
        // nuevas variables temporales
        Producto *tmpProducto;
        int *tmpId;
        // para modificar inventarios locales
        int *cantidadProducto;

        // inventario vacio
        if (newLength == 0) {
            producto = tmpProducto;
            id = tmpId;
        }

        // inventario no vacio
        else {
            // asignar memoria
            tmpProducto = new Producto[newLength];
            tmpId = new int[newLength];

            // copiar elementos que preceden al elemento borrado
            for (int i = 0; i < idx; i++) {
                tmpProducto[i] = producto[i];
                tmpId[i] = id[i];
            }

            // elementos que suceden al elemento borrado
            for (int i = idx; i < newLength; i++) {
                tmpProducto[i] = producto[i + 1];
                tmpId[i] = id[i + 1];
            }

            // asignar a variables del objeto
            producto = tmpProducto;
            id = tmpId;
            length = newLength;

            // modificar copias locales de inventario en cada sucursal
            for (int i = 0; i < cantidadSucursal; i++) {
                // NOTA: newLength es ahora length, y length es ahora (length + 1)

                // asignar ID y dimension
                sucursal[i]->setIdProducto(id);
                sucursal[i]->setLength(newLength);

                // copiar cantidades precedentes
                cantidadProducto = sucursal[i]->getCantidadProducto();
                for (int j = 0; j < idx; j++) {
                    sucursal[i]->EditarCantidad(id[j], cantidadProducto[j]);
                }

                // copiar cantidades sucedentes
                for (int j = idx; j < length; j++) {
                    sucursal[i]->EditarCantidad(id[j], cantidadProducto[j + 1]);
                }
            }
        }        
    } else {
        cout << "No existe un producto con el codigo " << codigo << " en el inventario. No se hicieron modificaciones." << endl;
    }
}
void Inventario :: AgregarSucursal(Sucursal &sucursal) {
    int newCantidadSucursal = cantidadSucursal + 1;
    
    // asignar memoria
    Sucursal **tmpSucursal = new Sucursal*[newCantidadSucursal];

    // copiar direcciones de sucursales
    for (int i = 0; i < cantidadSucursal; i++) {
        tmpSucursal[i] = this->sucursal[i];
    }

    // agregar direccion de nueva sucursal
    tmpSucursal[cantidadSucursal] = &sucursal;

    // asignar a variables del objeto
    this->sucursal = tmpSucursal;
    cantidadSucursal = newCantidadSucursal;
}
float Inventario :: getPrecioV(int id) {
    bool isContained = false;
    int idx;

    // comprobar si el producto existe en la copia local del inventario
    for (int i = 0; i < length; i++) {
        if (id == this->id[i]) {
            isContained = true;
            idx = i;
        }
    }

    if (isContained) {
        return producto[idx].getPrecioV();
    } else {
        cout << "No existe un producto con el codigo " << id << " en el inventario." << endl;
        return 0;
    }
}
string Inventario :: getNombre(int id) {
    bool isContained = false;
    int idx;

    // comprobar si el producto existe en la copia local del inventario
    for (int i = 0; i < length; i++) {
        if (id == this->id[i]) {
            isContained = true;
            idx = i;
        }
    }

    if (isContained) {
        return producto[idx].getNombre();
    } else {
        cout << "No existe un producto con el codigo " << id << " en el inventario." << endl;
        return 0;
    }
}

// BORRAR
void Inventario :: Imprimir() {
    cout << "Items : " << length << endl;;
    for (int i = 0; i < length; i++) {
        cout << "    ID " << id[i] << " : Producto " << producto[i].getCodigo() << " : " << producto[i].getNombre() << endl;
    }
}