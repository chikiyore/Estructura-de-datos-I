#include <iostream>
#include <Menus.h>
#include "GestorClientes.h"
using namespace std;

int main()
{
    Menus menu;
    int opcion;

    do {
        cout << "----- Menu Principal -----" << endl;
        cout << "1.- Gestion de Clientes." << endl;
        cout << "2.- Gestion de Vehiculos." << endl;
        cout << "3.- Gestion de Alquileres." << endl;
        cout << "0.- Salir." << endl;
        cout << "Ingrese una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cls
                cout << "HAS ELEGIDO LA OPCION 1" << endl;
                menu.MenuClientes();
                break;
            case 2:
                cls
               cout << "HAS ELEGIDO LA OPCION 2" << endl;
               menu.MenuVehiculos();
                break;
            case 3:
                cls
               cout << "HAS ELEGIDO LA OPCION 3" << endl;
                menu.MenuAlquiler1();

                break;
            case 0:
                cls
                cout << "Saliendo del programa. ¡Hasta luego!" << endl;
                break;
            default:
                cls
                cout << "Opcion no valida. Por favor, ingrese una opcion valida." << endl;
        }
    } while (opcion != 0);

    return 0;
}
