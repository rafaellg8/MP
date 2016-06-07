/**
 * lee cualquier imagen indicada por el usuario y un fichero con cadenas
 * de caracteres y crea ficheros de imagen transformadas, una por cadena
 */
#include <iostream>
#include <cstring>
#include "imagen.h"
#include "lista.h"

using namespace std;


int main(int argc,char *argv[]){
								if (argc != 3) { //nombre programa nombre imagen y nombre grises
																cout<<"\nError al leer archivos en main, formato: imagen.pgm grises.txt"<<endl;
																return 1;
								}
								else{
																const char * ficheroGrises = argv[2];
																const char * ficheroImagen = argv[1];

																Imagen origen;
																Lista celdas;

																// Leer la imagen desde fichero
																if (!origen.leerImagen(ficheroImagen)) {
																								cerr << "Error leyendo imagen " << ficheroImagen << endl;
																								return 1;
																}

																// Leer cadenas desde fichero
																if (celdas.leerLista(ficheroGrises)) {
																		cout<<celdas<<endl;
																								// realizar las conversiones
																								if (origen.listaAArteASCII(celdas)) {
																																cout << "Exito en la conversion." << endl;
																																cout << "Chequee los ficheros asciiX.txt" << endl;
																																cout << endl;
																								}else{
																																cerr << "La conversion no ha sido posible" << endl;
																																cerr << endl;
																								}
																								//celdas.destruir(); // liberar memoria listas
																}else{
																								cerr << "Error lista de grises " << ficheroGrises << endl;
																}

								} //Cerramos else de si el numero de parametros de la interfaz es distinto de 3

}
