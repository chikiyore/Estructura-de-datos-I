#include <iostream>
#include "Festival.h"
using namespace std;

int main()
{
    random_device rd;  // Semilla
    mt19937 gen(rd());
    uniform_int_distribution<> distribucion(9000, 9999);
    int opcion;
    Festival festival("FestiPrueba","20240425","20240510");

    do {

        cout << "----- GESTION FESTIVAL -----" << endl;
        cout << "1.- Mostrar información general." << endl;
        cout << "2.- Mostrar información conciertos." << endl;
        cout << "3.- Añadir concierto." << endl;
        cout << "4.- Cargar fichero concierto." << endl;
        cout << "5.- Eliminar concierto." << endl;
        cout << "6.- Mostrar entradas concierto." << endl;
        cout << "7.- Registrar compra de entrada." << endl;
        cout << "8.- Devolución entrada." << endl;
        cout << "9.- Mostrar reservas concierto." << endl;
        cout << "10.- Eliminación reserva." << endl;
        cout << "11.- Cambiar concierto." << endl;
        cout << "12.- Eliminar entradas." << endl;
        cout << "0.- Salir." << endl;
        cout << "Introduzca la opción deseada: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cls
                cout << "Mostrar información general" << endl;
                cadena nombre,fechainicio,fechafinal;
                festival.getNombre(nombre);
                festival.getFechaInicio(fechainicio);
                festival.getFechaFin(fechafinal);
                cout<<"Numero de conciertos: "<<festival.getNumConciertos()<<endl;

                break;
            case 2:
                cls
                cadena nombrebanda;
               cout << "Mostrar información conciertos" << endl;
               cout << "Introduzca nombre de artiste/banda o * para mostrar todos" << endl;

               cin.ignore();
               cin.getline(nombrebanda,30);

               if(strcmp(nombrebanda,"*")==0){
                for(int i=1;i<=festival.getNumConciertos();i++){
                    festival.mostrarInfoConcierto(i);
                }
               }
               else{
                    if(festival.existeConcierto(nombrebanda)==-1){
                cout<<"Error el artista o banda no existe "<<endl;
               }
               else
                festival.mostrarInfoConcierto(festival.existeConcierto(nombrebanda));
               }


                break;
            case 3:
                cls
                cadena fecha;
                int numentradas;
               cout << "Añadir concierto" << endl;
                cout << "Introduzca artista/grupo" << endl;
                cadena grupo3;
                cin.ignore();
                cin.getline(grupo3,20);
                if(festival.existeConcierto(grupo3)!=-1){
                    cout << "Ya existe un concierto de ese artista/grupo" << endl;
                     break;
                }
                cadena fechainicio3,fechafinal3;
                festival.getFechaInicio(fechainicio3);
                festival.getFechaFin(fechafinal3);
               do{
                cout << "Introduzca fecha valida " << endl;
                cin>>fecha;

                 }while(strcmp(fecha, fechainicio3) < 0 || strcmp(fecha, fechafinal3) > 0);
                 cout << "Introduzca el numero de entradas a la venta " << endl;
                 cin>>numentradas;

                int codidentifiador;
                do{
                    codidentifiador = distribucion(gen);
                }while(festival.existeConcierto(codidentifiador)!=-1);
              festival.programarConcierto(codidentifiador,grupo3,fecha,numentradas);

                break;

            case 4:
                cls
               cout << "Cargar fichero concierto" << endl;
               cadena nombrefichero;
               cout << "Introduzca nombre del fichero" << endl;
               cin.ignore();
               cin.getline(nombrefichero,20);
               festival.cargarConciertoDesdeFichero(nombrefichero);


                break;
            case 5:
                cls
                cadena grupoaborrar;
               cout << "Eliminar concierto" << endl;
              cout<<"Introduce nombre de artista/grupo"<<endl;
                cin.ignore();
                cin.getline(grupoaborrar,30);
                if(festival.existeConcierto(grupoaborrar)==-1){
                    cout<<"El artista o grupo no existe "<<endl;
                    }
                else{
                    festival.mostrarInfoConcierto(festival.existeConcierto(grupoaborrar));
                cout<<"¿Quiere borrarlo? s/n "<<endl;
                char op;
                cin>>op;
                if(op=='s'){
                    festival.cancelarConcierto(festival.getCodIdConcierto(festival.existeConcierto(grupoaborrar)));
                }
                else{
                    cout<<"No se borra "<<endl;
                }
                }


                break;
            case 6:
                cls
               cout << "Mostrar entradas concierto" << endl;
               cout<<"Introduzca posicion del concierto "<<endl;
               int posconcierto;
               cin>>posconcierto;
               if(festival.getCodIdConcierto(posconcierto)==-1){
                cout<<"No existe concierto en esa posicion "<<endl;
               }
               else{
                festival.mostrarEntradasVendidas(posconcierto);
               }

                break;
            case 7:
                cls
                cadena nombregrupo7;
                cadena dni7,nombre7,correo;
                int telefono;
                int decision;
                int codigoiden;
               cout << "Registrar compra de entrada" << endl;
                cout << "Introduce nombre del artista/grupo " << endl;
                cin.ignore();
                cin.getline(nombregrupo7,20);
               //cin>>nombregrupo7;
                codigoiden=festival.getCodIdConcierto(festival.existeConcierto(nombregrupo7));
                if(codigoiden!=-1){
                cout << "Introduce dni " << endl;
                cin>>dni7;
                  decision=festival.comprarEntrada(codigoiden,dni7);
                  if(decision==-1){
                    cout << "Introduce nombre " << endl;
                cin.ignore();
                cin.getline(nombre7,10);
                cout << "Introduce numero de telefono " << endl;
                cin>>telefono;
                cout << "Introduce correo " << endl;
                cin.ignore();
                cin.getline(correo,20);
                SolicitudCompra solicitud7;
                strcpy(solicitud7.dni,dni7);
                strcpy(solicitud7.mail,correo);
                strcpy(solicitud7.nombre,nombre7);
                solicitud7.numTlfn=telefono;
                festival.registrarReserva(codigoiden,solicitud7);
                  }
                }
                else{
                        cout<<"No existe dicho artista/grupo "<<endl;
                }

                break;
            case 8:
                cls
               cout << "Devolución entrada" << endl;
                cout<<"Introduce Id del artista/grupo "<<endl;
                int idgrupo;
                cin>>idgrupo;
                if(festival.existeConcierto(idgrupo)==-1){
                    cout<<"No existe ese artista/grupo "<<endl;
                    break;
                }
                cout<<"Introduce codigo identificador de la entrada "<<endl;
                int codentrada;
                cin>>codentrada;
                festival.eliminarEntrada(idgrupo,codentrada);



                break;
            case 9:
                cls
               cout << "Mostrar reservas concierto" << endl;
            cout<<"Introduce posicion del artista/grupo "<<endl;
             int posconcierto2;
               cin>>posconcierto2;
               if(festival.getCodIdConcierto(posconcierto2)==-1){
                cout<<"No existe concierto en esa posicion "<<endl;
               }
               else{
                festival.mostrarSolicitudesDeCompra(posconcierto2);
               }


                break;
            case 10:
                cls
               cout << "Eliminación reserva" << endl;
               cout<<"Introduce id del artista/grupo "<<endl;
               int id;
               cin>>id;
                cout<<"Introduce dni "<<endl;
                cadena dni;
                cin.ignore();
                cin.getline(dni,10);
                festival.eliminarReserva(id,dni);


                break;
            case 11:
                cls
                cadena dni11;
                int idconciertoorigen,idconciertodestino;
               cout << "Cambiar de concierto" << endl;
               cout<<"Introduce dni "<<endl;
                cin>>dni11;
                cout<<"Introduce id concierto origen "<<endl;
                cin>>idconciertoorigen;
                cout<<"Introduce id concierto destino "<<endl;
                cin>>idconciertodestino;
                festival.cambiardeconcierto(dni11,idconciertoorigen,idconciertodestino);

               break;
            case 12:
                cls
                cadena dni12;
               cout << "Eliminar entradas" << endl;
               cout<<"Introduce dni "<<endl;
               cin>>dni12;
               festival.eliminarentradas(dni12);

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
