/* Programa que calcula un c�rculo con centro en medio de dos c�rculos y radio la mitad de la distancia.
   Tambi�n calcula su �rea.

   Author: MP
   M�dulo no definitivo (creado para ser modificado)

   Un ejemplo de ejecuci�n es:
     Introduzca un circulo en formato radio-(x,y): 3-(0,0)
     Introduzca otro circulo: 4-(5,0)
     El c�rculo que pasa por los dos centros es: 2.5-(2.5,0)
	 Su area es: 19.63
**/

#include <iostream>
#include <cmath>
#include <stdlib.h>
using namespace std;

// Definici�n de las estructuras
struct Punto {
    double x;
    double y;
};

struct Circulo {
    Punto centro;
    double radio;
};

// Prototipos de las funciones
void EscribirPunto(const Punto &p);
Punto LeerPunto();
double DistanciaPuntos(const Punto &p1, const Punto &p2);
Punto PuntoMedio(const Punto &p1, const Punto &p2);

void EscribirCirculo(const Circulo &c);
Circulo LeerCirculo();
double AreaCirculo(const Circulo &c);

// Programa principal
int main()
{
    Circulo c1,c2, c3;

    do {
        cout << "Introduzca un circulo en formato radio-(x,y): ";
        c1 = LeerCirculo();

        cout << "Introduzca otro circulo: ";
        c2 = LeerCirculo();
    } while ( DistanciaPuntos (c1.centro,c2.centro) == 0 );

    c3.centro = PuntoMedio( c1.centro, c2.centro );

    c3.radio = DistanciaPuntos( c1.centro, c2.centro ) / 2;

    cout << "El circulo que pasa por los dos centros es: ";
	EscribirCirculo( c3 );
    cout << endl << "Su area es: " << AreaCirculo( c3 ) << endl;
}

// Implementaci�n de las funciones
void EscribirPunto(const Punto &p)
{
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
/* Fin: circulomedio.cpp */
