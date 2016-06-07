#include <iostream>
#include <cmath>
#include <stdlib.h>
#include "circulo.h"
using namespace std;

void EscribirCirculo(const Circulo &p)
{
    cout<<"\nCirculo : "<<p.radio<< " - "<<"("<<p.centro.x<<","<<p.centro.y<<")"<<endl;
}

/**
Funcion que lee los puntos de un circulo
*/
Circulo LeerCirculo()
{
  //Creamos un circulo
  Circulo circulo;

  //Leemos el radio

  cin>>circulo.radio;

  //Llamada a la función LeerPunto
  Punto punto = LeerPunto();
  //Guardamos el punto en el centro
  circulo.centro = punto;

  return circulo;
}

/**
* @return area del circulo
*/
double AreaCirculo(const Circulo &c)
{
  double area;
  area = 3.141*(pow(c.radio,2));
  return area;
}
