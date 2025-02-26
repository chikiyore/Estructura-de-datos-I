#include "GestorAlquiler.h"

GestorAlquiler::GestorAlquiler(cadena nomPpal)
{
    numAlquiler=0;
    tam=0;
    Alquileres=nullptr;
    strcpy(nomFichero,nomPpal);

    fichero.open(nomFichero, ios::in | ios::binary);
        if (!fichero) {
                fichero.close();
 fichero.clear();
 fichero.open(nomFichero,ios::out|ios::binary); //se crea el fichero
 fichero.close();
 fichero.clear();
 fichero.open(nomFichero,ios::in|ios::out|ios::binary);
        cout<<"ERROR AL ABRIR EL FICHERO, CREAMOS UNO NUEVO"<<endl;
        }

        // Leer el número de alquileres desde el archivo binario
        fichero.read((char*)&numAlquiler, sizeof(numAlquiler));
        tam = numAlquiler + INCREMENTO;
        Alquileres = new TAlquiler[tam];
        // Leer los alquileres desde el archivo binario
        fichero.read((char*)Alquileres, sizeof(TAlquiler) * numAlquiler);

        // Cerrar el archivo después de leer todos los datos
        fichero.close();
}

GestorAlquiler::~GestorAlquiler()
{
    // Abrir el fichero en modo escritura para sobrescribir los datos existentes
        fichero.open(nomFichero, ios::out | ios::binary);
        if (!fichero) {
            cout << "Error al abrir el archivo para escritura." << endl;

            return;
        }

        // Escribir el número de alquileres en el fichero
        fichero.write((char*)&numAlquiler, sizeof(numAlquiler));

        // Escribir los alquileres en el fichero
        fichero.write((char*)Alquileres, sizeof(TAlquiler) * numAlquiler);

        // Cerrar el fichero después de escribir los datos
        fichero.close();

        // Liberar la memoria asignada dinámicamente para el vector de alquileres
        delete[] Alquileres;
}

void GestorAlquiler::aumentarArray() {

TAlquiler *temp = new TAlquiler[tam + INCREMENTO];
for (int i = 0; i < numAlquiler; ++i) {
     temp[i] = Alquileres[i];
}
delete[] Alquileres;
Alquileres = temp;
tam += INCREMENTO;
    }

int GestorAlquiler::getNumAlquiler(){
return numAlquiler;
}

void GestorAlquiler::nuevo(TAlquiler A){
// Asegurarse de que hay suficiente espacio en el vector
if (numAlquiler == tam) {
aumentarArray(); // Aumentar el tamaño del vector si es necesario
}

Alquileres[numAlquiler]=A;
numAlquiler++;
}

int GestorAlquiler::Buscar(cadena Datos, char DM){
bool encontrado=false;
int posicion=0;
while(!encontrado && posicion<numAlquiler){
    if (DM == 'D') {
        if(strcmp(Alquileres[posicion].Dni, Datos) == 0)
        encontrado=true;
        else
        posicion++;
    }

    else if (DM == 'M') {
        if(strcmp(Alquileres[posicion].Matricula, Datos) == 0)
        encontrado=true;
        else
        posicion++;
    }

}

if(encontrado==true)
    return posicion+1;
else
    return -1;

}

TAlquiler GestorAlquiler::consultar(int posicion) {
posicion--;
         if (posicion >= 0 && posicion < numAlquiler) {
            return Alquileres[posicion];
        } else {
        TAlquiler alquilerVacio;
        strcpy(alquilerVacio.Dni,"*");
        strcpy(alquilerVacio.Matricula,"*");
        alquilerVacio.KmsCir = 0;
        alquilerVacio.NDiasCir = 0;
        return alquilerVacio; // Devolver el alquiler vacío si la posición es incorrecta
        }
    }


bool GestorAlquiler::modificar(TAlquiler A, int posicion){
posicion--;
if (posicion >= 0 && posicion < numAlquiler) {
        Alquileres[posicion]=A;
            return true;
        } else {
        return false;
        }

}

bool GestorAlquiler::eliminarPorPosicion(int posicion){
    posicion--;
if (posicion >= 0 && posicion < numAlquiler) {
         for (int i = posicion; i < numAlquiler - 1; ++i) {
                Alquileres[i] = Alquileres[i + 1];
            }
        numAlquiler--;
            return true;
        } else {

        return false;
        }

}

