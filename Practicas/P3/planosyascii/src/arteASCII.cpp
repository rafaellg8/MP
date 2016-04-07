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
  char grises[100];
  char arteASCII[TAMANIO_MAX]; // 4500 + el \0

  cout<<"\nIntroduzca el nombre de la imagen de entrada."<<endl;
  cout<<"\nSi la imagen no esta en este directorio introducir en el formato: directorio/nombreImagen.extension"<<endl;
  cin.getline(nombreFichero,50);

  cout<<"\nIntroduzca la escala de grises"<<endl;
  cin.getline(grises,97);
  //Introducimos espacio y fin de cadena
  grises[98]=' ';
  grises[99]='\0';


  Imagen origen;

  // Leer la imagen gio.pgm
  if (!origen.leerImagen(nombreFichero)) {
          cerr << "error leyendo imagenes/"<<nombreFichero<<"\n";
          return 1;
  }

  cout << "\nLa imagen en arte ASCII es:\n";
  if(origen.aArteASCII(grises, arteASCII, TAMANIO_MAX))
          cout << arteASCII;
  else
          cout << "La conversi�n no ha sido posible" << endl;

}
