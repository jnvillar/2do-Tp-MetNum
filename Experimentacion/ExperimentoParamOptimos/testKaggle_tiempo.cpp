#include "../../Matriz/parser.cpp"
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */


//Parametros optimos Vecinos=5 metoPot=20 K-cross= 5 a 7 aprox cant_autovectores_pls = ?? cant_autovectores_pca = ??   
int main(int argc, char* argv[]){
  if (argc != 5 && argc != 7){
    cout << "USO:" << endl;
    cout << "PSA: " << argv[0] << " pca [INPUT FILE TRAIN] [INPUT FILE TEST] [CANT DE AUTOVECTORES] [CANTIDAD ITERACIONES METODO POTENCIA] [CANTIDAD VECINOS]" << endl;
    cout << "PLS: " << argv[0] << " pls [INPUT FILE TRAIN] [INPUT FILE TEST] [CANT DE ITERACIONES PLS] [CANTIDAD ITERACIONES METODO POTENCIA] [CANTIDAD VECINOS]" << endl;
    cout << "KNN: " << argv[0] << " knn [INPUT FILE TRAIN] [INPUT FILE TEST] [CANTIDAD VECINOS]" << endl;
    return 0;
  }

  cout << "Parseo del train\n";
  Matriz train = parser(argv[2],-1);
  cout << "Parseo del test\n";
  Matriz test = parser(argv[3],-1);
  float tiempo;

  if(strcmp(argv[1],"pca") == 0)
  {

    //Copio a cantAutov la cantidad de componentes a considerar (autovectores)
    int cantAutov = atoi(argv[4]);
    //Copio a cantIterMetPot la cantidad de iteraciones para el método de las potencias
    int cantIterMetPot = atoi(argv[5]);
    //Copio a cantVecinos la cantidad de vecinos para kNN
    int cantVecinos = atoi(argv[6]);

    cout << "Comienzo PCA\n";
    //Mido el tiempo
    clock_t t;
    t = clock();
    usarPca(train, test, cantAutov, cantIterMetPot, cantVecinos);
    t = clock() - t;
    tiempo = ((float)t)/CLOCKS_PER_SEC;
  }
  else if (strcmp(argv[1],"pls") == 0)
  {

    //Copio a cantAutov la cantidad de componentes a considerar (autovectores)
    int cantIterPls = atoi(argv[4]);
    //Copio a cantIterMetPot la cantidad de iteraciones para el método de las potencias
    int cantIterMetPot = atoi(argv[5]);
    //Copio a cantVecinos la cantidad de vecinos para kNN
    int cantVecinos = atoi(argv[6]);

    cout << "Comienzo PLS\n";
    //Mido el tiempo
    clock_t t;
    t = clock();
    usarPls(train, test, cantIterPls, cantIterMetPot, cantVecinos);
    t = clock() - t;
    tiempo = ((float)t)/CLOCKS_PER_SEC;
  }
  else if (strcmp(argv[1],"knn") == 0)
  {

    //Copio a cantVecinos la cantidad de vecinos para kNN
    int cantVecinos = atoi(argv[4]);

    cout << "Comienzo kNN\n";
    //Mido el tiempo
    clock_t t;
    t = clock();
    usarKnn(train, test, cantVecinos);
    t = clock() - t;
    tiempo = ((float)t)/CLOCKS_PER_SEC;
  }

  cout << "Tiempo empleado (segundos): " << tiempo << "\n";

  return 0;

}