#include <iostream>
#include <imagen.h>
#include <fstream>

using namespace std;

/**
   Crear un programa arteASCII que pida al usuario el nom-
   bre de la imagen de entrada, el conjunto de caracteres para realizar la
   ́ y escriba en pantalla la imagen convertida a arte ASCII
 */
int main(){
        const int TAMANIO_MAX = 500*500;
        char nombreFichero [100];

        char arteASCII[TAMANIO_MAX]; // 4500 + el \0
        const int maxlong =TAMANIO_MAX;

        cout<<"\nIntroduzca el nombre de la imagen de entrada."<<endl;
        cout<<"\nSi la imagen no esta en este directorio introducir en el formato: directorio/nombreImagen.extension"<<endl;
        //cin.getline(nombreFichero,50);

        Imagen origen;

        // Leer la imagen gio.pgm
        if (!origen.leerImagen("imagenes/gio.pgm")) {
                cerr << "error leyendo imagenes/"<<nombreFichero<<"\n";
                return 1;
        }

        cout << "\nLa imagen en arte ASCII es:\n";

        if(origen.leeraArteASCII("grises.txt","arteASCII",maxlong))
                cout << arteASCII;
        else
                cout << "La conversion no ha sido posible" << endl;

}
