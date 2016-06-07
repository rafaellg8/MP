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
#include <cstdio>
#include <stdlib.h>

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

        if (f && filas>0 && filas <5000 && columnas >0 && columnas<5000) {
                f.get();
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

bool escribirPGMTexto (const char nombre[], const byte **datos, int filas, int columnas){
        ofstream f(nombre);
        bool res= true;
        unsigned int buffer = 0;

        if (f) {
                f << "P2" << endl;
                f << columnas << ' ' << filas << endl;
                f << 255 << endl;
                for (int i = 0; i < filas; i++) {
                        for(int j = 0; j < columnas; j++) {
                                buffer = (unsigned int)datos[i][j];
                                f << buffer;
                                f << ' ';
                        }
                }
                f.close();
        }
        else
                res=false;


        return res;
}


bool leerPGMBinario (const char nombre[], byte **datos, int& filas, int& columnas) {
        bool exito= false;
        ifstream f(nombre);

        if (f) {
                if (LeerTipo(f)==IMG_PGM_BINARIO)
                        if (LeerCabecera (f, filas, columnas))
                                if (f.read(reinterpret_cast<char *>(datos[0]),filas*columnas))
                                        exito= true;
                f.close(); //Cierro fichero
        }
        return exito;
}


bool leerPGMTexto (const char nombre[], byte ** datos, int& filas, int& columnas){
        bool exito= false;
        ifstream f(nombre); //Flujo de entrada con el nombre del archivo

        int buffer=0;
        if (f) {
                if (LeerTipo(f)==IMG_PGM_TEXTO)
                        if (LeerCabecera (f, filas, columnas)) {
                                for (int i = 0; i < filas; ++i) {
                                        for(int j = 0; j < columnas; j++) {
                                                f >> buffer;
                                                datos[i][j] = buffer;
                                        }
                                }
                        }

                exito = true;
                f.close();
        }
        return exito;
}
