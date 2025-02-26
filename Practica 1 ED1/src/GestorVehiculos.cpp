#include "GestorVehiculos.h"

GestorVehiculos::GestorVehiculos(cadena nomPpal)
{
    numVehiculos=0;
    tam=0;
    vehiculos=nullptr;
    strcpy(nomFichero,nomPpal);

    ficheroPrincipal.open(nomFichero, ios::in | ios::binary);
        if (!ficheroPrincipal) {
                 ficheroPrincipal.close();
 ficheroPrincipal.clear();
 ficheroPrincipal.open(nomFichero,ios::out|ios::binary); //se crea el fichero
 ficheroPrincipal.close();
 ficheroPrincipal.clear();
 ficheroPrincipal.open(nomFichero,ios::in|ios::out|ios::binary);
        cout<<"ERROR AL ABRIR EL FICHERO, CREAMOS UNO NUEVO"<<endl;
        }

       ficheroPrincipal.seekg(0,ios::end);
        tam = ficheroPrincipal.tellg();
          ficheroPrincipal.seekg(0,ios::beg);
          tam=tam/sizeof(Vehiculo);
          numVehiculos=tam;
          tam=tam+INCREMENTO;
        vehiculos = new Vehiculo[tam];
        // Leer los vehiculos desde el archivo binario
        ficheroPrincipal.read((char*)vehiculos, sizeof(Vehiculo) * numVehiculos);

        // Cerrar el archivo después de leer todos los datos
        ficheroPrincipal.close();
}

GestorVehiculos::~GestorVehiculos()
{
    // Abrir el fichero en modo escritura para sobrescribir los datos existentes
        ficheroPrincipal.open(nomFichero, ios::out | ios::binary);
        if (!ficheroPrincipal) {
            cout << "Error al abrir el archivo para escritura." << endl;

            return;
        }


        // Escribir los vehiculos en el fichero
        ficheroPrincipal.write((char*)vehiculos, sizeof(Vehiculo) * numVehiculos);

        // Cerrar el fichero después de escribir los datos
        ficheroPrincipal.close();

        // Liberar la memoria asignada dinámicamente para el vector de vehiculos
        delete[] vehiculos;
}

void GestorVehiculos::aumentarArray() {

Vehiculo *temp = new Vehiculo[tam + INCREMENTO];
for (int i = 0; i < numVehiculos; ++i) {
     temp[i] = vehiculos[i];
}
delete[] vehiculos;
vehiculos = temp;
tam += INCREMENTO;
    }

int GestorVehiculos::getNumVehiculos(){
return numVehiculos;
}

void GestorVehiculos::mostrar(cadena provincia){
  cout<< left<< setw(20) <<"MODELO"<< setw(15) <<"MATRICULA"<< setw(15) <<"PROVINCIA"<< setw(15) <<"KILOMETROS"<< setw(20) <<"PRECIO POR KM"<<"ESTADO"<<endl;
cout<<"*******************************************************************************************************************"<<endl;

if(strcmp(provincia,"*")==0){
for(int i=0;i<numVehiculos;i++){
    cout<<left<<
    setw(20) <<vehiculos[i].modelo<<
    setw(15) <<vehiculos[i].matricula<<
    setw(15) <<vehiculos[i].provincia<<
    setw(15) <<vehiculos[i].kilometros<<
    setw(20) <<vehiculos[i].precio_km<<
    vehiculos[i].estado<<endl;
}
}
else {
for(int i=0;i<numVehiculos;i++){
    if(strcmp(vehiculos[i].provincia,provincia)==0){
    cout<<left<<
    setw(20) <<vehiculos[i].modelo<<
    setw(15) <<vehiculos[i].matricula<<
    setw(15) <<vehiculos[i].provincia<<
    setw(15) <<vehiculos[i].kilometros<<
    setw(20) <<vehiculos[i].precio_km<<
    vehiculos[i].estado<<endl;
    }
}

}
cout<<endl;
}


Vehiculo GestorVehiculos::consultar(int posicion){
    posicion--;
if(posicion>=0 && posicion<numVehiculos)
    return vehiculos[posicion];
else{
    Vehiculo devolver;
    strcpy(devolver.matricula,"0");
    return devolver;
}
}



int GestorVehiculos::consultar(cadena matricula){
bool encontrado=false;
int posicion=0;
while(!encontrado && posicion<numVehiculos){
    if(strcmp(matricula,vehiculos[posicion].matricula)==0)
        encontrado=true;
    else
        posicion++;
}
if(encontrado==true)
    return posicion+1;
else
    return -1;

}

void GestorVehiculos::insertar(Vehiculo v){
if(tam==numVehiculos)
    aumentarArray();
bool encontrado=false;
int posicion=0;
if(consultar(v.matricula)==-1){
while(!encontrado && posicion<numVehiculos){
    if(strcmp(v.provincia,vehiculos[posicion].provincia)==0)
        encontrado=true;
    else
    posicion++;
}
if(encontrado==true){
    for(int i=numVehiculos;i>posicion;i--)
    vehiculos[i]=vehiculos[i-1];
    vehiculos[posicion]=v;
    numVehiculos++;}
else{
    vehiculos[numVehiculos]=v;
    numVehiculos++;
}
}
else
    cout<<"ERROR EL VEHICULO YA EXISTE "<<endl;

}


void GestorVehiculos::modificar(Vehiculo v, int posicion){
    posicion--;
if(posicion>=0 && posicion<numVehiculos){
    vehiculos[posicion]=v;
    }
else{
    cout<<"ERROR AL INTENTAR MODIFICAR"<<endl;
}
}

void GestorVehiculos::eliminarPorPosicion(int posicion){
    posicion--;
if(posicion>=0 && posicion<numVehiculos && !strcmp(vehiculos[posicion].estado,"Ocupado")==0){
         for (int i = posicion; i < numVehiculos - 1; i++) {
                vehiculos[i] = vehiculos[i + 1];
            }
        numVehiculos--;
        cout<<"Vehiculo eliminado correctamente"<<endl<<endl;
}
else{
    cout<<"El vehiculo esta reservado no puede eliminarse"<<endl<<endl;
}

}
//MODIFICACION EJERCICIO 1
//***************************************************************************************************
//***************************************************************************************************
//***************************************************************************************************
void GestorVehiculos::renovarvehiculos(cadena ficheroventa){
fstream ficherodeventa;
int tamventa=0;
 int numVehiculosventa=0;
int mayorkilometraje1=0;
int mayorkilometraje2=0;
int mayorkilometraje3=0;
Vehiculo renovar;
ficherodeventa.open(ficheroventa, ios::in | ios::binary);
        if (!ficherodeventa) {
                 ficherodeventa.close();
 ficherodeventa.clear();
 ficherodeventa.open(ficheroventa,ios::out|ios::binary); //se crea el fichero
 ficherodeventa.close();
 ficherodeventa.clear();
 ficherodeventa.open(ficheroventa,ios::in|ios::out|ios::binary);
        cout<<"ERROR AL ABRIR EL FICHERO, CREAMOS UNO NUEVO"<<endl;
        }
 ficherodeventa.seekg(0,ios::end);
        tamventa = ficherodeventa.tellg();
          ficherodeventa.seekg(0,ios::beg);
          tamventa=tamventa/sizeof(Vehiculo);
          numVehiculosventa=tamventa;
ficherodeventa.seekp(sizeof(Vehiculo)*numVehiculosventa,ios::beg);

//CALCULO LOS 3 KILOMETRAJES MAS ALTOS
for(int i=0;i<numVehiculos;i++){
    renovar=vehiculos[i];
    if(renovar.kilometros>mayorkilometraje1 && !(strcmp(renovar.estado,"Ocupado")==0)){
        mayorkilometraje1=renovar.kilometros;
    }
}

for(int i=0;i<numVehiculos;i++){
    renovar=vehiculos[i];
    if(renovar.kilometros>mayorkilometraje2 &&renovar.kilometros<mayorkilometraje1 && !(strcmp(renovar.estado,"Ocupado")==0)){
        mayorkilometraje2=renovar.kilometros;
    }
}
for(int i=0;i<numVehiculos;i++){
    renovar=vehiculos[i];
    if(renovar.kilometros>mayorkilometraje3 &&renovar.kilometros<mayorkilometraje2 && !(strcmp(renovar.estado,"Ocupado")==0)){
        mayorkilometraje3=renovar.kilometros;
    }
}
//Y LOS BUSCO Y ESCRIBO EN EL FICHERO
for(int i=0;i<numVehiculos;i++){
    renovar=vehiculos[i];
    if(renovar.kilometros==mayorkilometraje1 && !(strcmp(renovar.estado,"Ocupado")==0)){
        ficherodeventa.write((char *)&vehiculos[i],sizeof(Vehiculo));
        strcpy(vehiculos[i].estado,"Ocupado");
        modificar(vehiculos[i],i+1);
    }
}
for(int i=0;i<numVehiculos;i++){
    renovar=vehiculos[i];
    if(renovar.kilometros==mayorkilometraje2 && !(strcmp(renovar.estado,"Ocupado")==0)){
        ficherodeventa.write((char *)&vehiculos[i],sizeof(Vehiculo));
        strcpy(vehiculos[i].estado,"Ocupado");
        modificar(vehiculos[i],i+1);
    }
}
for(int i=0;i<numVehiculos;i++){
    renovar=vehiculos[i];
    if(renovar.kilometros==mayorkilometraje3 && !(strcmp(renovar.estado,"Ocupado")==0)){
        ficherodeventa.write((char *)&vehiculos[i],sizeof(Vehiculo));
        strcpy(vehiculos[i].estado,"Ocupado");
        modificar(vehiculos[i],i+1);
    }
}
ficherodeventa.close();
}
//***************************************************************************************************
//***************************************************************************************************
//***************************************************************************************************
//EJERCICIO 2
//***************************************************************************************************
//***************************************************************************************************
//***************************************************************************************************
 void GestorVehiculos::mostrarenventa(cadena ficheroventa){
 fstream abrirventa;
 Vehiculo *vehiculosventa;
 int tamventa=0;
 int numVehiculosventa=0;
 abrirventa.open(ficheroventa, ios::in | ios::binary);
        if (!abrirventa) {
                 abrirventa.close();
 abrirventa.clear();
 abrirventa.open(ficheroventa,ios::out|ios::binary); //se crea el fichero
 abrirventa.close();
 abrirventa.clear();
 abrirventa.open(ficheroventa,ios::in|ios::out|ios::binary);
        cout<<"ERROR AL ABRIR EL FICHERO, CREAMOS UNO NUEVO"<<endl;
        }

       abrirventa.seekg(0,ios::end);
        tamventa = abrirventa.tellg();
          abrirventa.seekg(0,ios::beg);
          tamventa=tamventa/sizeof(Vehiculo);
          numVehiculosventa=tamventa;
          tamventa=tamventa+INCREMENTO;
        vehiculosventa = new Vehiculo[tamventa];
        // Leer los vehiculos desde el archivo binario
        abrirventa.read((char*)vehiculosventa, sizeof(Vehiculo) * numVehiculosventa);

        // Cerrar el archivo después de leer todos los datos
        abrirventa.close();

         cout<< left<< setw(20) <<"MODELO"<< setw(15) <<"MATRICULA"<< setw(15) <<"PROVINCIA"<< setw(15) <<"KILOMETROS"<< setw(20) <<"PRECIO POR KM"<<"ESTADO"<<endl;
cout<<"*******************************************************************************************************************"<<endl;
 for(int i=0;i<numVehiculosventa;i++){
    cout<<left<<
    setw(20) <<vehiculosventa[i].modelo<<
    setw(15) <<vehiculosventa[i].matricula<<
    setw(15) <<vehiculosventa[i].provincia<<
    setw(15) <<vehiculosventa[i].kilometros<<
    setw(20) <<vehiculosventa[i].precio_km<<
    vehiculosventa[i].estado<<endl;
}
abrirventa.close();
delete[] vehiculosventa;
 }
//***************************************************************************************************
//***************************************************************************************************
//***************************************************************************************************
