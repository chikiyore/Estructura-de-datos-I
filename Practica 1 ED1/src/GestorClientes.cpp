#include "GestorClientes.h"
#include "Comun.h"
GestorClientes::GestorClientes(cadena NomFile)
{
    numClientes=0;
    fichero.open(NomFile,ios::binary|ios::out|ios::in);
    if(!fichero){
            fichero.close();
 fichero.clear();
 fichero.open(NomFile,ios::out|ios::binary); //se crea el fichero
 fichero.close();
 fichero.clear();
 fichero.open(NomFile,ios::in|ios::out|ios::binary);
        cout<<"ERROR AL ABRIR EL FICHERO, CREAMOS UNO NUEVO"<<endl;
        }
    else{
        fichero.read((char*)&numClientes,sizeof(numClientes));
          }

}

GestorClientes::~GestorClientes()
{
    fichero.close();
}

int GestorClientes::getNumClientes(){
    cout<<"HAY "<<numClientes<<" CLIENTES "<<endl;
return numClientes;
}

bool GestorClientes::mostrar(cadena Dni){
    int contador=0;
    TCliente cliente;
      cout<< left<< setw(15) <<"DNI" << setw(35) <<"NOMBRE" << setw(15) <<"PROVINCIA"<< setw(15) << "ACUMU KM"<< setw(15) << "ACUMU EUR" << "VEHICULO"<<endl;
cout<<"******************************************************************************************************************"<<endl;
fichero.seekg(sizeof(numClientes),ios::beg);
if(strcmp(Dni,"*")==0){

for(int i=0;i<numClientes;i++){
fichero.read((char*)&cliente,sizeof(TCliente));
    cout << left << setw(15) << cliente.Dni
                      << setw(35) << cliente.Nombre
                      << setw(15) << cliente.Provincia
                      << setw(15) << cliente.AcumuKm
                      << setw(15) << cliente.AcumuEuros
                      << (cliente.VEnAlquiler ? "SI" : "NO") << endl;
            contador++;
}

}else {
    int pos=0;
bool encontrado=false;
while(pos<numClientes && !encontrado){
         TCliente cliente;
fichero.read((char*)&cliente,sizeof(TCliente));
    if(strcmp(cliente.Dni,Dni)==0){
        encontrado=true;
    cout << left << setw(15) << cliente.Dni
                      << setw(35) << cliente.Nombre
                      << setw(15) << cliente.Provincia
                      << setw(15) << cliente.AcumuKm
                      << setw(15) << cliente.AcumuEuros
                      << (cliente.VEnAlquiler ? "SI" : "NO") << endl;
     contador++;
    }
    else
pos++;
}
fichero.clear();
}
cout<<endl;
if (contador>0)
    return true;
else
    return false;
}


int GestorClientes::buscar(cadena Dni){
bool encontrado=false;
int posicion=0;
TCliente cliente;
fichero.seekg(sizeof(numClientes),ios::beg);
while(posicion<numClientes && !encontrado){
fichero.read((char*)&cliente,sizeof(TCliente));
    if(strcmp(Dni,cliente.Dni)==0)
        encontrado=true;
    else
        posicion++;
}
fichero.clear();
return encontrado==true? (posicion+1):-1;
}

TCliente GestorClientes::consultar(int Posicion){
    Posicion--;
    TCliente cliente;
if(Posicion>=0 && Posicion<numClientes){
        fichero.seekg(sizeof(numClientes)+Posicion*sizeof(TCliente),ios::beg);
    fichero.read((char*)&cliente,sizeof(TCliente));
}
else{
    strcpy(cliente.Dni,"*");
    strcpy(cliente.Nombre,"*");
    strcpy(cliente.Provincia,"*");

}

return cliente;
}

void GestorClientes::insertar(TCliente C){
bool encontrado=false;
int posicion=0;
TCliente cliente;
if(buscar(C.Dni)==-1){
fichero.seekg(sizeof(numClientes),ios::beg);
while(!encontrado&&posicion<numClientes){
        fichero.read((char *)&cliente,sizeof(TCliente));
    if(strcmp(C.Dni,cliente.Dni)<0)
        encontrado=true;
    else
    posicion++;
}
fichero.clear();

    for(int i=numClientes;i>posicion;i--){
    fichero.seekg(sizeof(numClientes)+(i-1)*sizeof(TCliente),ios::beg);
    fichero.read((char *)&cliente,sizeof(TCliente));
    fichero.seekp(sizeof(numClientes)+i*sizeof(TCliente),ios::beg);
    fichero.write((char *)&cliente,sizeof(TCliente));
    }
    fichero.seekp(sizeof(numClientes)+posicion*sizeof(TCliente),ios::beg);
    fichero.write((char *)&C,sizeof(TCliente));
    numClientes++;
    fichero.seekp(0,ios::beg);
    fichero.write((char *)&numClientes,sizeof(numClientes));

if(fichero.fail()){
    cout<<"ERROR DE ESCRITURA "<<endl;
    fichero.clear();
}
}
else
    cout<<"ERROR EL CLIENTE YA EXISTE "<<endl;
}


bool GestorClientes::modificar(TCliente C, int Posicion){
Posicion--;
TCliente cliente;
if(Posicion>=0 && Posicion<numClientes && buscar(C.Dni)!=-1){

    /*for(int i=numClientes;i>Posicion;i--){
    fichero.seekg(sizeof(numClientes)+(i-1)*sizeof(TCliente),ios::beg);
    fichero.read((char *)&cliente,sizeof(TCliente));
    fichero.seekp(sizeof(numClientes)+i*sizeof(TCliente),ios::beg);
    fichero.write((char *)&cliente,sizeof(TCliente));
    }*/
    fichero.seekp(sizeof(numClientes)+Posicion*sizeof(TCliente),ios::beg);
    fichero.write((char *)&C,sizeof(TCliente));
    /*numClientes++;
    fichero.seekp(0,ios::beg);
    fichero.write((char *)&numClientes,sizeof(numClientes));*/

if(fichero.fail()){
    cout<<"ERROR DE ESCRITURA "<<endl;
    fichero.clear();
}
return true;
}else
    return false;

}


bool GestorClientes::eliminar(int Posicion){
Posicion--;
TCliente cliente;
if(Posicion>=0 && Posicion<numClientes){
    for(int i=Posicion;i<numClientes-1;i++){
        fichero.seekg(sizeof(numClientes)+(i+1)*sizeof(TCliente),ios::beg);
    fichero.read((char *)&cliente,sizeof(TCliente));
    fichero.seekp(sizeof(numClientes)+i*sizeof(TCliente),ios::beg);
    fichero.write((char *)&cliente,sizeof(TCliente));
    }
    numClientes--;
    fichero.seekp(0,ios::beg);
    fichero.write((char *)&numClientes,sizeof(numClientes));
    return true;
}else
 return false;



}
