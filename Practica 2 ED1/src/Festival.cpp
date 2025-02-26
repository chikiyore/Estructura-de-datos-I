#include "Festival.h"

Festival::Festival(cadena nomFestival, cadena fIni, cadena fFin)
{
    strcpy(nombre,nomFestival);
    strcpy(fechaInicio,fIni);
    strcpy(fechaFin,fFin);
    numConciertos=0;
    conciertos=nullptr;
}

//Método destructor de la clase, que liberará convenientemente la memoria reservada para almacenar
 //cada uno de los nodos tipo Concierto, generados de forma dinámica.
Festival::~Festival(){
 Concierto *Nodo_Borr, *Nodo_Sig;
Nodo_Borr=conciertos;
while (Nodo_Borr!=nullptr)
{
 Nodo_Sig=Nodo_Borr->sigC;
 delete Nodo_Borr;
 Nodo_Borr=Nodo_Sig;
}
conciertos=nullptr;
 }

void Festival::getNombre(cadena nomFestival){
strcpy(nomFestival,nombre);
cout<<"Nombre del festival: "<<nombre<<endl;
}

void Festival::getFechaInicio(cadena fIni){
strcpy(fIni,fechaInicio);
cout<<"Fecha de inicio: "<<fechaInicio<<endl;
}
void Festival::getFechaFin(cadena fFin){
strcpy(fFin,fechaFin);
cout<<"Fecha de fin: "<<fechaFin<<endl;
}

int Festival::getNumConciertos(){

return numConciertos;
}

bool Festival::programarConcierto(int idConcierto, cadena nomGrupo, cadena fecha, int numEntradasMax){
// Verificar si ya existe un concierto con el mismo idConcierto
    if (existeConcierto(idConcierto) != -1) {
            cout<<"Ya existe un concierto con el mismo identificador "<<endl;
        return false; // Ya existe un concierto con el mismo identificador
    }

    // Verificar si ya existe un concierto con el mismo nomGrupo
     if (existeConcierto(nomGrupo) != -1) {
        cout<<"Ya existe un concierto con el mismo grupo "<<endl;
        return false; // Ya existe un concierto con el mismo grupo
    }

    // Crear un nuevo nodo de tipo Concierto
    Concierto *nuevoConcierto = new Concierto;

    // Asignar valores al nuevo concierto
    nuevoConcierto->codId = idConcierto;
    strcpy(nuevoConcierto->nombreGrupo, nomGrupo);
    strcpy(nuevoConcierto->fechaCelebracion, fecha);
    nuevoConcierto->numMaxEntradas = numEntradasMax;
    nuevoConcierto->numEntradasVendidas = 0;
    nuevoConcierto->colaEspera;
    nuevoConcierto->entradasVendidas;
    nuevoConcierto->sigC = nullptr;

    // Insertar el nuevo concierto en la lista enlazada
    if (conciertos == nullptr) {
        conciertos = nuevoConcierto;
    } else {
        Concierto *temp = conciertos;
        Concierto *anterior = nullptr;
        while (temp->sigC != nullptr) {
                anterior=temp;
            temp = temp->sigC;
        }
        temp->sigC=nuevoConcierto;

    }

    // Incrementar el contador de conciertos
    numConciertos++;

    return true; // El concierto se ha programado correctamente
 }


bool Festival::cargarConciertoDesdeFichero(cadena nomFichero){
// Abrir el fichero binario
    ifstream archivo(nomFichero, ios::binary);

    // Verificar si se pudo abrir el archivo correctamente
    if (archivo.fail()) {
            cout<<"No se ha podido abrir el fichero "<<endl;
        return false; // No se pudo abrir el archivo
    }

    // Leer la información del concierto desde el archivo
    Concierto *leerconcierto=new Concierto;

    archivo.read((char*)&leerconcierto->codId, sizeof(int));
    archivo.read((char*)&leerconcierto->nombreGrupo, sizeof(cadena));
    archivo.read((char*)&leerconcierto->fechaCelebracion, sizeof(cadena));
    archivo.read((char*)&leerconcierto->numMaxEntradas, sizeof(int));
    archivo.read((char*)&leerconcierto->numEntradasVendidas, sizeof(int));
    leerconcierto->sigC=nullptr;
 //cout<<"NUMERO MAXIMO DE ENTRADAS "<<leerconcierto->numMaxEntradas<<endl;
    if (existeConcierto(leerconcierto->codId) != -1) {
            cout<<"Ya existe un concierto con el mismo identificador "<<endl;
        return false; // Ya existe un concierto con el mismo identificador
    }
    if(strcmp(leerconcierto->fechaCelebracion,fechaInicio ) < 0 || strcmp(leerconcierto->fechaCelebracion, fechaFin) > 0){
    cout<<"La fecha del concierto no esta entre las del festival "<<endl;
        return false;
    }
    if (existeConcierto(leerconcierto->nombreGrupo) != -1) {
        cout<<"Ya existe un concierto con el mismo grupo "<<endl;
        return false; // Ya existe un concierto con el mismo grupo
    }

    for (int i = 0; i < leerconcierto->numEntradasVendidas; i++) {
    Entrada entrada;
    archivo.read((char *)&entrada, sizeof(Entrada));
    leerconcierto->entradasVendidas.anadirDch(entrada);
    }
    int solicitudes=0;
    archivo.read((char *)&solicitudes, sizeof(int));
    for (int i = 0; i < solicitudes; i++) {
    SolicitudCompra solicitud;
    archivo.read((char *)&solicitud, sizeof(SolicitudCompra));
    leerconcierto->colaEspera.encolar(solicitud);
    }

    if (conciertos == nullptr) {
        conciertos = leerconcierto;
    } else {
        Concierto *temp = conciertos;
        Concierto *anterior = nullptr;
        while (temp->sigC != nullptr) {
                anterior=temp;
            temp = temp->sigC;
        }
        temp->sigC=leerconcierto;

    }


numConciertos++;
    // Cerrar el archivo
    archivo.close();

    return true; // Se cargaron los conciertos correctamente desde el archivo

}

bool Festival::cancelarConcierto(int idConcierto) {

    // Verificar si existe un concierto con el identificador indicado
    int posicion = existeConcierto(idConcierto);
    if (posicion == -1) {
        cout << "No se ha encontrado concierto con el ID indicado" << endl;
        return false; // No existe ningún concierto con el identificador indicado
    }

    // Eliminar el concierto de la lista enlazada
    Concierto *temp = conciertos;
    Concierto *anterior = nullptr;

    // Buscar el concierto a eliminar
    for (int i = 1; i < posicion; i++) {
        anterior = temp;
        temp = temp->sigC;
    }

    // Actualizar los enlaces para eliminar el nodo
    if (anterior == nullptr && numConciertos>1) { // Si el concierto es el primero en la lista
        conciertos = temp->sigC;
    }
    else if (anterior == nullptr && numConciertos==1) { // Si el concierto es el primero en la lista
        conciertos = nullptr;
    }else {
        anterior->sigC = temp->sigC;
    }
if (temp != nullptr) {
    delete temp;
} // Liberar la memoria del concierto eliminado
    numConciertos--;

    return true; // El concierto fue cancelado correctamente
}


int Festival::existeConcierto(int idConcierto){
// Recorrer la lista enlazada buscando el concierto con el identificador indicado
    Concierto *temp = conciertos;
    int posicion = 1; // Inicializar la posición del primer concierto

    while (temp != nullptr) {
        if (temp->codId == idConcierto) {
            return posicion; // Se encontró el concierto, devolver la posición
        }
        temp = temp->sigC;
        posicion++; // Incrementar la posición para el siguiente concierto
    }

    return -1;
}
int Festival::existeConcierto(cadena nomGrupo){
// Recorrer la lista enlazada buscando el concierto con el nombre de grupo indicado
    Concierto *temp = conciertos;
    int posicion = 1; // Inicializar la posición del primer concierto

    while (temp != nullptr) {
        if (strcmp(temp->nombreGrupo, nomGrupo) == 0) {
            return posicion; // Se encontró el concierto, devolver la posición
        }
        temp = temp->sigC;
        posicion++; // Incrementar la posición para el siguiente concierto
    }

    return -1; // No se encontró ningún concierto con el nombre de grupo indicado

}

void Festival::mostrarInfoConcierto(int posicion){
// Verificar si la posición está dentro de los límites válidos
    if (posicion < 1 || posicion > numConciertos) {
        cout << "Posición de concierto no válida." << endl;
        return;
    }

    // Recorrer la lista enlazada hasta encontrar el concierto en la posición indicada
    Concierto *temp = conciertos;
    int posicionActual = 1;
    while (posicionActual < posicion) {
        temp = temp->sigC;
        posicionActual++;
    }

    // Mostrar la información del concierto
    cout << "Nombre del artista: " << temp->nombreGrupo << endl;
    cout << "Código identificativo del concierto: " << temp->codId << endl;
    cout << "Fecha de celebración: " << temp->fechaCelebracion << endl;
    cout << "Número de entradas disponibles: " << temp->numMaxEntradas - temp->numEntradasVendidas << endl<<endl;


}

int Festival::getCodIdConcierto(int posicion){
 // Verificar si la posición está dentro de los límites válidos
    if (posicion < 1 || posicion > numConciertos) {
        return -1; // Posición fuera de rango, devolver -1
    }

    // Recorrer la lista enlazada hasta encontrar el concierto en la posición indicada
    Concierto *temp = conciertos;
    int posicionActual = 1;
    while (posicionActual < posicion) {
        temp = temp->sigC;
        posicionActual++;
    }

    // Devolver el código identificador del concierto en la posición indicada
    return temp->codId;
}

int Festival::comprarEntrada(int idConcierto, cadena dni){
    int posicion=existeConcierto(idConcierto);
    if(posicion==-1){
        cout<<"No existe concierto con ese identificador "<<endl;
        return -1;
    }
    Concierto *temp = conciertos;

    int posicionActual = 1;
    while (posicionActual < posicion) {
        temp = temp->sigC;
        posicionActual++;
    }

    for(int i=1;i<=temp->numEntradasVendidas;i++){
        if(strcmp(dni,temp->entradasVendidas.observar(i).dniComprador)==0){
            cout<<"Ya existe entrada vendida con ese DNI "<<endl;
            return -2;
        }
    }
    if((temp->numMaxEntradas)-(temp->numEntradasVendidas)==0)
    {
        cout<<"No quedan entradas "<<endl;
        return -1;
    }
    bool existe=false;
    Entrada nuevaentrada;
    random_device rd;  // Se utiliza para obtener una semilla aleatoria del sistema
    mt19937 gen(rd());
    uniform_int_distribution<> distribucion(10000, 50000);
    int numero;
    do{
    existe=false;
     numero = distribucion(gen);
    for(int i=1;i<=temp->numEntradasVendidas;i++){
        if(numero==temp->entradasVendidas.observar(i).codIdEntrada){
           // cout<<"Ya existe entrada con ese codigo, generamos otro codigo aleatorio "<<endl;
            existe=true;
        }
    }
    }while(existe==true);
    nuevaentrada.codIdEntrada=numero;
    strcpy(nuevaentrada.dniComprador,dni);
    temp->entradasVendidas.anadirDch(nuevaentrada);
    temp->numEntradasVendidas++;

    return numero;
}

bool Festival::registrarReserva(int idConcierto, SolicitudCompra s){
int posicion=existeConcierto(idConcierto);
    if(posicion==-1){
        cout<<"No existe concierto con ese identificador "<<endl;
        return -1;
    }
     Concierto *temp = conciertos;

    int posicionActual = 1;
    while (posicionActual < posicion) {
        temp = temp->sigC;
        posicionActual++;
    }
    if(temp->numMaxEntradas-temp->numEntradasVendidas>0){
        cout<<" Aún hay entradas disponibles en venta "<<endl;
        return -1;
    }
    bool existe=false;
    cola aux;
    while(!temp->colaEspera.esvacia()){
    if(strcmp(temp->colaEspera.primero().dni,s.dni)==0){
        existe==true;
        cout<<"Ya existe una reserva con ese dni "<<endl;
    }
    aux.encolar(temp->colaEspera.primero());
    temp->colaEspera.desencolar();

    }
    while(!aux.esvacia()){
        temp->colaEspera.encolar(aux.primero());
        aux.desencolar();
    }
    if(existe)
        return -1;

    for(int i=1;i<=temp->numEntradasVendidas;i++){
        if(strcmp(s.dni,temp->entradasVendidas.observar(i).dniComprador)==0){
            cout<<"Ya existe entrada vendida con ese DNI "<<endl;
            return -1;
        }
    }
    temp->colaEspera.encolar(s);

return true;
}

bool Festival::eliminarEntrada(int idConcierto, int idEntrada){
int posicion=existeConcierto(idConcierto);
    if(posicion==-1){
        cout<<"No existe concierto con ese identificador "<<endl;
        return -1;
    }
     Concierto *temp = conciertos;

    int posicionActual = 1;
    while (posicionActual < posicion) {
        temp = temp->sigC;
        posicionActual++;
    }
    Entrada nuevaentrada;
    nuevaentrada.codIdEntrada=idEntrada;
    strcpy(nuevaentrada.dniComprador,"");
    int posicionentrada=temp->entradasVendidas.posicion(nuevaentrada);
    if(posicionentrada==-1){
            cout<<"No existe entrada vendida con ese ID"<<endl;
         return -1;
    }

    if(!temp->colaEspera.esvacia()){

        SolicitudCompra nueva;
        nueva=temp->colaEspera.primero();
        strcpy(nuevaentrada.dniComprador,nueva.dni);
        temp->entradasVendidas.modificar(posicionentrada,nuevaentrada);
        temp->colaEspera.desencolar();
    }
    else{
    temp->entradasVendidas.eliminar(posicionentrada);
    temp->numEntradasVendidas--;
    }
return true;
}

bool Festival::eliminarReserva(int idConcierto, cadena dni){
int posicion=existeConcierto(idConcierto);
    if(posicion==-1){
        cout<<"No existe concierto con ese identificador "<<endl;
        return false;
    }
     Concierto *temp = conciertos;

    int posicionActual = 1;
    while (posicionActual < posicion) {
        temp = temp->sigC;
        posicionActual++;
    }

    bool existe=false;
    cola aux;
    while(!temp->colaEspera.esvacia()){
    if(!strcmp(temp->colaEspera.primero().dni,dni)==0){
        aux.encolar(temp->colaEspera.primero());
    temp->colaEspera.desencolar();
    }
    else{
         existe=true;
         temp->colaEspera.desencolar();

    }

    }
    while(!aux.esvacia()){
        temp->colaEspera.encolar(aux.primero());
        aux.desencolar();
    }
    if(existe==false){
            cout<<"No existe ese dni en la cola "<<endl;
        return false;
        }
    else
        return true;
}

void Festival::mostrarEntradasVendidas(int posicion){
if (posicion < 1 || posicion > numConciertos) {
        cout << "Posición de concierto no válida." << endl;
        return;
    }

    // Buscar el concierto en la posición indicada
    Concierto *temp = conciertos;
    int posicionActual = 1;
    while (posicionActual < posicion) {
        temp = temp->sigC;
        posicionActual++;
    }

    // Verificar si se encontró el concierto
    if (temp == nullptr) {
        cout << "No se encontró el concierto en la posición indicada." <<endl;
        return;
    }
    for(int i=1;i<=temp->numEntradasVendidas;i++){
    Entrada mostrarentrada=temp->entradasVendidas.observar(i);
    cout<<"Codigo: "<<mostrarentrada.codIdEntrada<<endl<<"Dni: "<<mostrarentrada.dniComprador<<endl<<endl;
    }
}

void Festival::mostrarSolicitudesDeCompra(int posicion){
if (posicion < 1 || posicion > numConciertos) {
        cout << "Posición de concierto no válida." << endl;
        return;
    }

    // Buscar el concierto en la posición indicada
    Concierto *temp = conciertos;
    int posicionActual = 1;
    while (posicionActual < posicion) {
        temp = temp->sigC;
        posicionActual++;
    }

    // Verificar si se encontró el concierto
    if (temp == nullptr) {
        cout << "No se encontró el concierto en la posición indicada." <<endl;
        return;
    }
    cola aux;
    while(!temp->colaEspera.esvacia()){
    SolicitudCompra mostrarsolicitud;
    mostrarsolicitud=temp->colaEspera.primero();
    cout<<"Dni: "<<mostrarsolicitud.dni<<endl<<"Nombre: "<<mostrarsolicitud.nombre<<endl<<"NumTlf: "<<mostrarsolicitud.numTlfn<<endl<<"Email: "<<mostrarsolicitud.mail<<endl<<endl;
    aux.encolar(temp->colaEspera.primero());
    temp->colaEspera.desencolar();

    }
    while(!aux.esvacia()){
        temp->colaEspera.encolar(aux.primero());
        aux.desencolar();
    }

}




//****************************************MODIFICACION EXAMEN**************************************
//*************************************************************************************************
//*************************************************************************************************
//*************************************************************************************************
//*************************************************************************************************
//*************************************************************************************************
//*************************************************************************************************



bool Festival::cambiardeconcierto(cadena dni, int idconciertoorigen, int idconciertodestino){
bool existe=false;
cadena nombre,correo;
int telefono;
int posicion=existeConcierto(idconciertoorigen);
    if(posicion==-1){
        cout<<"No existe concierto con ese identificador "<<endl;
        return false;
    }
     Concierto *temp = conciertos;

    int posicionActual = 1;
    while (posicionActual < posicion) {
        temp = temp->sigC;
        posicionActual++;
    }
    Entrada nuevaentrada;
    strcpy(nuevaentrada.dniComprador,dni);
    for(int i=1;i<=temp->numEntradasVendidas;i++){
    Entrada mostrarentrada=temp->entradasVendidas.observar(i);
    if(strcmp(mostrarentrada.dniComprador,dni)==0){
        nuevaentrada.codIdEntrada=mostrarentrada.codIdEntrada;
        eliminarEntrada(temp->codId,mostrarentrada.codIdEntrada);
        existe=true;
    }
    }
    if(existe==false){
            cout<<"No existe entrada con ese dni "<<endl;
        return false;
    }

    int resultadocompra=comprarEntrada(idconciertodestino,dni);
    if(resultadocompra==-1){
                    cout << "Introduce nombre " << endl;
                cin.ignore();
                cin.getline(nombre,10);
                cout << "Introduce numero de telefono " << endl;
                cin>>telefono;
                cout << "Introduce correo " << endl;
                cin.ignore();
                cin.getline(correo,20);
                SolicitudCompra solicitud7;
                strcpy(solicitud7.dni,dni);
                strcpy(solicitud7.mail,correo);
                strcpy(solicitud7.nombre,nombre);
                solicitud7.numTlfn=telefono;
                registrarReserva(idconciertodestino,solicitud7);
                  }

    return true;

}



 bool Festival::eliminarentradas(cadena dni){

 Concierto *temp = conciertos;
    int posicion = 1; // Inicializar la posición del primer concierto
bool existe=false;
    while (temp != nullptr) {
        for(int i=1;i<=temp->numEntradasVendidas;i++){
    Entrada mostrarentrada=temp->entradasVendidas.observar(i);
    if(strcmp(mostrarentrada.dniComprador,dni)==0){
        eliminarEntrada(temp->codId,mostrarentrada.codIdEntrada);
        existe=true;
    }
    }


    cola aux;
    while(!temp->colaEspera.esvacia()){
    if(!strcmp(temp->colaEspera.primero().dni,dni)==0){
        aux.encolar(temp->colaEspera.primero());
    temp->colaEspera.desencolar();
    }
    else{
         existe=true;
         temp->colaEspera.desencolar();

    }

    }
    while(!aux.esvacia()){
        temp->colaEspera.encolar(aux.primero());
        aux.desencolar();
    }
        temp = temp->sigC;
        posicion++; // Incrementar la posición para el siguiente concierto
    }

 if(existe==false){
            cout<<"No existen entradas con ese dni "<<endl;
        return false;
        }
    else
        return true;
 }

