/**
 * @file
 * @brief Fichero con las definiciones para la E/S de imágenes PGM
 *
 * Permite la E/S de archivos de tipos PGM
 *
 */

#include <fstream>
#include <string>
#include <cstring>
#include "pgm.h"
#include <iostream>
#include<cstdio>
#include<stdlib.h>

using namespace std;


TipoImagen LeerTipo(ifstream& f)
{
        char c1,c2;
        TipoImagen res= IMG_DESCONOCIDO;

        if (f) {
                f >> c1 >> c2;
                if (f && c1=='P')
                        switch (c2) {
                        case '5': res= IMG_PGM_BINARIO; break;
                        case '2': res= IMG_PGM_TEXTO; break;
                        default: res= IMG_DESCONOCIDO;
                        }
        }
        return res;
}


// _____________________________________________________________________________

char SaltarSeparadores (ifstream& f)
{
        char c;
        do {
                c= f.get();
        } while (isspace(c));
        f.putback(c);
        return c;
}

// _____________________________________________________________________________

bool LeerCabecera (ifstream& f, int& filas, int& columnas)
{
        int maxvalor;

        while (SaltarSeparadores(f)=='#')
                f.ignore(10000,'\n');

        f >> columnas >> filas >> maxvalor;

        if (/*str &&*/ f && filas>0 && filas <5000 && columnas >0 && columnas<5000) {
                f.get(); // Saltamos separador
                return true;
        }
        else return false;
}

// _____________________________________________________________________________

TipoImagen infoPGM(const char nombre[], int& filas, int& columnas)
{
        TipoImagen tipo;
        filas=columnas=0;
        ifstream f(nombre);

        tipo=LeerTipo(f);
        if (tipo!=IMG_DESCONOCIDO)
                if (!LeerCabecera(f,filas,columnas)) {
                        tipo=IMG_DESCONOCIDO;
                }

        return tipo;
}
/**
// _____________________________________________________________________________

bool leerPGMBinario (const char nombre[], unsigned char datos[], int& filas, int& columnas)
{
        bool exito= false;
        filas=0;
        columnas=0;
        ifstream f(nombre);

        if (LeerTipo(f)==IMG_PGM_BINARIO)
                if (LeerCabecera (f, filas, columnas))
                        if (f.read(reinterpret_cast<char *>(datos),filas*columnas))
                                exito= true;

        return exito;
}

// _____________________________________________________________________________
bool leerPGMTexto (const char nombre[], unsigned char datos[], int& filas, int &columnas)
{
      bool exito = false;
      filas = 0;
      columnas = 0;
      int buffer;
      ifstream f(nombre); //Flujo de entrada con el nombre del archivo

      //Comprobamos que sea de tipo PGMTexto
      if (LeerTipo(f)==IMG_PGM_TEXTO)
        if (LeerCabecera(f,filas,columnas)){
          for (int i=0;i<filas*columnas;i++){
            f>>buffer;
            //cout<<buffer<< " ";
            datos[i]=buffer;
          }
            exito= true;
        }

        return exito;
}
// _____________________________________________________________________________

bool escribirPGMBinario (const char nombre[], const unsigned char datos[], int filas, int columnas)
{
        ofstream f(nombre);
        bool res= true;

        if (f) {
                f << "P5" << endl;
                f << columnas << ' ' << filas << endl;
                f << 255 << endl;
                f.write(reinterpret_cast<const char *>(datos),filas*columnas);
                if (!f) res=false;
        }
        return res;
}



bool escribirPGMTexto (const char nombre[], const unsigned char datos[], int filas, int columnas)
{
        ofstream f(nombre);
        bool res = true;

        if (f) {
                f << "P2" << endl;
                f << columnas << ' ' << filas << endl;
                f << 255 << endl;
		for (int i=0;i<filas*columnas;i++){
		  f << (int)datos[i] << ' ';
		}
		if (!f) res=false;
        }
        return res;
}*/
bool leerPGMBinario (const char nombre[], byte **datos, int& filas, int& columnas) {
  bool exito= false;
  ifstream f(nombre);

  if (LeerTipo(f)==IMG_PGM_BINARIO)
    if (LeerCabecera (f, filas, columnas))
	    if (f.read(reinterpret_cast<char *>(datos[0]),filas*columnas))
	      exito= true;
  f.close();
  return exito;
}

bool escribirPGMBinario (const char nombre[], const byte ** datos, int filas, int columnas) {
  ofstream f(nombre);
  bool res= true;

  if (f) {
    f << "P5" << endl;
    f << columnas << ' ' << filas << endl;
    f << 255 << endl;
    f.write(reinterpret_cast<const char *>(datos[0]),filas*columnas);
    if (!f) res=false;
  }

  f.close();
  return res;
}

bool leerPGMTexto (const char nombre[], byte ** datos, int& filas, int& columnas){
  bool exito= false;
  ifstream f(nombre);
  int numero=0;

  if (LeerTipo(f)==IMG_PGM_TEXTO)
    if (LeerCabecera (f, filas, columnas)){
      for (int i = 0; i < filas; ++i) {
        for(int j = 0; j < columnas; j++){
          f >> numero;
          datos[i][j] = numero;
        }
      }
    }
  if(f){
    exito = true;
  }
  f.close();
 return exito;
}
bool escribirPGMTexto (const char nombre[], const byte **datos, int filas, int columnas){
  ofstream f(nombre);
  bool res= true;
  unsigned int numero = 0;

  if (f) {
    f << "P2" << endl;
    f << columnas << ' ' << filas << endl;
    f << 255 << endl;
    for (int i = 0; i < filas; i++) {
      for(int j = 0; j < columnas; j++){
        numero = (unsigned int)datos[i][j];
        f << numero;
        f << ' ';
      }
    }
    f.close();
  }
  else
    res=false;


  return res;
}
