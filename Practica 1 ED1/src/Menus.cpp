#include "Menus.h"
#include "GestorVehiculos.h"
#include "GestorAlquiler.h"
#include "GestorClientes.h"
Menus::Menus()
{
    //ctor
}

Menus::~Menus()
{
    //dtor
}
void Menus::MenuClientes()
{
    GestorClientes gestor("ClientesSin.dat");
    int opcion;
    do
    {
        cout << "----- Menu Gestion de Clientes -----" << endl;
        cout << "1.- Consulta de clientes" << endl;
        cout << "2.- Buscar un cliente" << endl;
        cout << "3.- Nuevo cliente." << endl;
        cout << "4.- Modificar cliente." << endl;
        cout << "5.- Eliminar un cliente." << endl;
        cout << "0.- Salir." << endl;
        cout << "Ingrese una opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            cls
            cout << "Introduzca DNI o asterisco" << endl;
            cadena opcion;
            cin>>opcion;
            gestor.mostrar(opcion);
            cout<<"Numero de clientes: "<<gestor.getNumClientes()<<endl;
            break;
        case 2:
            cls
            TCliente clienteconsulta;
            cout << "Introduzca DNI" << endl;
            cadena opcionconsulta;
            cin>>opcionconsulta;
            int pos;
            pos=gestor.buscar(opcionconsulta);
            cout<<"Posicion metodo 2 :" <<pos<<endl;
            if(pos==-1)
                cout<<"ERROR, NO HAY CLIENTE CON ESE DNI "<<endl;
            else
            {
                clienteconsulta=gestor.consultar(pos);
                gestor.mostrar(clienteconsulta.Dni);
            }
            break;
        case 3:
            cls
            TCliente clientenuevo;
            cout << "Introduzca DNI " << endl;
            cadena opcdni;
            cin>>opcdni;
            cout << "Introduzca Nombre " << endl;
            cadena opcnombre;
            cin.ignore();
            cin.getline(opcnombre, 50);
            cout << "Introduzca Provincia " << endl;
            cadena opcprovincia;
            cin.ignore();
            cin.getline(opcprovincia, 50);
            strcpy(clientenuevo.Dni,opcdni);
            strcpy(clientenuevo.Nombre,opcnombre);
            strcpy(clientenuevo.Provincia,opcprovincia);
            clientenuevo.AcumuEuros=0;
            clientenuevo.AcumuKm=0;
            clientenuevo.VEnAlquiler=0;
            gestor.insertar(clientenuevo);

            break;
        case 4:
            cls
            TCliente modificarcliente;
            int contador;
            contador=0;
            cout << "Introduzca DNI" << endl;
            cadena opcionmodificar,opcmodnombre,opcmodprovincia,opcnuevonombre,opcnuevaprovincia;
            cin>>opcionmodificar;
            int posmodificar;
            posmodificar=gestor.buscar(opcionmodificar);
            if(posmodificar==-1)
                cout<<"ERROR, NO HAY CLIENTE CON ESE DNI "<<endl;
            else
            {
                modificarcliente=gestor.consultar(posmodificar);
                gestor.mostrar(modificarcliente.Dni);

                cout<<"Desea modificar el nombre? (s/n) "<<endl;
                cin>>opcmodnombre;
                if(strcmp(opcmodnombre,"s")==0)
                {
                    cout<<"Introduzca nombre: "<<endl;
                    cin.ignore();
                    cin.getline(opcnuevonombre, 50);
                    strcpy(modificarcliente.Nombre,opcnuevonombre);
                    contador++;
                }
                cout<<"Desea modificar la provincia? (s/n) "<<endl;
                cin>>opcmodprovincia;
                if(strcmp(opcmodprovincia,"s")==0)
                {
                    cout<<"Introduzca provincia: "<<endl;
                    cin.ignore();
                    cin.getline(opcnuevaprovincia, 50);
                    strcpy(modificarcliente.Provincia,opcnuevaprovincia);
                    contador++;
                }
                if(contador>0)
                {
                    gestor.modificar(modificarcliente,posmodificar);
                    cout<<"El cliente ha sido actualizado "<<endl;
                }
            }
            break;
        case 5:
            cls
            TCliente eliminarcliente;
            cout << "Introduzca DNI" << endl;
            cadena opcioneliminar,confirmareliminacion;
            cin>>opcioneliminar;
            int poseliminar;
            poseliminar=gestor.buscar(opcioneliminar);
            if(poseliminar==-1)
                cout<<"ERROR, NO HAY CLIENTE CON ESE DNI "<<endl;
            else
            {
                eliminarcliente=gestor.consultar(poseliminar);
                gestor.mostrar(eliminarcliente.Dni);
                if(eliminarcliente.VEnAlquiler==true)
                    cout<<"ERROR, NO SE PUEDE ELIMINAR POR TENER UN VEHICULO ALQUILADO "<<endl;
                else
                {
                    cout<<"Desea eliminar el cliente? (s/n) "<<endl;
                    cin>>confirmareliminacion;
                    if(strcmp(confirmareliminacion,"s")==0)
                    {
                        gestor.eliminar(poseliminar);
                        cout<<"El cliente ha sido eliminado "<<endl;
                    }
                    else
                        cout<<"El cliente no se elimina "<<endl;

                }
            }

            break;
        case 0:
            cls
            cout << "Saliendo del menu de Gestion de Clientes." << endl;
            break;
        default:
            cls
            cout << "Opcion no valida. Por favor, ingrese una opcion valida." << endl;
        }
    }
    while (opcion != 0);

}

void Menus::MenuVehiculos()
{
    GestorVehiculos gvehiculo("vehiculos.bin");
    int opcion;

    do
    {
        cout << "----- Menu Gestion de Vehiculos -----" << endl;
        cout << "1.- Consulta de vehiculos" << endl;
        cout << "2.- Buscar un vehiculo" << endl;
        cout << "3.- Nuevo vehiculo." << endl;
        cout << "4.- Modificar vehiculo." << endl;
        cout << "5.- Eliminar un vehiculo." << endl;
        cout << "6.- Renovar vehiculos." << endl;
        cout << "7.- Mostrar vehiculos en venta." << endl;
        cout << "0.- Salir." << endl;
        cout << "Ingrese una opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            cls
            cout << "Introduzca provincia o asterisco" << endl;
            cadena opcion;
            cin.ignore();
            cin.getline(opcion, 50);
            gvehiculo.mostrar(opcion);
            break;
        case 2:
            cls
            cadena opcion1,opcion2c;
            int opcion2i;
            Vehiculo vehiculo;
            do
            {
                cout << "Introduzca si quiere buscar por posicion (P) o por matricula (M)" << endl;
                cin>>opcion1;

            }
            while(strcmp(opcion1,"P")!=0 && strcmp(opcion1,"M")!=0);

            if(strcmp(opcion1,"P")==0)
            {
                cout << "Introduzca la posicion" << endl;
                cin>>opcion2i;
                vehiculo=gvehiculo.consultar(opcion2i);
            }
            else if(strcmp(opcion1,"M")==0)
            {
                cout <<"Introduzca la matricula"<<endl;
                cin>>opcion2c;
                int pos=gvehiculo.consultar(opcion2c);
                vehiculo=gvehiculo.consultar(pos);
            }
            cout<< left<< setw(20) <<"MODELO"<< setw(15) <<"MATRICULA"<< setw(15) <<"PROVINCIA"<< setw(15) <<"KILOMETROS"<< setw(20) <<"PRECIO POR KM"<<"ESTADO"<<endl;
            cout<<"*******************************************************************************************************************"<<endl;
            cout<<left<<
                setw(20) <<vehiculo.modelo<<
                setw(15) <<vehiculo.matricula<<
                setw(15) <<vehiculo.provincia<<
                setw(15) <<vehiculo.kilometros<<
                setw(20) <<vehiculo.precio_km<<
                vehiculo.estado<<endl<<endl;

            break;
        case 3:
            cls
            Vehiculo inserta;
            cadena op1,op2,op3;
            int op4;
            float op5;
            cout << "Introduzca modelo " << endl;
            cin.ignore();
            cin.getline(op1, 50);
            strcpy(inserta.modelo,op1);
            cout << "Introduzca matricula " << endl;
            cin>>op2;
            strcpy(inserta.matricula,op2);
            cout << "Introduzca provincia " << endl;
            cin.ignore();
            cin.getline(op3, 50);
            strcpy(inserta.provincia,op3);
            cout << "Introduzca kilometraje " << endl;
            cin>>op4;
            inserta.kilometros=op4;
            cout << "Introduzca precio por kilometro " << endl;
            cin>>op5;
            inserta.precio_km=op5;
            strcpy(inserta.estado,"Libre");
            gvehiculo.insertar(inserta);

            break;
        case 4:
            cls
            Vehiculo modifica;
            cadena opc1;
            float opc2;
            int posi;
            cout << "Introduzca posicion del vehiculo a modificar " << endl;
            cin>>posi;
            modifica=gvehiculo.consultar(posi);
            if(strcmp(modifica.matricula,"0")==0)
                cout<<"ERROR POSICION INCORRECTA "<<endl;
            else
            {
                cout << "Introduzca provincia " << endl;
                cin.ignore();
                cin.getline(opc1, 50);
                strcpy(modifica.provincia,opc1);
                cout << "Introduzca precio por kilometro " << endl;
                cin>>opc2;
                modifica.precio_km=opc2;
                gvehiculo.modificar(modifica,posi);
                cout<<"Vehiculo modificado correctamente"<<endl<<endl;
                }
            break;
        case 5:
            cls
            int posicioneliminar;
            Vehiculo vehiculoeliminar;
            cout << "Introduzca posicion del vehiculo a eliminar " << endl;
            cin>>posicioneliminar;
            vehiculo=gvehiculo.consultar(posicioneliminar);
            cout<< left<< setw(20) <<"MODELO"<< setw(15) <<"MATRICULA"<< setw(15) <<"PROVINCIA"<< setw(15) <<"KILOMETROS"<< setw(20) <<"PRECIO POR KM"<<"ESTADO"<<endl;
            cout<<"*******************************************************************************************************************"<<endl;
            cout<<left<<
                setw(20) <<vehiculo.modelo<<
                setw(15) <<vehiculo.matricula<<
                setw(15) <<vehiculo.provincia<<
                setw(15) <<vehiculo.kilometros<<
                setw(20) <<vehiculo.precio_km<<
                vehiculo.estado<<endl<<endl;
            gvehiculo.eliminarPorPosicion(posicioneliminar);
            break;
        case 6:
            cls
            gvehiculo.renovarvehiculos("EnVenta.dat");

            break;
        case 7:
            cls
            gvehiculo.mostrarenventa("EnVenta.dat");

            break;
        case 0:
            cls
            cout << "Saliendo del menu de Gestion de Vehiculos." << endl;
            break;
        default:
            cls
            cout << "Opcion no valida. Por favor, ingrese una opcion valida." << endl;
        }
    }
    while (opcion != 0);
}

void Menus::MenuAlquiler1()
{
    GestorAlquiler gestoralquiler("Alquileres.dat");
    GestorVehiculos vehiculos("vehiculos.bin");
    GestorClientes clientes("ClientesSin.dat");
    TAlquiler alquileres;
    Vehiculo vehiculo;
    TCliente cliente;
    int posicion,posicion2;
    int opcion;

    do
    {
        cout << "----- Menu Gestion de Alquileres -----" << endl;
        cout << "1.- Mostrar Vehiculos alquilados." << endl;
        cout << "2.- Alquilar un vehiculo." << endl;
        cout << "3.- Devolver un vehiculo." << endl;
        cout << "0.- Salir." << endl;
        cout << "Ingrese una opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            cls

            int numeroalquileres;
            numeroalquileres=gestoralquiler.getNumAlquiler();
            cout << left << setw(15) << "Matricula"
                 << setw(15) << "Kilometros"
                 << setw(15) << "Dni"
                 << setw(35) << "Nombre"
                 << setw(15) << "KmsCir"
                 << setw(15) << "NDiasCir" << endl;
            cout<<"*******************************************************************************************************************"<<endl;
//En este for empiezo en 1 porque  llamo al metodo consultar que siempre hace pos--
            for(int i=1; i<=numeroalquileres; i++)
            {
                alquileres=gestoralquiler.consultar(i);
                posicion=vehiculos.consultar(alquileres.Matricula);
                vehiculo=vehiculos.consultar(posicion);
                posicion=clientes.buscar(alquileres.Dni);
                cliente=clientes.consultar(posicion);
                cout << left << setw(15) << alquileres.Matricula
                     << setw(15) << vehiculo.kilometros
                     << setw(15) << alquileres.Dni
                     << setw(35) << cliente.Nombre
                     << setw(15) << alquileres.KmsCir
                     << setw(15) << alquileres.NDiasCir << endl;
            }
            break;
        case 2:
            cls
            cadena dni,matricula,confirmacion;
            int km,dias;
            cout << "Introduzca DNI" << endl;
            cin>>dni;
            cout << "Introduzca matricula" << endl;
            cin>>matricula;
            posicion=vehiculos.consultar(matricula);
            vehiculo=vehiculos.consultar(posicion);
            posicion2=clientes.buscar(dni);
            cliente=clientes.consultar(posicion2);
            if(clientes.buscar(dni)!=-1 && vehiculos.consultar(matricula)!=-1 && gestoralquiler.Buscar(dni,'D')==-1 && gestoralquiler.Buscar(matricula,'M')==-1 && strcmp(vehiculo.estado,"Libre")==0)
            {

                clientes.mostrar(dni);
                cout<< left<< setw(20) <<"MODELO"<< setw(15) <<"MATRICULA"<< setw(15) <<"PROVINCIA"<< setw(15) <<"KILOMETROS"<< setw(20) <<"PRECIO POR KM"<<"ESTADO"<<endl;
                cout<<"*******************************************************************************************************************"<<endl;
                cout<<left<<
                    setw(20) <<vehiculo.modelo<<
                    setw(15) <<vehiculo.matricula<<
                    setw(15) <<vehiculo.provincia<<
                    setw(15) <<vehiculo.kilometros<<
                    setw(20) <<vehiculo.precio_km<<
                    vehiculo.estado<<endl<<endl;
                cout<< "Son los datos correctos?(s/n)"<<endl;
                cin>>confirmacion;
                if(strcmp(confirmacion,"s")==0)
                {
                    cout<< "Introduce el maximo de km a circular:"<<endl;
                    cin>>km;
                    cout<< "Introduce el numero de días a circular:"<<endl;
                    cin>>dias;
                    TAlquiler nuevoalquiler;
                    strcpy(nuevoalquiler.Dni,dni);
                    strcpy(nuevoalquiler.Matricula,matricula);
                    nuevoalquiler.KmsCir=km;
                    nuevoalquiler.NDiasCir=dias;

                    //NO DICE QUE HAGA ESTO PERO ES DE SENTIDO COMUN
                    //ACTUALIZAR EL ESTADO DE ALQUILER EN CLIENTES Y VEHICULOS

                    cliente.VEnAlquiler=true;
                    strcpy(vehiculo.estado,"Ocupado");
                    vehiculos.modificar(vehiculo,posicion);
                    clientes.modificar(cliente,posicion2);

                    gestoralquiler.nuevo(nuevoalquiler);
                    cout<< "El coche ha sido alquilado."<<endl;
                }
                else
                {
                    cout<<"No se confirma "<<endl;
                    break;
                }
            }
            else
                cout<<"ALGO NO CUADRA "<<endl;
            break;
        case 3:
            cls
            cadena dni3,confirmacion3;
            int posicion3,posicionv,posicionc,KMR,NDC;
            float precio_total;
            cout << "Introduzca DNI" << endl;
            cin>>dni3;
            posicion3=gestoralquiler.Buscar(dni3,'D');
            if(posicion3!=-1){
                alquileres=gestoralquiler.consultar(posicion3);
                 cout << left << setw(15) << "Matricula"
                 << setw(15) << "Kilometros"
                 << setw(15) << "Dni"
                 << setw(35) << "Nombre"
                 << setw(15) << "KmsCir"
                 << setw(15) << "NDiasCir" << endl;
            cout<<"*******************************************************************************************************************"<<endl;

                posicionv=vehiculos.consultar(alquileres.Matricula);
                vehiculo=vehiculos.consultar(posicionv);
                posicionc=clientes.buscar(alquileres.Dni);
                cliente=clientes.consultar(posicionc);
                cout << left << setw(15) << alquileres.Matricula
                     << setw(15) << vehiculo.kilometros
                     << setw(15) << alquileres.Dni
                     << setw(35) << cliente.Nombre
                     << setw(15) << alquileres.KmsCir
                     << setw(15) << alquileres.NDiasCir << endl;
                     cout<< "Son los datos correctos?(s/n)"<<endl;
                cin>>confirmacion3;
                if(strcmp(confirmacion3,"s")==0)
                {
                    KMR=1+rand()%alquileres.KmsCir;
                    NDC=1+rand()%alquileres.NDiasCir;
                    cout<< "Kilometros Recorridos: "<<KMR<<endl;
                    cout<< "Dias Circulados: "<<NDC<<endl;
                    precio_total=KMR*vehiculo.precio_km/100+NDC*50;
                    cout<< "Precio Total: "<<precio_total<<endl;

                    cliente.VEnAlquiler=false;
                    cliente.AcumuEuros=cliente.AcumuEuros+precio_total;
                    cliente.AcumuKm=cliente.AcumuKm+KMR;
                    vehiculo.kilometros=vehiculo.kilometros+KMR;
                    strcpy(vehiculo.estado,"Libre");
                    vehiculos.modificar(vehiculo,posicionv);
                    clientes.modificar(cliente,posicionc);

                    gestoralquiler.eliminarPorPosicion(posicion3);
                    cout<< "El coche ha sido devuelto"<<endl;
                }
                else
                {
                    cout<<"No se confirma "<<endl;
                    break;
                }

            }
            else{
                cout<<"NO TIENE ALQUILER "<<endl;
            }


            break;
        case 0:
            cls
            cout << "Saliendo del menu de Gestion de Alquileres." << endl;
            break;
        default:
            cls
            cout << "Opcion no valida. Por favor, ingrese una opcion valida." << endl;
        }
    }
    while (opcion != 0);
}
