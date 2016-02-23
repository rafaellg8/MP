#include<iostream>
#include<string>
using namespace std;
struct Producto
{
 string nombre;
 int peso; // en gramos
 float precio_kg;
};
struct Compra
{
 static const int MAX = 10;
 Producto lista[MAX];
};
// función para devolver los datos de un producto como un string
string productoToString(Producto a)
{
 string rta;
 rta = a.nombre + "\t\t" + to_string(a.peso) + "\t" + to_string(a.precio_kg);
 return rta;
}


// crea una variable de tipo Producto y la devuelve
Producto creaProducto(string nombre, int peso, float precio) {
  //Creamos un producto
  Producto producto;
  //Inicializamos
  producto.nombre=nombre;
  //Pasamos el peso a Kg
  producto.peso=peso;
  producto.precio_kg = precio;

  return producto;
}

// incrementa el precio de cada producto en un k %
void incrementarPrecios(Compra & c, int k)
{
  //Recorremos la lista de la compra y multiplicamos %
  for (int i=0;i<10;i++){
    c.lista[i].precio_kg=c.lista[i].precio_kg*(k*0.01)+c.lista[i].precio_kg;
  }
}
// muestra el listado de productos comprados
void listarCompra(const Compra & c)
{
  for (int i=0;i<10;i++){
    cout<<productoToString(c.lista[i])<<endl;
  }
}
// función que devuelve el importe total de la compra (sinIVA) y su peso (en kgs)
void obtenerImporteYPeso(const Compra & c, float & precio, int & peso)
{
  peso=0;
  precio=0;
  for (int i = 0; i < 10; i++) {
    //Pasamos de gramos a Kg
    precio+=c.lista[i].precio_kg*((float)c.lista[i].peso/1000);
    peso+=c.lista[i].peso;
  }

  peso = (float(peso/1000));
}

//Función auxiliar que devuelve el precio de la compra sin IVA
void obtenerImporte(const Compra & c, float & precio){
  precio=0;
  for (int i = 0; i < 10; i++) {
    //Pasamos de gramos a Kg
    precio+=c.lista[i].precio_kg*((float)c.lista[i].peso/1000);
  }
}

// función que muestra el "ticket" de compra según el formato sugerido
void mostrarTicketCompra(const Compra & c)
{
  listarCompra(c);
  float precioSinIVA;
  obtenerImporte(c,precioSinIVA);
  cout<<"\nSubtotal :"<<precioSinIVA<<endl;

  //IVA sobre el 21%
  const float IVA = 0.21;
  float total = (precioSinIVA*IVA)+precioSinIVA;
  cout<<"\nIVA (21%): " <<precioSinIVA*IVA;
  cout<<"\nTotal : "<<total<<endl;
}

int main()
{
 const int TAM = 10;
 Producto actual;
 Compra mi_compra;
 float precio;
 int peso;
 string nombre;
 for(int i = 0; i < TAM; i++)
 {
cin >> nombre >> peso >> precio;
mi_compra.lista[i] = creaProducto(nombre, peso, precio);
 }
 // se muestra la lista de productos.
 cout << "\n ******** Prueba de funcion listarCompra ******** \n";
 listarCompra(mi_compra);
 // se muestra el importe total de la compra y el peso
 cout << "\n ******** Prueba de funcion obtenerImporteYPeso ******** \n";
 obtenerImporteYPeso(mi_compra, precio, peso);
 cout << "\nEl importe de la compra es: " << precio << ", su compra pesa:"
<< peso << " Kg. " << endl;
 // se muestra el ticket de la compra.
 cout << "\n ******** Prueba de la funcion mostrarTicketCompra ******** \n";
 mostrarTicketCompra(mi_compra);
 cout << "\n ******** Prueba de la funcion incrementarPrecio ********";
 incrementarPrecios(mi_compra, 10);
 cout << "\n ******** y listarCompra de nuevo \t\t********\n\n";
 listarCompra(mi_compra);
 return(0);
}
