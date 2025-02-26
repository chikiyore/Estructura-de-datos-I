#ifndef FESTIVAL_H
#define FESTIVAL_H
#include "lista.h"
#include "cola.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include <random>
typedef char cadena[100]; //Definici�n del tipo de datos Cadena.
#define cls system("cls"); //Macro para borrar la pantalla
using namespace std;

struct Concierto{
 int codId; //c�digo �nico identificativo del concierto
 cadena nombreGrupo; //nombre del grupo o artista que realiza la actuaci�n
 cadena fechaCelebracion; //fecha de celebraci�n del concierto. Formato: AAAAMMDD
 int numMaxEntradas; //n�mero m�ximo de entradas disponibles para el concierto
 int numEntradasVendidas; //n�mero de entradas vendidas para el concierto
 cola colaEspera; //cola de solicitudes de compra de entradas
 lista entradasVendidas; //lista de entradas vendidas
 Concierto *sigC;
};

class Festival{
 Concierto *conciertos; //puntero inicial de la estructura de nodos enlazados de tipo Concierto
 //correspondiente al conjunto de conciertos que integran el festival
 int numConciertos; //n�mero de conciertos registrados en el festival
 cadena nombre; //nombre del festival
 cadena fechaInicio; //fecha de comienzo del festival, con formato AAAAMMDD
 cadena fechaFin; //fecha en la que finaliza el festival, con formato AAAAMMDD
public:
 //M�todo constructor de la clase. Inicializara los atributos nombre, fechaInicio y fechaFin
 //respectivamente con los valores contenidos en los par�metros nombreConcierto, fIni y fFin.
 //El nuevo festival inicialmente no tendr� ning�n concierto registrado, siendo necesario
 //inicializar el atributo numConciertos de acuerdo con esta circunstancia.
 Festival(cadena nomFestival, cadena fIni, cadena fFin);
 //M�todo para devolver el nombre del festival a trav�s del par�metro de E/S nomFestival.
 void getNombre(cadena nomFestival);
 //M�todo para devolver la fecha de comienzo del festival a trav�s del par�metro de E/S fIni.
 void getFechaInicio(cadena fIni);
 //M�todo para devolver la fecha de clausura del festival a trav�s del par�metro de E/S fFin.
 void getFechaFin(cadena fFin);
 //M�todo para devolver el n�mero de conciertos registrados en el festival
 int getNumConciertos();
 //M�todo para registrar un nuevo concierto en el festival. Insertara un nuevo registro tipo
 //Concierto en la estructura enlazada accesible a trav�s del atributo conciertos. Dicho
 //registro ser� previamente inicializado a partir de los par�metros reales recibidos por el
 //m�todo. El identificador codId de un Concierto es �nico en el sistema, por lo que ser�
 //necesario garantizar que no existe almacenado previamente ning�n concierto con el mismo
 //valor para dicho campo que el indicado por el par�metro idConcierto. Igualmente, se asume
 //que en un mismo festival no ocurrir� en m�s de una ocasi�n la actuaci�n de un mismo artista.
 //Por tanto tambi�n ser� necesario garantizar que no se a�ada el concierto si ya hay otro
 //registro para el artista/grupo indicado. El m�todo devolver� true en caso de que se haya
 //podido realizar la inserci�n del nuevo concierto; false evidentemente en caso contrario.
 bool programarConcierto(int idConcierto, cadena nomGrupo, cadena fecha, int numEntradasMax);
 //M�todo para registrar un nuevo concierto en el festival, a partir de la informaci�n
 //contenida en el fichero binario con nombre el indicado por el par�metro nomFichero. El
 //m�todo devolver� true en caso de realizarse correctamente la apertura del fichero indicado;
 //false en caso contrario.
 bool cargarConciertoDesdeFichero(cadena nomFichero);
 //M�todo para eliminar el concierto con identificador el indicado por el par�metro idConcierto.
 //Si no existe ning�n concierto con el identificador indicado el m�todo devolver� false; true
 //en caso contrario, confirmando que dicho concierto ha sido eliminado de la estructura
 //enlazada.
 bool cancelarConcierto(int idConcierto);
 //M�todo que permite conocer si existe en el festival un concierto con c�digo identificador
 //coincidente con el pasado como par�metro. Devolver� su posici�n dentro de la secuencia de
 //nodos enlazados, donde el primer elemento es el 1, en caso de existir; -1 en caso contrario.
 int existeConcierto(int idConcierto);

 //M�todo que permite conocer si existe en el festival un concierto del artista/grupo de nombre
 //coincidente con el indicado por el par�metro nomGrupo. Devolver� su posici�n dentro de la
 //secuencia de nodos enlazados, donde el primer elemento es el 1, en caso de existir; -1 en
 //caso contrario.
 int existeConcierto(cadena nomGrupo);
 //M�todo para mostrar por pantalla la informaci�n del concierto que se encuentra en la
 //posici�n indicada por el par�metro posicion dentro de la secuencia enlazada accesible a
 //partir de conciertos, donde el primer elemento est� en la posici�n 1. Se mostrar� el nombre
 //del artista, el c�digo identificativo del concierto, la fecha de celebraci�n y el n�mero de
 //entradas disponibles.
 void mostrarInfoConcierto(int posicion);
 //M�todo para obtener el c�digo identificador �nico (codId) del concierto almacenado en la
 //posici�n indicada por el par�metro posicion dentro de la secuencia de nodos enlazados tipo
 //Concierto accesible a trav�s del atributo conciertos. Si el valor de posicion est� fuera del
 //rango efectivo, el m�todo devolver� un -1.
 int getCodIdConcierto(int posicion);
 //M�todo para registrar la compra de una entrada en el concierto de c�digo identificador �nico
 //idConcierto. Si hay entradas disponibles, y no hay ninguna otra ya registrada con el mismo dni
 //que el indicado por par�metro, se generar� un registro Entrada, y ser� almacenado en la
 //lista entradasVendidas del Concierto. El campo codIdEntrada ser� generado de forma aleatoria,
 //dentro del rango [10000, 50000], garantizando adem�s que para un mismo concierto no existan
 //dos entradas distintas con el mismo c�digo. El m�todo devolver� dicho valor aleatorio. Si no
 //hay entradas disponibles, o bien ya existe otra entrada con el mismo dni que el indicado por el
 //par�metro correspondiente, el m�todo devolver� un -1.
 int comprarEntrada(int idConcierto, cadena dni);
 //M�todo para registrar una reserva en el concierto de c�digo identificador �nico idConcierto.
 //La instancia de tipo SolicitudCompra ser� a�adida al final de la cola colaEspera del concierto
 // correspondiente. El m�todo devolver� true cuando el registro es encolado correctamente;
 //false en caso contrario, esto es, cuando no exista ning�n concierto en el festival con el
 //c�digo identificador indicado por el par�metro idConcierto, o bien cuando a�n haya entradas
 //disponibles para dicho concierto, y por tanto no tenga sentido registrar una solicitud de
 //compra en espera. Adem�s, se asume que no puede haber dos reservas realizadas por la misma
 //persona, por lo que igualmente ser� necesario comprobar que no hay ya otro registro con dni
 //igual al indicado en el par�metro s, y devolver un false tambi�n en caso de que esto ocurra.
 bool registrarReserva(int idConcierto, SolicitudCompra s);
 //M�todo para eliminar de la lista entradasVendidas la entrada de c�digo identificativo idEntrada,
 //correspondiente al concierto de c�digo idConcierto. Al liberarse una entrada, ser� necesario
 //comprobar si hab�a solicitudes de compra en espera. En caso positivo, habr� que registrar una
 //nueva entrada para la solicitud a la cabeza de la cola, y evidentemente eliminar este elemento
 //de la misma. Esta nueva entrada deber� conservar el idEntrada de la entrada eliminada. El m�todo
 //devolver� true en caso de eliminar correctamente la entrada de la lista; false en caso contrario,
 //cuando no exista un concierto, o bien una entrada para el mismo, con el identificador indicado.
 bool eliminarEntrada(int idConcierto, int idEntrada);
 //M�todo para eliminar una solicitud de compra registrada para el concierto de identificador
 //idConcierto. Eliminar� de la cola colaEspera dicho registro. Devolver� true en caso de eliminarse
 //el registro correctamente; false en caso contrario, cuando no exista el concierto con
 //identificador idConcierto, o bien una reserva para una persona con el dni indicado por el par�metro
 //correspondiente.
 bool eliminarReserva(int idConcierto, cadena dni);
 //M�todo para mostrar la informaci�n de cada entrada vendida para el concierto que se encuentra en
 //la posici�n indicada por el par�metro posicion, dentro de la secuencia de nodos enlazados
 //accesibles a partir del atributo conciertos. Si no hay concierto alguno en la posici�n indicada,
 //el m�todo mostrara un mensaje de error. Se considera que el primer elemento es el situado en la
 //posicion 1.
 void mostrarEntradasVendidas(int posicion);
 //M�todo para mostrar la informaci�n de cada reserva en la cola colaEspera del concierto que se
 //encuentra en la posici�n indicada por el par�metro posici�n, dentro de la secuencia de nodos
 //enlazados accesibles a partir del atributo conciertos. Si no hay concierto alguno en la posici�n
 //indicada, el m�todo mostrara un mensaje de error. Se considera que el primer elemento es el
 //situado en la posici�n 1.
 void mostrarSolicitudesDeCompra(int posicion);
 //M�todo destructor de la clase, que liberar� convenientemente la memoria reservada para almacenar
 //cada uno de los nodos tipo Concierto, generados de forma din�mica.
 ~Festival();

 bool cambiardeconcierto(cadena dni, int idconciertoorigen, int idconciertodestino);

 bool eliminarentradas(cadena dni);
};


#endif // FESTIVAL_H
