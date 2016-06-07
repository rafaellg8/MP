#include "lista.h"
#include <iostream>
using namespace std;

int main(){
  const char * ficheroGrises = "grises.txt";
  Lista l1;


  if (l1.leerLista(ficheroGrises))
    cout<<l1<<endl;

  Lista l2("");
  cout<<l2<<endl;

  l2 = l1;

  Lista l3 = l2;
  std::cout << l3 << std::endl;
  Lista l4 = (Lista() +"HOLA MUNDO"); //Es como si hacemos Lista l4 = l4 + ("HOLA MUNDO")
  //El problema es que da errores de la otra forma porque l4 esta sin inicializar
  std::cout <<l4<< std::endl;

  Lista l5;
  l5.insertar("HOLA");
  cout<<l5<<endl;
}
