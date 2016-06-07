#include "punto.h"
#include <iostream>
using namespace std;

// Implementaci�n de las funciones
void EscribirPunto(const Punto &p)
{
  cout<<"\nPunto coordenadas x,y: "<<p.x<< ","<<p.y<<endl;
}

/**
* Funcion que lee los puntos de una cadena
*  -(5,0) 6 caracteres
*/
Punto LeerPunto()
{
  //Guardamos la basura en este caso -(,)
  char coma;
  cin>>coma;
  cin>>coma;

  Punto p;
  cin>>p.x;
  cin>>coma;
  cin>>p.y;
  cin>>coma;
  return p;
}

/**
* @return distancia entre dos puntos
*/
double DistanciaPuntos(const Punto &p1, const Punto &p2)
{
  double d1 = p1.x+p1.y;
  double d2 = p2.x+p2.y;

  if (d1>d2)
    return (d1-d2);
  else
    return (d2-d1);
}

/**
* Calcula el punto intermedio entre dos puntos
* @param p1 Punto 1
* @param p2 Punto 2
* @return punto intermedio
*/
Punto PuntoMedio(const Punto &p1, const Punto &p2)
{
  Punto intermedio;
  intermedio.x = (p1.x+p2.x)/2;
  intermedio.y = (p1.y+p2.y)/2;

  return intermedio;
}
