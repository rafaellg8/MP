/**
  * @file
  * @brief Clase para la estructura de datos de lista de strings
  * @author Rafael Lachica Garrido / Víctor Urquízar Hinojosa
  * Permite el manejo de cadenas (strings) en una lista enlazada
  *
  */

#ifndef _LISTA_H_
#define _LISTA_H_

#include <string>

using namespace std;

struct Celda{
	string datos;		///valor de la celda actual
	Celda * siguiente;  ///puntero al siguiente elemento de la lista
};

class Lista{

private:
   Celda * cabecera;
   int num_elementos;

/**
* @brief Inicializa una Lista de celdas enlazadas
*/
	 void inicializar();
/**
* @brief Libera la memoria reservada en la lista de cadenas
*
* Libera la memoria reservada en el vetor de imagen y actualiza el numero
* de elementos de la misma a 0.
*/
   void destruir();

/**
* @brief Funcion auxiliar que imprime una lista enlazada por pantalla
* @note metodo constante para no modificar el objeto lista
*/
	void imprimir() const;

/**
* @brief Funcion auxiliar que copia en la lista this la lista @a otra
* @param otra Lista que queremos copiar
*/
	void copiar(const Lista & otra);
public:

/**
* @brief  Construye una lista vacia (0 elementos)
*/
   Lista();


/**
* @brief  Destructor
*/
   ~Lista();

/**
* @brief Construye una lista a partir de un elemento
* @param cadena el elemento a insertar en la lista
*
* Construye una lista de tamaño 1 e inserta la cadena @a cadena
*/
   Lista(string cadena);

/**
* @brief Constructor de copiar
* @param otra Lista a copiar
*/
	Lista(const Lista & otra);

/**
* @brief Sobrecarga del operador de asignacion
* @param otra Lista a copiar
*/
	Lista & operator = (const Lista & otra);

/**
* @brief Sobrecarga del operador suma. Añade a una lista un string
* @param string a concatenar
*/
  Lista & operator + (const string str);

/**
 * @brief inserta una nueva cadena al final de la lista
 * @param cad elemento a insertar en la lista
 *
 * Añade un nuevo elemento ( @a cadena ) a la lista
 */
void insertar(string cadena);

/**
 * @brief devuelve la cadena de la posicion i-esima de la lista o una cadena
 * vacia en caso de que el valor de i sea erroneo.
* @param i indice del elemento dentro de la lista
* @return la cadena que se encuentra en la celda con indice @a i
* siempre que este valor se encuentre en los margenes de la lista,
* o una cadena vacia en caso contrario
*/
string getCelda(int i) const;

/**
 * @brief devuelve el numero de celdas que contiene la lista
 * @return el tamaño de la lista
 *
 */
int longitud() const;

/**
 * @brief Construye una lista de celdas enlazadas a partir de la informacion
 * contenida en un fichero.
 * @param nombreFichero ruta del fichero de texto con el contenido de las cadenas
 * a insertar en la lista
 * @retval true si ha tenido éxito en la lectura y el formato es el correcto
 * @retval false si se ha producido algún error en la lectura
 *
 * Lee desde disco los elementos almacenados en @a nombreFichero y los guarda
 * en la lista. La función debe asegurarse de que la estructura sigue un patron
 * determinado, y se ha de crear la lista con el numero de elementos que contenga.
 */
bool leerLista(const char nombrefichero[]);

/**
* @brief Sobrecarga del operador de salida imprime una lista enlazada por pantalla
* @note metodo constante para no modificar el objeto lista
* @param out operador de salida
* @param lista Lista constante que queremos imprimir a través del operador de salida
*/
friend ostream & operator << (ostream &out,const Lista & lista);

/**
* @brief Funcion que comprueba si una lista esta sin inicializar
* @return devuelve true esta vacia la lista
**/
bool esNula() const;

};
#endif
