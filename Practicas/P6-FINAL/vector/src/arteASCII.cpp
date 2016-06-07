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
        char nombreSalida [100];
        const int maxlong = TAMANIO_MAX;

        cout<<"\nIntroduzca el nombre de la imagen de entrada."<<endl;
        cout<<"\nSi la imagen no esta en este directorio introducir en el formato: directorio/nombreImagen.extension"<<endl;
        cin.getline(nombreFichero,99);

        Imagen origen;

        // Leer la imagen gio.pgm
        if (!origen.leerImagen(nombreFichero)) {
                cerr << "error leyendo imagenes/"<<nombreFichero<<"\n";
                return 1;
        }

        //Leemos el nombre del fichero de salida
        cout<<"\nIntroduzca el nombre del fichero de salida"<<endl;
        cin.getline(nombreSalida,99);
        if(origen.leeraArteASCII("grises.txt",nombreSalida,maxlong))
                cout << "\nFicheros creados correctamente, busque los : "<<nombreSalida<<".txt"<<endl;
        else
                cout << "La conversion no ha sido posible" << endl;

}
