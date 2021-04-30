#include "Orden.h"
#include <iostream>
using namespace std;

int main() {

    Inventario inventario;

    // c. Agregar 4 productos, modificar 1 producto y quitar 1 producto
    Producto escritorio(92, "Escritorio omega", 430.50, 599.90, 120,    0.5,  0.8, 2);
    Producto sillon(537, "Sillon mega comfort", 270.70, 330.50, 120,    2,    6,   1);
    Producto cama(398, "Cama Ginebra dormilon", 550,    650.20, 100,    0.5,  1.5, 2);
    Producto cinta(55, "Cinta adhesiva 1.50 m",   9.75,  20.50,   0.05, 0.02, 0.1, 0.1);
    inventario.Agregar(escritorio);
    inventario.Agregar(sillon);
    inventario.Agregar(cama);
    inventario.Agregar(cinta);
    inventario.Modificar(92, "nombre", "Escritorio beta");
    inventario.Borrar(55);

    cout << ">> Se crea inventario y se agregan, modifican y borran elementos" << endl;
    inventario.Imprimir();

    // a. Crear 2 sucursales
    Sucursal sucursal1(inventario);
    Sucursal sucursal2(inventario);

    cout << endl << ">> Se crean sucursales. Mostrando datos de sucursal 1:" << endl;
    sucursal1.MostrarClientes();
    sucursal1.MostrarEmpleados();
    sucursal1.MostrarInventario();

    // b. Agregar 1 gerente, 1 vendedor y 1 administrador por sucursal
    Empleado gerente1("Alicia Ortigoza", "Priv. de los Encinos 2172", "+52 33 2315 6944", "1972-11-02", "F", 4);
    Empleado vendedor1("Federico Roman", "Av. Leonardo da Vinci 420", "+52 33 6223 1856", "1997-04-15", "M", 2);
    Empleado administrador1("Ian Conan", "Calzada de la Victoria 89", "+52 33 7754 0523", "1985-02-07", "M", 3);
    Empleado gerente2("Donato Sanroman", "Paseo de los Fresnillos 5", "+52 81 1647 5492", "1977-08-23", "M", 4);
    Empleado vendedor2("Ana Maria Fray", "Av. Tlatoani Moctezuma 83", "+52 81 9965 2113", "2000-09-18", "F", 2);
    Empleado administrador2("Mateo San", "Boulevard Colomillos 7401", "+52 81 6275 4311", "1981-04-30", "M", 3);
    sucursal1.AgregarEmpleado(gerente1);
    sucursal1.AgregarEmpleado(vendedor1);
    sucursal1.AgregarEmpleado(administrador1);
    sucursal2.AgregarEmpleado(gerente2);
    sucursal2.AgregarEmpleado(vendedor2);
    sucursal2.AgregarEmpleado(administrador2);

    cout << endl << ">> Se agregan empleados a sucursales. Mostrando datos de sucursal 1:" << endl;
    sucursal1.MostrarEmpleados();


    // d. Agregar el numero de piezas de cada producto a ambas sucursales
    sucursal1.EditarCantidad(92, 12);
    sucursal1.EditarCantidad(537, 9);
    sucursal1.EditarCantidad(398, 2);
    sucursal2.EditarCantidad(92, 11);
    sucursal2.EditarCantidad(537, 3);
    sucursal2.EditarCantidad(398, 8);

    cout << endl << ">> Se editan cantidades en existencia de sucursales. Mostrando datos de sucursal 1:" << endl;
    sucursal1.MostrarInventario();

    // e. Agregar 3 clientes, modificar 1 cliente y quitar 1 cliente
    Cliente cliente1("Lautaro Gianni", "Calzada del Monte 32", "+52 55 6543 2144", "1965-05-23", "M", "GIXL650523AZ0");
    Cliente cliente2("Mara Soto Rody", "Av. los Tulipanes 55", "+52 33 6651 2158", "1988-02-01", "F", "SORM880201KWA");
    Cliente cliente3("Eulalia O Mann", "C. Dr. San Acevedo 2", "+52 81 6657 9854", "2001-12-22", "F", "OXME011222CAM");
    sucursal1.AgregarCliente(cliente1);
    sucursal1.AgregarCliente(cliente2);
    sucursal1.AgregarCliente(cliente3);
    sucursal1.ModificarCliente("OXME011222CAM", "nombre", "Eulalia de la O Mann");
    sucursal1.BorrarCliente("GIXL650523AZ0");

    cout << endl << ">> Se crean clientes y se agregan, modifican y borran de sucursal 1" << endl;
    sucursal1.MostrarClientes();

    // f. Generar una ordene intenta asignársela a un administrador (deberá mostrar error y no procesar la orden)
    Orden orden(1, "transferencia bancaria");
    orden.AsignarCliente(cliente1);
    orden.AsignarSucursal(sucursal1);
    // NOTA: Se debe asignar una sucursal antes de agregar productos porque la orden trabaja con la copia del inventario en la sucursal
    cout << endl << ">> Se crea orden y se agregan menos productos de los disponibles:" << endl;
    orden.AgregarProducto(92, 7);
    cout << endl << ">> Se crea orden y se agregan mas productos de los disponibles:" << endl;
    orden.AgregarProducto(398, 3);
    cout << endl << ">> Se agrega la cantidad exacta en existencia." << endl;
    orden.AgregarProducto(537, 9);
    cout << endl << ">> Mostrando inventario de sucursal 1 tras agregar a orden." << endl;
    sucursal1.MostrarInventario();
    // orden.Imprimir();
    cout << endl << ">> Se eliminan menos productos de los que hay en la orden." << endl;
    orden.BorrarProducto(398, 1);
    cout << endl << ">> Se elimina la cantidad exacta de productos que hay en la orden." << endl;
    orden.BorrarProducto(398, 1);
    cout << endl << ">> Se eliminan más productos de los que hay en la orden." << endl;
    orden.BorrarProducto(92, 8);
    cout << endl << ">> Mostrando inventario de sucursal 1 tras borrar de orden." << endl;
    sucursal1.MostrarInventario();
    // orden.Imprimir();
    cout << endl << ">> Se intenta asignar un empleado sin permiso de ventas." << endl;
    orden.AsignarEmpleado(administrador1);



    // g. Generar una orden e intenta asignársela a un vendedor
    orden.AsignarEmpleado(vendedor1);

    // h. Mostrar los datos de la orden generada
    cout << endl << ">> Se imprime la orden:" << endl;
    orden.Imprimir();

    // i. Mostrar los datos completos del cliente que compro la orden
    cout << endl << ">> Se imprime la información del cliente:" << endl;
    orden.DatosCliente();

    return 0;
}