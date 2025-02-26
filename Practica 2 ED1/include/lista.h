#ifndef LISTA_H
#define LISTA_H
#include <iostream>
typedef char cadena[100];
using namespace std;
#define INCREMENTO 4
using namespace std;

struct Entrada {
 int codIdEntrada; //código identificativo de la entrada
 cadena dniComprador; //dni del dueño de la entrada
};

class lista {
 Entrada *elementos; // elementos de la lista
 int n; // nº de elementos que tiene la lista
 int Tama; // tamaño de la tabla en cada momento
 public:
 lista(); // constructor de la clase
 ~lista(); // destructor de la clase
 lista(Entrada e);
 bool esvacia();
 int longitud();
 void anadirIzq(Entrada e);
 void anadirDch(Entrada e);
 void eliminarIzq();
 void eliminarDch();
 Entrada observarIzq();
 Entrada observarDch();
 void concatenar(lista l);
 bool pertenece(Entrada e);
 void insertar(int i, Entrada e);
 void eliminar(int i);
 void modificar(int i, Entrada e);
 Entrada observar(int i);
 int posicion(Entrada e);
};
#endif // LISTA_H
