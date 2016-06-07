#include "imagen.h"
#include <iostream>
using namespace std;

int main(){
  Imagen origen();
  Imagen destino(100,100);
  origen.leerImagen("imagenes/giotexto.pgm");
}
