//lee imagenes/gio.pgm y la convierte en ascii con los caracteres "@%#*+=-:. "
#include <iostream>
#include <imagen.h>

using namespace std;

/**
 * @brief Funcion auxiliar para imprimir la matriz arteASCII
 */
void imprimir(char ** arteASCII, int f, int c){
        if (arteASCII!=0)
                for (int i=0; i<f; i++) {
                        for (int j=0; j<c; j++) {
                                cout<<arteASCII[i][j];
                        }
                        cout <<"\n";
                }
}

/**
 * @brief Funcion auxiliar que crea he inicializa la matriz por defecto arteASCII
 * @param arteASCII matriz de tipo char para crear
 * @param f entero numero de filas
 * @param c entero numero de columnas
 */
void crear(char ** &arteASCII, int f, int c){
        //Si esta sin crear arteASCII lo creamos
        if (arteASCII == 0) {
                arteASCII = new char * [f];


                arteASCII[0]= new char [f*c]; //Primera columna que apunta al array

                //Enlazamos desde la posicion 1 al final
                for (int i=1; i< f; i++) {
                        arteASCII [i] = arteASCII [i-1] + c;
                }

                //asignar valor
                for (int i=0; i<f; i++)
                        for (int j=0; j<c; j++)
                                arteASCII[i][j] = 0;
        }
}


int main(){
        // const char * grises = "@#%xo;:,. ";
        const char * grises = "#$:. ";

        char ** arteASCII=0;

        Imagen origen;
        int cardinal = 0;

        //Obtenemos el cardinal
        do{
          cardinal++;
        }while(grises[cardinal]!= ' ');

        cardinal++; //añadimos el ultimo caracter /n para que el tamaño sea correcto
        cout<<cardinal;

        // Leer la imagen gio.pgm
        if (!origen.leerImagen("imagenes/gio.pgm")) {
                cerr << "error leyendo imagenes/gio.pgm\n";
                return 1;
        }

        crear(arteASCII,origen.filas(),origen.columnas()); //Reservamos espacio para la matriz arteASCII

        cout << "\nLa imagen en arte ASCII es:\n";
        if(origen.aArteASCII(grises,arteASCII,4501))
              imprimir(arteASCII,origen.filas(),origen.columnas());
        else
                cout << "La conversion no ha sido posible" << endl;


        // cout << "Ahora Forzamos que no quepa. Debe aparecer un mensaje de error\n";
        // if(origen.aArteASCII(grises, arteASCII,4199))
        //         imprimir(arteASCII,origen.filas(),origen.columnas());
        // else
        //         cout << "La conversion no ha sido posible" << endl;

        if (arteASCII[0] != 0) //Si fila de filas * columnas no esta vacia
                delete [] arteASCII [0];  //Borramos la primera fila

        if (arteASCII != 0)
                delete [] arteASCII;

        arteASCII = 0;
}
