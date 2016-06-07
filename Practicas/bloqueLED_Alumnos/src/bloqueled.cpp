#include "bloqueLed.h"
#include <iostream>
using namespace std;
typedef unsigned char bloqueLed; ///< Un @c bloqueLed contiene el estado de 8 LEDs

/**
@brief enmascara a binario una posicion
@param numero de posicion
*/
bloqueLed enmascara(int numero){
  bloqueLed binario;

  //enmsarcara la máscara en numero posiciones
  binario = 1<<numero;
  return binario;
}

/**
@brief enciende el LED @p pos del @c bloqueLed @p b
@param b 	el @c bloqueLed cuyo LED se quiere activar
@param pos 	el LED dentro de @p b que se quiere activar (0 m�s a la derecha)
*/
void on(bloqueLed &b, int pos){
  //ensmascara
  bloqueLed mask = enmascara(pos);

  //aplicarle or
  b = b | mask;

}
/**
@brief apaga el LED @p pos del  @c bloqueLed @p b
@param b 	el @c bloqueLed cuyo LED se quiere desactivar
@param pos 	el LED dentro de @p b que se quiere desactivar (0 m�s a la derecha)
*/
void off(bloqueLed &b, int pos){
  //ensmascara
  bloqueLed mask = enmascara(pos);

  mask = ~mask;

  b = b & mask;
}

/**
@brief devuelve el estado del LED (encendido = true, apagado = false) en la posici�n @p pos
@param b 	el @c bloqueLed que se quiere consultar
@param pos 	el LED dentro de @ b que se quiere consultar (0 m�s a la derecha)
@retval true 	si el LED en la posici�n @p pos est� encendido
@retval false	si el LED en la posici�n @p pos est� apagado
*/
bool get(bloqueLed b, int pos){
  //crear máscara
  bloqueLed mask = enmascara(pos);
  bool resultado = mask & b;

  if (resultado != 0)
    return true;
  else
    return false;
}

/**
@brief Muestra por la salida est�ndar una secuencia de 0s y 1s correspondiente  al estado de cada LED
@param b el @c bloqueLed que se quiere imprimir

Muestra por la salida est�ndar una secuencia de 0s y 1s correspondiente  al estado de cada LED del bloqueLed donde un cero representa que un LED est� apagado y un uno que el LED est� encendido. Se implementa utilizando la funci�n "get".

Por ejemplo, si en el @c bloqueLed @c b est�n encendidos los LEDs en posiciones 1 y 3 (0 m�s a la derecha), @c print(b); mostrar� @c 00001010

*/
void print(bloqueLed b){
  for (int i = 7;i>=0;i--) {
    cout<<get(b,i);
  }
  cout<<endl;
}

/**
@brief enciende todos los LEDs
@param b el @c bloqueLed que se quiere encender completamente.
*/
void encender(bloqueLed &b){
  b = 0b11111111;
}
/**
@brief apaga todos los LEDs
@param b el @c bloqueLed que se quiere apagar completamente.
*/
void apagar(bloqueLed &b){
  b = 0b00000000;
}

/**
@brief enciende los LEDs seg�n la configuraci�n de @p v
@param b el @c bloqueLed sobre el que se quiere actuar
@param v vector de 8 elementos que contiene la secuencia de LEDS que se quieren asignar

Asigna a @p b la configuraci�n de LEDs contenida en @p v. @p v es un vector de 8 booleanos donde @c true significa encendido y @c false significa apagado.
*/
void asignar(bloqueLed &b, const bool v[]){
for (int i=0;i<8;i++){
  if (v[i]==1)
    on(b,i);
  else
    off(b,i);
  }
}

/**
@brief recupera la configuraci�n de todos los LED
@param b el @c bloqueLed que se quiere consultar
@param v vector de 8 elementos que contendr� el estado de cada uno de los LEDs de @ b

Vuelca en @p v la configuraci�n de LEDs contenida en @p b. @c true significa encendido y @c false significa apagado. El tama�o de @p v debe ser 8.
*/
void volcar(bloqueLed b, bool v[]){
  for (int i=0;i<8;i++){
    v[i]=get(b,i);
  }
}
/**
@brief devuelve las posiciones de los LEDs encendidos
@param b el @c bloqueLed que se quiere consultar
@param posic vector de enteros (valores entre 0 a 7) que indican la posici�n de los LEDs de @p b que est�n encendidos
@param cuantos n�mero de LEDs encendidos en @p b (n�mero de elementos usados en el vector @p posic)
*/
void encendidos(bloqueLed b, int posic[], int &cuantos){
  cuantos = 0;
  for (int i=0;i<8;i++){
    if (get(b,i)==true){
      posic[cuantos]=7-i;
      cuantos++;
    }
  }
}
