#include <imagen.h>
#include <cstring>
#include <iostream>

using namespace std;

int main(int argc,char * argv[]){
        if (argc == 5) {
                Imagen lecturaA, lecturaB;

                //Leemos ImagenA
                if (!lecturaA.leerImagen(argv[1])) {
                        cerr << "error leyendo "<<argv[1]<<endl;
                        return 1;
                }

                //Leemos ImagenB
                if (!lecturaB.leerImagen(argv[2])) {
                        cerr << "error leyendo "<<argv[2]<<endl;
                        return 1;
                }

                //Probamos a crear la imagen concatenada
                try{
                  Imagen suma = (lecturaA+lecturaB);

                  if (argv[4]==string("b"))
                    suma.escribirImagen(argv[3],true);
                  else
                    suma.escribirImagen(argv[3],false);

              }
              catch (int e)
              {
                      cout << "An exception occurred. Exception Nr. " << e << '\n';
              }
        }
        else{
                cout<<"\nError en el paso de argumentos, falta alguno de ellos....."<<endl;
                cout<<"\nFormato: ./suma img1.pgm img2.pgm img_out.pgm t"<<endl;
        }

        return 0;
}
