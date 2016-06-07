/**
@file main.cpp
@brief 
@author Rafael Lachica Garrido
GRUPO 18
DNI 76655442F

Universidad de Granada
Metodología de la Programación I
Examen de laboratorio 

Por favor, rellene las funciones que se indican
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;

/**
@brief Imprime el contenido de un vector de string
@param v 	Vector de string
@param n	Número de elementos que contiene @a v
*/
void imprimirVector(string *v, int n)  {
	cout << n << " elementos" << endl;

	for (int i=0; i<n; i++)
		cout << "["<<i<<"] = " << v[i] << endl;
}


/*
@brief Lee un fichero y llama al constructor de frutas
@param nombreFichero 
@param elem numero de elementos que contiene
@return devuelve un array de tipo string
*/	
string * leerVector(const char * nombreFichero, int &elem){
	string * array;	
	ifstream fi;	
	fi.open(nombreFichero);
	
	int numeroElementos=0;
	fi>>numeroElementos; //Leemos el numero de elementos del fichero
	elem = numeroElementos; //Guardamos el numero de elementos

	array = new string [numeroElementos]; //Reservamos memoria
	string fruta;

	for (int i=0;i<numeroElementos;i++){
		fi>>fruta;
		array[i]=fruta;			
	}
	
	fi.close(); //Cerramos el fichero

	return array;
}

/*
@brief Complementario
@param A string A
@param elemA numero elementos de A
@param B string B
@return resultado con el string de complementarios
*/
string * complementario(string * A,int elemA, string * B, int elemB,int &tamanioResultado){
	string * resultado;
	int tamanioFinal = 0; //Tamanio final del vector resultado
	string * auxiliar; //Vector auxiliar que guardaremos los que vayamos encontrando
	auxiliar = new string [elemB]; //Como mucho coinciden todos los elementos	

		
	int j =0; //contador

	bool	esta = false; //Si lo encontramos paramos y saltamos a otra iteracion
	for (int i=0;i<elemB;i++){ //Recorro los elementos de B
		esta = false;
		while(!esta && j<elemA){ //Mientras no este y no se pase de elementos de A
			if (B[i] == A[j]){
				esta = true; //Esta no hacemos nada salimos del bucle
			}
			j++;
		}
		if (!esta) {//Si no esta lo aniadimos
			auxiliar[tamanioFinal]=B[i];
			tamanioFinal++;
			cout<<"\nAniado "<<B[i]<<endl;
		}
		j=0; //Para volver al principio del otro array y vuelta a empezar

	}


	//Copiamos el resultado final
	resultado = new string[tamanioFinal];
	for (int i=0;i<tamanioFinal;i++)
		resultado[i]=auxiliar[i];

	delete []auxiliar; //Liberamos memoria del vector que ya no necesitamos
	
	tamanioResultado = tamanioFinal; //tamanio del resultado que devolvemos
	
	return resultado;
	
}


/**
@brief Destructor
@param array array de string que queremos liberar
*/
void destructor(string * array){
	delete [] array;
	array=0;
	cout<<"\nDestructor"<<endl;
}




int main(int argc,char *argv[])  {
	string *A=NULL, *B=NULL, *Resultado=NULL;
	int elemA, elemB, elemResultado;
	
	//Si introducimos los nombres de los ficheros
	if (argc==3){
		A = leerVector(argv[1],elemA);
		B = leerVector(argv[2],elemB);		
	}

		
	else{
	/// Examen: Leer fichero en vector A
	A = leerVector("mod5A.txt",elemA);	
	B = leerVector("mod5B.txt",elemB);
	}

	imprimirVector(A,elemA);
	imprimirVector(B, elemB);

	/// Examen: Calcular resultado
	Resultado=complementario(A,elemA,B,elemB,elemResultado);
	/// Examen: Mostrar resultado
	imprimirVector(Resultado, elemResultado);

	/// Examen: Terminación del programa
	destructor(A);
	destructor(B);
	destructor(Resultado);
	return 0;
}
