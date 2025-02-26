#ifndef COLA_H
#define COLA_H
#include <iostream>
#define INCREMENTO 4
using namespace std;
typedef char cadena[100];

struct SolicitudCompra {
 cadena dni; //dni del solicitante de compra de una entrada
 cadena nombre; //nombre del solicitante de compra
 int numTlfn; //n�mero de tel�fono del solicitante de compra
 cadena mail; //direcci�n de correo electr�nico del solicitante de compra
};

class cola
{
 SolicitudCompra *elementos; //elementos de la cola
 int inicio, fin; //principio y fin de la cola
 int Tama; //Capacidad de la tabla
 int ne; //N� de elementos
 public:
 cola(); // constructor de la clase
 ~cola(); // destructor de la clase
 void encolar(SolicitudCompra e);
 void desencolar();
 bool esvacia();
 SolicitudCompra primero() ;
 int longitud();
};

#endif // COLA_H
