/*
   Haz un programa que lea una serie de n´umeros enteros (como m´aximo 100) y que elimine
   los elementos repetidos guard´andolos en un nuevo array. Debe contener funciones para
   leer los elementos de un array, imprimirlo y eliminar los elementos repetidos. Haz una
   segunda versi´on de la funci´on para eliminar los elementos repetidos de forma que la
   eliminaci´on se haga sobre el mismo array de entrada, sin usar un segundo array auxiliar.
   Las funciones implementadas se probar´an desde main.
 */
#include <iostream>
using namespace std;

/**Quicksort**/
// Función para dividir el array y hacer los intercambios
int divide(int *array, int start, int end) {
        int left;
        int right;
        int pivot;
        int temp;

        pivot = array[start];
        left = start;
        right = end;

        // Mientras no se cruzen los índices
        while (left < right) {
                while (array[right] > pivot) {
                        right--;
                }

                while ((left < right) && (array[left] <= pivot)) {
                        left++;
                }

                // Si todavía no se cruzan los indices seguimos intercambiando
                if (left < right) {
                        temp = array[left];
                        array[left] = array[right];
                        array[right] = temp;
                }
        }

        // Los índices ya se han cruzado, ponemos el pivot en el lugar que le corresponde
        temp = array[right];
        array[right] = array[start];
        array[start] = temp;

        // La nueva posición del pivot
        return right;
}

// Función recursiva para hacer el ordenamiento
void quicksort(int *array, int start, int end)
{
        int pivot;

        if (start < end) {
                pivot = divide(array, start, end);

                // Ordeno la lista de los menores
                quicksort(array, start, pivot - 1);

                // Ordeno la lista de los mayores
                quicksort(array, pivot + 1, end);
        }
}

/**
   Leer elementos de un array
   @return Numero de valores utiles
*/
int readArray(int array[]){
        int contador=0;
        int aux;
        int nutil;
        nutil = -1;
        do {
                cout<<"\nIntroduzca un entero como valor, sino -1 para finalizar"<<endl;
                cin >> aux;
                array[contador]=aux;
                nutil=contador;
                contador++;
        } while((contador<10) && (aux>0));

        //Si se rellena el array entero, modificamos el numero de utiles
        if (nutil == 9 && array[9]!=-1)
          nutil = 10;

        return nutil;
}

void printArray(int array[],int nutil){
        if (nutil==0) {
                cout<<"\nArray vacío"<<endl;
        }

        else{
                for (int i=0; i<nutil; i++)
                        cout<<array[i]<<" ";
        }
        cout<<endl;
}

/**
   Borra repeticiones
   @param repe array repetidos
   @return nutil
 **/
int deleteRepeats(int array[],int nutil,int repe[]){
        if (nutil==0) {
                cout<<"\nArray vacío"<<endl;
        }
        else{
                int aux; //Guardo valor comprobar repetido
                int pos; //Posicion valor repetido
                int pos_repe=0; //Contador para el array de repetidos
                //A lo bestia 0 (n^n). Recorremos el vector entero
                for (int i=0; i<nutil; i++) {
                        aux=array[i];
                        pos=i;
                        for (int j=0; j<nutil; j++) {
                                if (array[j]==aux && j!=pos) {
                                        //Elimino ese valor
                                        array[i]=0;
                                        repe[pos_repe]=aux;
                                        pos_repe++;
                                }
                        }
                }
        }
        return nutil;
}


int main(){
        const int MaxSize = 100;
        int array [MaxSize];
        int nutil;
        nutil = readArray(array);
        cout<<nutil;
        printArray(array,nutil);
        int repe [MaxSize];
        nutil = deleteRepeats(array,nutil,repe);
        cout<<nutil<<endl;
        printArray(array,nutil);
        return 0;
}
