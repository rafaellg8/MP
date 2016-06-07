#include <string>
#include <fstream>
#include <iostream>
#include "lista.h"

using namespace std;

void Lista::inicializar(){
  cabecera=new Celda;
  cabecera->datos="";
  cabecera->siguiente=0;
  num_elementos=0;
}
Lista::Lista(){ //Creamos una lista vacia de un solo elemento
        cabecera=new Celda;
        cabecera->datos="";
        cabecera->siguiente=0;
        num_elementos=0;
}

Lista::~Lista(){
        if(cabecera!=0) {
                destruir();
        }
}

Lista::Lista(string valor){
        cabecera=new Celda;
        cabecera->datos="";
        Celda *nueva=new Celda();
        nueva->datos=valor;
        nueva->siguiente=0;
        cabecera->siguiente=nueva;
        num_elementos=1;

}

Lista::Lista(const Lista & otra){
  this->cabecera=0; //Llamamos desde el constructor inicializamos
  this->copiar(otra);
}

Lista & Lista::operator = (const Lista & otra){
  this->copiar(otra);
  return *this;
}

Lista & Lista::operator + (const string str){
  insertar(str);
  return *this;
}
void Lista::copiar(const Lista & otra){
  if (otra.cabecera != 0){
    this->destruir();
    this->inicializar();
    for (int i=0;i<otra.longitud();i++){
      this->insertar(otra.getCelda(i));
    }
  }
}

void Lista::destruir(){
        if(cabecera!=0) {
                Celda *actual=cabecera;
                while(actual->siguiente!=0) {
                        Celda *sig = actual->siguiente;
                        //TODO Hace falta est en destruir
                        //cerr << actual << "  " << actual->datos << " " << actual->siguiente << endl;
                        delete actual;
                        actual=sig;
                }
                //cerr << actual << "  " << actual->datos << " " << actual->siguiente << endl;
                delete actual;
                cabecera=0;
                num_elementos=0;
        }
}

void Lista::insertar(string valor){
    if (cabecera == 0){ //Comprobamos si la lista esta vacia directamente inicializamos e insertamos
      this->inicializar();
      cabecera->datos=valor;
    }
    else{
        Celda *nueva=new Celda;
        Celda *ultima=cabecera;
        nueva->datos=valor;
        nueva->siguiente=0;
        if (ultima->siguiente!=0)
          while(ultima->siguiente!=0) {
                ultima=ultima->siguiente;
          }
        ultima->siguiente=nueva;
      }
        num_elementos++;

}

string Lista::getCelda(int pos) const {
    if (cabecera!=0 && pos<=longitud()){
        Celda *actual=cabecera;
        int contador=0;
        while(contador<=pos) {
                actual=actual->siguiente;
                contador++;
        }
        return actual->datos;
      }
      else{
        return string("");
      }
}

int Lista::longitud() const {
        return num_elementos;
}

bool Lista::esNula() const{
  return (this->cabecera->datos== "" && this->num_elementos != 0);
}

/**
 * @brief Construye una lista de celdas enlazadas a partir de la informacion
 * contenida en un fichero.
 * @param nombreFichero ruta del fichero de texto con el contenido de las datoss
 * a insertar en la lista
 * @retval true si ha tenido éxito en la lectura y el formato es el correcto
 * @retval false si se ha producido algún error en la lectura
 *
 * Lee desde disco los elementos almacenados en @a nombreFichero y los guarda
 * en la lista. La función debe asegurarse de que la estructura sigue un patron
 * determinado, y se ha de crear la lista con el numero de elementos que contenga.
 */
bool Lista::leerLista(const char nombrefichero[]){
        ifstream fin;
        fin.open(nombrefichero);
        if(!fin) {
                return false;
        }else{
                string grises;
                int lineas;
                getline(fin,grises); //la primera linea se ignora
                fin >> lineas; //leo el numero de datos de grises
                getline(fin,grises); //leer salto de linea
                if (!fin) {
                        return false;
                }else {
                        int i = 0;
                        getline(fin,grises); //leer cadena de caracteres
                        while ((i < lineas)&&(fin)) {
                                if (grises != "") {
                                        insertar(grises);
                                        i++;
                                }
                                getline(fin,grises); //leer cadena de caracteres
                        }
                }
                fin.close();
        }
        return true;
}

void Lista::imprimir() const {
        int tamanio = this->longitud();
        for (int i=0; i<tamanio; i++) {
                std::cout<<this->getCelda(i)<<std::endl;
        }
}

ostream & operator << (ostream & out,const Lista & lista){
        std::cout<<"\n++++++++++++++++++++++++++++"<<std::endl;
        std::cout<<"\nImprimiendo lista de grises"<<std::endl;
        std::cout<<"\nLista de longitud : "<<lista.longitud()<<std::endl;
        lista.imprimir();
        std::cout<<"\n++++++++++++++++++++++++++++"<<std::endl;
        return out;
}
