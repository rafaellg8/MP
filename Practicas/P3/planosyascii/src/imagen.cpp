#include "imagen.h"
#include "pgm.h"
#include "byte.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
Imagen::Imagen(){
  nfilas = 0;
  ncolumnas = 0;
}

Imagen::Imagen(int filas, int columnas){
  nfilas = filas;
  ncolumnas = columnas;

  //i = y ∗ columnas + x
  //Recorremos de forma secuencial el vector y lo ponemos a negro cada posicion
  for (int i=0;i<ncolumnas*nfilas;i++){
    datos[i]=0;
  }
}

void Imagen::crear(int filas,int columnas){
  nfilas = filas;
  ncolumnas = columnas;

  for (int i=0;i<ncolumnas*nfilas;i++)
    datos[i]=0;
}

int Imagen::filas(){
  return nfilas;
}

int Imagen::columnas(){
  return ncolumnas;
}

void Imagen::set(int y, int x, byte v){
  datos[y*ncolumnas+x]=v;
}

byte Imagen::get(int y, int x){
  return datos[y*ncolumnas+x];
}

void Imagen::setPos(int i, byte v){
  datos[i]=v;
}

byte Imagen::getPos(int i){
    return datos[i];
}


/**
@brief Carga una imagen desde un fichero
@param nombreFichero nombre del fichero que contiene la imagen
@retval true 	si ha tenido éxito en la lectura
@retval false 	si se ha producido algún error en la lectura

Lee desde disco los datos de la imagen llamada @a nombreFichero y la guarda en la memoria. La función debe asegurarse de que la imagen es de un tipo de imagen conocido y de que su tamaño es menor del tamaño máximo permitido (@c MAXDATOS)
*/
bool Imagen::leerImagen(const char nombreFichero[]){
  //Nos aseguramos de que la imagen sea de tipo PGM
  TipoImagen img = infoPGM(nombreFichero,this->nfilas,this->ncolumnas);
  if (this->nfilas*this->ncolumnas <= this->MAXPIXELS){
      return leerPGMBinario(nombreFichero, this->datos, this->nfilas, this->ncolumnas);
  }
  else
    return false;
}

/**
@brief Guarda una imagen desde un fichero
@param nombreFichero nombre del fichero que contiene la imagen
@param esBinario toma el valor @c true si el fichero se escribe en formato binario o @c false en caso contrario.
@retval true 	si ha tenido éxito en la escritura
@retval false 	si se ha producido algún error en la escritura
*/
bool Imagen::escribirImagen(const char nombreFichero[], bool esBinario){
  return escribirPGMBinario (nombreFichero, this->datos, this->nfilas, this->ncolumnas);
}

/**
@brief Dado un numero @param k extraer el plano de bits k-esimo y devolverlo como una nueva imagen
@param k bit k-esimo
*/
Imagen Imagen::plano (int k){
    byte bAux; //Byte auxiliar que sacarameos de la imagen original
    bool bit; //Valor del bit kesimo
    Imagen copia(this->nfilas,this->ncolumnas);
    //Recorremos pixeles
    for (int i=0;i<this->nfilas*this->ncolumnas;i++){
      //Obtenemos el byte
      bAux = this->getPos(i);
      //Ahora obtenemos el valor del bit k-esimo
      //Como recorremos en nuestra clase el vector de la forma 7 6 5 4 3 2 1 0
      //A la hora de enmascarar, le pasamos la 7-kesima de la forma que la posicion 0 es la 7 en nuestro caso
      //Entonces si queremos en realidad una posicion, necesitamos pasarlo asi
      bit = getbit(bAux,k);
      //Ahora ponemos en el bit mas significado del pixel actual de la imagen copia el valor del bit de la imagen original
      //Ponemos ese a 1 y los demas a 0 si esta encendido
      if (bit == 1){
        on(copia.datos[i],7);
        for (int j=0;j<7;j++)
          off(copia.datos[i],j);
      }
      else{
        off(copia.datos[i],7);
        for (int j=0;j<7;j++)
          off(copia.datos[i],j);
      }
    }//For
    return copia;
  }

/**
@brief ArtesAscci
@param char grises vector con los caracteres
@param aArteASCII vector a devolver de imagenes
@param maxlong maximo tamaño de aArteASCII
*/
bool Imagen::aArteASCII (const char grises[],char arteASCII[],int maxlong){
  int filas = this->nfilas;
  int columnas = this->ncolumnas+1;
  int cardinal=0;
  byte pixel=0;
  int contadorColumna=0;

  cardinal = 7;//+1 del espacio final
  if (maxlong > filas*columnas){
    for (int i=0;i<filas;i++){
      //Obtenemos valor del pixel
      for (int j=0;j<columnas;j++){
        contadorColumna = j;
        pixel = this->get(i,j); //Hacemos casting
        arteASCII[i*j] = grises[((pixel * cardinal/256))];
        cout<<grises[((pixel * cardinal/256))]<<" ";
      }
      cout<<endl;
    }
    return true;
  }
  else{
    return false;
  }
}
