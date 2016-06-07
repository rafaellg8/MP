#include "imagen.h"
#include "pgm.h"
#include "byte.h"
#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <iostream>
using namespace std;

/**
 * Funciones Auxiliares
 */


void Imagen::copiar(byte ** data,int f, int c){
        this->nfilas = f;
        this->ncolumnas = c;
        crear(nfilas,ncolumnas);

        for (int i=0; i<nfilas; i++) {
                for (int j=0; j<ncolumnas; j++)
                        this->datos[i][j]=data[i][j];
        }
}


void Imagen::crear(int filas,int columnas){
        if (datos!=0) {
                //Si hay memoria reservada
                destruir();
        }
        this->nfilas = filas;
        this->ncolumnas = columnas;

        datos = new byte * [filas]; //array de punteros

        datos[0]= new byte [filas*columnas]; //Primera columna que apunta al array

        //Enlazamos desde la posicion 1 al final
        for (int i=1; i< filas; i++) {
                datos [i] = datos [i-1] + columnas;
        }

        //asignar valor
        for (int i=0; i<filas; i++)
                for (int j=0; j<columnas; j++)
                        datos[i][j] = 0;
}


//Funcion auxliar al destructor
void Imagen::destruir(){
        if (datos[0] != 0)
                delete [] datos [0];  //Borramos la primera fila

        if (datos != 0)
                delete [] datos;

        datos = 0;
        nfilas = ncolumnas = 0;

}

const int Imagen::filas() const {
        return nfilas;
}

const int Imagen::columnas() const {
        return ncolumnas;
}

void Imagen::set(int y, int x, byte v){
        if (this->nfilas > y && this->ncolumnas > x)
                datos[y][x]=v;
        else {
                cerr<<"Error posicion incorrecta fuera de la matriz en el set"<<endl;
                exit(1);
        }
}

const byte Imagen::get(int y, int x) const {
        if (this->nfilas > y && this->ncolumnas > x)
                return datos[y][x];
        else {
                cerr<<"Error posicion incorrecta fuera de la matriz en el get"<<endl;
                exit(1);
        }
}



void Imagen::setPos(int i, byte b){
        //Comprobamos que esta dentro de los limites
        if (i<nfilas*ncolumnas)
                datos[0][i]=b;
        else {
                cerr<<"Error posicion incorrecta fuera de la matriz "<<endl;
                exit(1);
        }
}

byte Imagen::getPos(int i){
        //Comprobamos que esta dentro de los limites
        if (i<nfilas*ncolumnas)
                return datos[0][i];
        else {
                cerr<<"Error posicion incorrecta fuera de la matriz "<<endl;
                exit(1);
        }
}

const byte Imagen::getPos(int i) const {
        //Comprobamos que esta dentro de los limites
        if (i<nfilas*ncolumnas)
                return datos[0][i];
        else {
                cerr<<"Error posicion incorrecta fuera de la matriz "<<endl;
                exit(1);
        }
}


/**+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
* Constructores
*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
Imagen::Imagen(){
        nfilas = 0;
        ncolumnas = 0;
        datos = 0;
}

Imagen::Imagen(int filas, int columnas){
        datos = 0;
        crear(filas,columnas);
}

//Destructor
Imagen::~Imagen(){
        destruir();
}

Imagen::Imagen(const Imagen & copia){
        datos = 0; //Inicializamos la variable datos para que no haya problemas
        //se esta llamando desde el constructor por lo que no se ha creado antes
        //y no hay que destruir nada
        this->copiar(copia.datos,copia.nfilas,copia.ncolumnas);
}

/**+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * SOBRECARGA DE OPERADORES
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
Imagen & Imagen::operator = (const Imagen & copia){
        this->copiar(copia.datos,copia.nfilas,copia.ncolumnas);
        return *this;
}

Imagen operator + (const Imagen imagenA, const Imagen imagenB){
        if (imagenA.filas()>0 && imagenB.filas()>0) {
                int nuevaFila = imagenA.filas() > imagenB.filas() ? imagenA.filas() : imagenB.filas(); //Nos quedamos con el mayor numero de filas
                int nuevaColumna = imagenA.columnas()+imagenB.columnas(); //Sumamos el numero de columnas

                Imagen nueva (nuevaFila,nuevaColumna);

                // //Escribimos la imagen A
                for (int i=0; i<imagenA.filas(); i++)
                        for (int j=0; j<imagenA.columnas(); j++)
                                nueva.setPos(i*nueva.columnas()+j,imagenA.get(i,j));


                //Escribimos la imagen B
                for (int i=0; i<imagenB.nfilas; i++)
                        for (int j=0; j<imagenB.ncolumnas; j++)
                                nueva.setPos(i*nueva.columnas()+j+imagenA.columnas(),imagenB.get(i,j));

                return nueva;
        }
        else{
                cout<<"\nDevolviendo imagen nula, una de las 2 imagenes no existe:"<<endl;
                Imagen nueva;
                return nueva;
        }
}

ostream & Imagen::imprimir(ofstream & out,char ** arteASCII, int f, int c){
        if (out) {
                for (int i=0; i<f; i++) {
                        for (int j=0; j<c; j++) {
                                out<<arteASCII[i][j];
                        }
                        out <<"\n";
                }

        }
        return out;
}

/**+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * FUNCIONES arteASCII
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

bool Imagen::leerImagen(const char nombreFichero[]){
        int f, c;
        TipoImagen tipo = infoPGM(nombreFichero,f,c);
        this->crear(f,c); //creamos el vector
        if(tipo==IMG_PGM_BINARIO) {
                leerPGMBinario(nombreFichero,datos,this->nfilas,this->ncolumnas);
                return true;
        }else{
                if(tipo==IMG_PGM_TEXTO) {
                        leerPGMTexto(nombreFichero,datos,f,c);
                        return true;
                }
        }
        return false;
}


const bool Imagen::escribirImagen(const char nombreFichero[], bool esBinario){
        return (esBinario) ?
               escribirPGMBinario (nombreFichero, (const_cast<const byte **>(this->datos)), this->nfilas, this->ncolumnas) :
               escribirPGMTexto(nombreFichero, (const_cast<const byte **>(this->datos)), this->nfilas, this->ncolumnas);
        //Pasamos los valores casting a constante para que no se modifiquen
}


Imagen Imagen::plano (int k){
        byte bAux; //Byte auxiliar que sacaremos de la imagen original
        bool bit; //Valor del bit kesimo
        Imagen copia(this->nfilas,this->ncolumnas); //Creamos una imagen copia
        //Recorremos pixeles
        int i=0; //Contador en forma de array
        for (int fila=0; fila<this->nfilas; fila++) {
                for (int columna=0; columna<this->ncolumnas; columna++) {
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
                                on(copia.datos[fila][columna],7);
                                for (int j=0; j<7; j++)
                                        off(copia.datos[fila][columna],j);
                        }
                        else{
                                off(copia.datos[fila][columna],7);
                                for (int j=0; j<7; j++)
                                        off(copia.datos[fila][columna],j);
                        }
                        i++;
                } //For columnas
        } //For filas
        return copia;

}



const bool Imagen::aArteASCII (const char grises[],char ** arteASCII,int maxlong){
        int filas = this->nfilas;
        int columnas = this->ncolumnas;
        int cardinal;
        byte pixel;

        cardinal = 0;
        while (grises[cardinal] != ' ') { //Recorre la lista hasta que encuentra el espacio final
                cardinal++;
        }

        //Si es mayor que filas*columnas cabe en la imagen, la creamos y devuleve true
        if (maxlong > (filas*columnas)) {
                for (int i=0; i<filas; i++) {
                        //Obtenemos valor del pixel
                        for (int j=0; j<columnas; j++) {   //Una columna menos porque la ultima tiene el caracter \n
                                pixel = this->get(i,j);
                                //Asignamos a cada posicion de arteASCII su conversion a caracteres segun el rango de intensidad
                                //de cada pixel
                                arteASCII[i][j] = grises[pixel*cardinal/256];
                        }
                }
                return true;
        }

        else {
                return false;
        }

}

const bool Imagen::aArteASCII(const char grises[], char **arteASCII, int maxlong,int cardinal){
	bool status = true;

	if (nfilas*(ncolumnas)<maxlong){
		for (int i = 0; i < filas(); i++){
			for (int j = 0; j < columnas(); j++){
				arteASCII[i][j] = grises[get(i,j)*cardinal/256];
			}
		}
	}
	else
		status = false;
	return status;
}


const bool Imagen::listaAArteASCII(const Lista &celdas){

        char ** arteASCII = 0;
        arteASCII = new char * [nfilas]; //array de punteros

        arteASCII[0]= new char [nfilas*ncolumnas]; //Primera columna que apunta al array

        //Enlazamos desde la posicion 1 al final
        for (int i=1; i< nfilas; i++) {
                arteASCII [i] = arteASCII [i-1] + ncolumnas;
        }

        bool exito=true;
        //asignar valor
        for (int i=0; i<nfilas; i++)
                for (int j=0; j<ncolumnas; j++)
                        arteASCII[i][j] = 0;

        //Para cada lista de celdas
        for(int x=0; x<celdas.longitud(); x++) {
                string gris = celdas.getCelda(x);
                const char *gris_char = gris.c_str();

                bool estado;


                estado = this->aArteASCII(gris_char, arteASCII, this->nfilas*(this->ncolumnas+1)+1);

                if(estado) {
                        char nombre_aux[255]="";
                        ofstream fsalida;
                        cout<<nombre_aux<<" "<<"ascii"<<x<<".txt"<<endl;
                        sprintf(nombre_aux, "ascii%d.txt",x); //Formateamos el nombre_aux
                        if (arteASCII !=NULL) {
                                fsalida.open(nombre_aux);
                                imprimir(fsalida,arteASCII,this->nfilas,this->ncolumnas);
                                fsalida.close();

                        }
                }else{
                        cout << "La conversión " << x << " no ha sido posible" << endl;
                        exito= false;
                }
        }
        //Liberamos memoria igual que en el destructor
        if (arteASCII[0] != 0) //Si fila de filas * columnas no esta vacia
                delete [] arteASCII [0];  //Borramos la primera fila

        if (arteASCII != 0)
                delete [] arteASCII;

        arteASCII = 0;


        return exito;

}


const bool Imagen::leeraArteASCII (const char * fichero,char * ficheroSalida,int maxlong){
        int filas = this->nfilas;
        int columnas = this->ncolumnas; //Para saltarnos el maxlong además de añadir /n
        int cardinal=0;
        byte pixel=0;
        int contadorColumna=0;
        int numCadenasGrises = 0;
        //Cadena de caracteres para la lectura del fichero grises
        char buffer [500];

        //Abrimos flujo entrada para leer del fichero
        ifstream fi;
        fi.open(fichero);

        if (fi) {
                fi.getline(buffer,500); //lee la primera linea que es basura
                fi>>numCadenasGrises;
                fi.getline(buffer,500); //Leemos la basura seguida del 4 que es una linea entera
        }
        else{
                std::cerr << "Error de lectura del fichero" << std::endl;
                return false;
        }

//Si es mayor que filas*columnas cabe en la imagen, la creamos y devuelve true
        if (maxlong > (filas*columnas)) {
                //Creamos un archivo de salida para cada numero de cadenas de grises
                for (int num=0; num<numCadenasGrises; num++) {
                        int size = 0;
                        fi.getline(buffer,500);

                        //Obtenemos el cardinal del buffer leido
                        while ((buffer[size])!=' ') {
                                cout<<buffer[size]<<" ";
                                size++;
                        }
                        cardinal=size; //Añadimos el caracter \n

                        //Ahora creamos el fichero de salida
                        ofstream fo;
                        char salida [100] = {0};
                        strcat(salida,ficheroSalida);
                        char numeroSalida[32]; //Donde guardamos el entero pasado a caracter
                        sprintf(numeroSalida,"%d",num); //Lo pasamos a caracter
                        strcat(salida,numeroSalida); //Concatenamos
                        strcat(salida,".txt");

                        fo.open(salida);
                        for (int i=0; i<filas; i++) {
                                //Obtenemos valor del pixel
                                for (int j=0; j<this->ncolumnas; j++) { //Una columna menos porque la ultima tiene el caracter \n
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
