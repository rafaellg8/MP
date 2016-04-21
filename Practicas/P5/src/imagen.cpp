#include "imagen.h"
#include "pgm.h"
#include "byte.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include "../include/pgm.h"
using namespace std;

Imagen::Imagen(){
        nfilas = 0;
        ncolumnas = 0;
}

Imagen::Imagen(int filas, int columnas){
        crear(filas,columnas);

        //i = y ∗ columnas + x
        //Recorremos de forma secuencial el vector y lo ponemos a negro cada posicion
        for (int i=0; i<ncolumnas*nfilas; i++) {
                datos[i]=0;
        }
}

//Destructor
Imagen::~Imagen(){
  destruir();
}

void Imagen::crear(int filas,int columnas){
        if (nfilas*ncolumnas > 0){ //Si hay memoria reservada
          destruir();
        }
        nfilas = filas;
        ncolumnas = columnas;

        datos = new byte [nfilas*ncolumnas];

        for (int i=0; i<ncolumnas*nfilas; i++)
                datos[i]=0;
}

//Funcion auxliar al destructor
void Imagen::destruir(){
  this->nfilas = this->ncolumnas = 0;
  delete [] datos;
  delete datos;
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
   @retval true   si ha tenido éxito en la lectura
   @retval false  si se ha producido algún error en la lectura

   Lee desde disco los datos de la imagen llamada @a nombreFichero y la guarda en la memoria. La función debe asegurarse de que la imagen es de un tipo de imagen conocido y de que su tamaño es menor del tamaño máximo permitido (@c MAXDATOS)
 */
bool Imagen::leerImagen(const char nombreFichero[]){
        //Nos aseguramos de que la imagen sea de tipo PGM
        TipoImagen img = infoPGM(nombreFichero,this->nfilas,this->ncolumnas);
        //Si se crea la imagen
        if (this->nfilas*this->ncolumnas <= this->MAXPIXELS){
                if (img==IMG_PGM_BINARIO) {
                        return leerPGMBinario(nombreFichero, this->datos, this->nfilas, this->ncolumnas);
                }
                else if (img==IMG_PGM_TEXTO){
                        return leerPGMTexto(nombreFichero,this->datos,this->nfilas,this->ncolumnas);
                }
                else
                        return false;
        }
        else
                return false;
}

/**
   @brief Guarda una imagen desde un fichero
   @param nombreFichero nombre del fichero que contiene la imagen
   @param esBinario toma el valor @c true si el fichero se escribe en formato binario o @c false en caso contrario.
   @retval true   si ha tenido éxito en la escritura
   @retval false  si se ha producido algún error en la escritura
 */
bool Imagen::escribirImagen(const char nombreFichero[], bool esBinario){
  return (esBinario)?
  escribirPGMBinario (nombreFichero, this->datos, this->nfilas, this->ncolumnas):
  escribirPGMTexto(nombreFichero, this->datos, this->nfilas, this->ncolumnas);

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
        for (int i=0; i<this->nfilas*this->ncolumnas; i++) {
                //Obtenemos el byte
                bAux = this->getPos(i);
                //Ahora obtenemos el valor del bit k-esimo
                //Como recorremos en nuestra clase el vector de la forma 7 6 5 4 3 2 1 0
                //A la hora de enmascarar, le pasamos la 7-kesima de la forma que la posicion 0 es la 7 en nuestro caso
                //Entonces si queremos en realidad una posicion, necesitamos pasarlo asi
                bit = getbit(bAux,k);
                //Ahora ponemos en el bit mas significado del pixel actual de la imagen copia el valor del bit de la imagen original
                //Ponemos ese a 1 y los demas a 0 si esta encendido
                if (bit == 1) {
                        on(copia.datos[i],7);
                        for (int j=0; j<7; j++)
                                off(copia.datos[i],j);
                }
                else{
                        off(copia.datos[i],7);
                        for (int j=0; j<7; j++)
                                off(copia.datos[i],j);
                }
        } //For
        return copia;
}

/**
   @brief ArtesAscci
   @param grises vector con los caracteres
   @param arteASCII vector a devolver de imagenes
   @param maxlong maximo tamaño de aArteASCII
 */
bool Imagen::aArteASCII (const char grises[],char arteASCII[],int maxlong){
        int filas = this->nfilas;
        int columnas = this->ncolumnas+1;
        int cardinal=0;
        byte pixel=0;
        int contadorColumna=0;

//Obtenemos el tamanio de grises
        int size=0;
        while ((grises[size])!=' ') {
                size++;
        }
        cardinal=size+1; //Añadimos el caracter \n

//Si es mayor que filas*columnas cabe en la imagen, la creamos y devuleve true
        if (maxlong > (filas*columnas)) {
                for (int i=0; i<filas; i++) {
                        //Obtenemos valor del pixel
                        for (int j=0; j<columnas-1; j++) { //Una columna menos porque la ultima tiene el caracter \n
                                pixel = this->get(i,j);
                                //Asignamos a cada posicion de arteASCII su conversion a caracteres segun el rango de intensidad
                                //de cada pixel
                                arteASCII[contadorColumna] = char(grises[((pixel * cardinal/256))]);
                                contadorColumna++;
                        }
                        arteASCII[contadorColumna]='\n';
                        contadorColumna++;
                }
                return true;
        }

        else {
                return false;
        }

}

bool Imagen::aArteASCII (const char grises[],char arteASCII[],int maxlong,int tamGrises){
        int filas = this->nfilas;
        int columnas = this->ncolumnas+1;
        int cardinal=tamGrises; //Ya le hemos pasado a traves de la funcion el cardinal
        byte pixel=0;
        int contadorColumna=0;


//Si es mayor que filas*columnas cabe en la imagen, la creamos y devuleve true
        if (maxlong > (filas*columnas)) {
                for (int i=0; i<filas; i++) {
                        //Obtenemos valor del pixel
                        for (int j=0; j<columnas-1; j++) { //Una columna menos porque la ultima tiene el caracter \n
                                pixel = this->get(i,j);
                                //Asignamos a cada posicion de arteASCII su conversion a caracteres segun el rango de intensidad
                                //de cada pixel
                                arteASCII[contadorColumna] = char(grises[((pixel * cardinal/256))]);
                                contadorColumna++;
                        }
                        arteASCII[contadorColumna]='\n';
                        contadorColumna++;
                }
                return true;
        }

        else {
                return false;
        }

}

/*
Lectura de un fichero de texto con los caracteres de grises
*/
bool Imagen::leeraArteASCII (const char * fichero,char * ficheroSalida,int maxlong){
        int filas = this->nfilas;
        int columnas = this->ncolumnas+1;
        int cardinal=0;
        byte pixel=0;
        int contadorColumna=0;
        int numCadenasGrises = 0;
        //Cadena de caracteres para la lectura del fichero grises
        char buffer [500];

        //Abrimos flujo entrada para leer del fichero
        ifstream fi;
        fi.open(fichero);

        if (fi){
          fi.getline(buffer,500); //lee la primera linea que es basura
          fi>>numCadenasGrises;
          fi.getline(buffer,500);//Leemos la basura seguida del 4 que es una linea entera
          cout<<buffer<<endl;
        }
        else{
          std::cerr << "Error de lectura del fichero" << std::endl;
          return false;
        }

//Si es mayor que filas*columnas cabe en la imagen, la creamos y devuelve true
        if (maxlong > (filas*columnas)) {
          //Creamos un archivo de salida para cada numero de cadenas de grises
          for (int num=0;num<numCadenasGrises;num++){
            int size = 0;
            fi.getline(buffer,500);

            cout<<"\nLeyendo buffer"<<buffer<<endl;
            //Obtenemos el cardinal del buffer leido
            while ((buffer[size])!=' ') {
                    size++;
            }
            cardinal=size+1; //Añadimos el caracter \n

            //Ahora creamos el fichero de salida
            ofstream fo;
            char salida [100];
            strcat(salida,ficheroSalida);
            char numeroSalida[32]; //Donde guardamos el entero pasado a caracter
            sprintf(numeroSalida,"%d",num); //Lo pasamos a caracter
            strcat(salida,numeroSalida); //Concatenamos
            strcat(salida,".txt");


            fo.open(salida);
                for (int i=0; i<filas; i++) {
                        //Obtenemos valor del pixel
                        for (int j=0; j<columnas-1; j++) { //Una columna menos porque la ultima tiene el caracter \n
                                pixel = this->get(i,j);
                                //Asignamos a cada posicion de arteASCII su conversion a caracteres segun el rango de intensidad
                                //de cada pixel
                                fo<<char(buffer[((pixel * cardinal/256))]);
                                contadorColumna++;
                        }
                        fo<<'\n';
                        contadorColumna++;
                }
                fo.close();
                strcpy(salida,"");
        }
      }
        else {
                return false;
        }
        return true;
}
