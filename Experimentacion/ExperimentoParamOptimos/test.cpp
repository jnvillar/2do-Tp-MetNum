#include "../../Matriz/parser.cpp"
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */


vector<float> sumarVectores(vector<float> v1, vector<float> v2)
{
  vector<float> res;
  for (int i = 0; i < v1.size(); i++)
  {
    res.push_back(v1[i] + v2[i]);
  }
  return res;
}

vector<float> dividirVector(vector<float> v, float divisor)
{
  vector<float> res;
  for (int i = 0; i < v.size(); i++)
  {
    res.push_back(v[i]/divisor);
  }
  return res;
}

void imprimirMatConf(ostream &salida, vector<vector<float> > v){
  salida << "MatConf: " << endl;
  for (int i = 0; i < v.size(); ++i){
    salida << "[";
    for (int j = 0; j < v[i].size(); ++j){
      salida <<  v[i][j] <<",";   
    }
    salida << "]" << endl;  
  }
}

//Parametros optimos Vecinos=5 metoPot=20 K-cross= 5 a 7 aprox cant_autovectores_pls = ?? cant_autovectores_pca = ??   

int main(int argc, char* argv[]){
  if (argc != 9 && argc != 7){
    cout << "USO:" << endl;
    cout << "PSA: " << argv[0] << " pca [INPUT FILE] [OUTPUT FILE] [CANT DE IMAGENES] [CANT DE AUTOVECTORES] [CANTIDAD ITERACIONES METODO POTENCIA] [CANTIDAD VECINOS] [K]" << endl;
    cout << "PLS: " << argv[0] << " pls [INPUT FILE] [OUTPUT FILE] [CANT DE IMAGENES] [CANT DE ITERACIONES PLS] [CANTIDAD ITERACIONES METODO POTENCIA] [CANTIDAD VECINOS] [K]" << endl;
    cout << "KNN: " << argv[0] << " knn [INPUT FILE] [OUTPUT FILE] [CANT DE IMAGENES] [CANTIDAD VECINOS] [K]" << endl;
    return 0;
  }


  ofstream myfile(argv[3]);

  if (myfile.is_open())
  {
    //Si queremos una única ejecución con una cantidad exacta de imagenes descomentar estas dos lineas
    // int total_imag = atoi(argv[4]) + 1;
    // int cantIm = atoi(argv[4]);
    
    int total_imag = atoi(argv[4]);
    int cantIm = 200;
    int k;
    while (cantIm < total_imag)
    {

      float hR = 0;
      vector<float> precision(11, 0);
      vector<float> recall(11, 0);
      vector<float> f1Score(11, 0);
      vector< vector<float> > matrizConf;

      if(strcmp(argv[1],"pca") == 0)
      {
        //Parseo del archivo que contiene las imagenes
        cout << "Parseo imagenes\n";
        Matriz imagenes = parser(argv[2],cantIm);
        //Copio a cantAutov la cantidad de componentes a considerar (autovectores)
        int cantAutov = atoi(argv[5]);
        //Copio a cantIterMetPot la cantidad de iteraciones para el método de las potencias
        int cantIterMetPot = atoi(argv[6]);
        //Copio a cantVecinos la cantidad de vecinos para kNN
        int cantVecinos = atoi(argv[7]);
        //Copio a k la cantidad de particiones del train
        k = atoi(argv[8]);

        cout << "PCA: cantidad imagenes = " << cantIm << "\n";
        cout << "     cantidad de autovectores = " << cantAutov << "\n";
        cout << "     cantidad iteraciones MP = " << cantIterMetPot << "\n";
        cout << "     cantidad vecinos = " << cantVecinos << "\n";
        cout << "     cantidad de particiones del train (k) = " << cantVecinos << "\n";
        
        int tamConj = cantIm/k;

        for(int i = 0; i<k; i++)
        {
          //Hacemos la particion del conjunto de imagenes
          cout << "Subconjunto de test " << i+1 << "\n";
          Matriz test = imagenes.subMatriz(i*tamConj,(i+1)*tamConj);
          Matriz train = imagenes.subMatriz(0,i*tamConj,(i+1)*tamConj,cantIm);
          //Aplicamos pca con kNN
          cout << "Aplico PCA y luego kNN\n";
          pair< vector< vector<float> >, vector< vector<float> > > res = usarPca2(train,test,cantAutov,cantIterMetPot,cantVecinos);
          cout << "Sumo resultados para calcular metricas finales\n";
          precision = sumarVectores(precision, res.first[0]);
          recall = sumarVectores(recall, res.first[1]);
          f1Score = sumarVectores(f1Score, res.first[2]);
          hR += res.first[3][0];
          matrizConf = res.second;
        }

      }
      else if (strcmp(argv[1],"pls") == 0)
      {
        //Parseo del archivo que contiene las imagenes
        cout << "Parseo imagenes\n";
        Matriz imagenes = parser(argv[2],cantIm);
        //Copio a cantIterPls la cantidad de componentes a considerar (autovectores)
        int cantIterPls = atoi(argv[5]);
        //Copio a cantIterMetPot la cantidad de iteraciones para el método de las potencias
        int cantIterMetPot = atoi(argv[6]);
        //Copio a cantVecinos la cantidad de vecinos para kNN
        int cantVecinos = atoi(argv[7]);
        //Copio a k la cantidad de particiones del train
        k = atoi(argv[8]);

        cout << "PLS: cantidad imagenes = " << cantIm << "\n";
        cout << "     cantidad de iteraciones PLS = " << cantIterPls << "\n";
        cout << "     cantidad iteraciones MP = " << cantIterMetPot << "\n";
        cout << "     cantidad vecinos = " << cantVecinos << "\n";
        cout << "     cantidad de particiones del train (k) = " << cantVecinos << "\n";

        int tamConj = cantIm/k;

        for(int i = 0; i<k; i++)
        {
          //Hacemos la particion del conjunto de imagenes
          cout << "Subconjunto de test " << i+1 << "\n";
          Matriz test = imagenes.subMatriz(i*tamConj,(i+1)*tamConj);
          Matriz train = imagenes.subMatriz(0,i*tamConj,(i+1)*tamConj,cantIm);
          //Aplicamos pls con kNN
          cout << "Aplico PLS y luego kNN\n";
          pair< vector< vector<float> >, vector< vector<float> > > res = usarPls2(train,test,cantIterPls,cantIterMetPot,cantVecinos);
          cout << "Sumo resultados para calcular metricas finales\n";        
          precision = sumarVectores(precision, res.first[0]);
          recall = sumarVectores(recall, res.first[1]);
          f1Score = sumarVectores(f1Score, res.first[2]);
          hR += res.first[3][0];
          matrizConf = res.second;
        }

      } 
      else if (strcmp(argv[1],"knn") == 0)
      {

        //Parseo del archivo que contiene las imagenes
        cout << "Parseo imagenes\n";
        Matriz imagenes = parser(argv[2],cantIm);
        //Copio a cantVecinos la cantidad de vecinos para kNN
        int cantVecinos = atoi(argv[5]);
         //Copio a k la cantidad de particiones del train
        k = atoi(argv[6]);

        cout << "kNN: cantidad imagenes = " << cantIm << "\n";
        cout << "     cantidad vecinos = " << cantVecinos << "\n";
        cout << "     cantidad de particiones del train (k) = " << cantVecinos << "\n";

        int tamConj = cantIm/k;

        for(int i = 0; i<k; i++)
        {
          //Hacemos la particion del conjunto de imagenes
          cout << "Subconjunto de test " << i+1 << "\n";
          Matriz test = imagenes.subMatriz(i*tamConj,(i+1)*tamConj);
          Matriz train = imagenes.subMatriz(0,i*tamConj,(i+1)*tamConj,cantIm);
          //Aplicamos kNN
          cout << "Aplico kNN\n";
          pair< vector< vector<float> >, vector< vector<float> > > res = usarKnn2(train,test,cantVecinos);
          cout << "Sumo resultados para calcular metricas finales\n";
          precision = sumarVectores(precision, res.first[0]);
          recall = sumarVectores(recall, res.first[1]);
          f1Score = sumarVectores(f1Score, res.first[2]);
          hR += res.first[3][0];
          matrizConf = res.second;
        }

      }

      //Divido todas las sumas por k para calcular promedio e imprimio por std output
      cout << "Divido la suma de los resultados para calcular el promedio final\n";
      hR = hR/(float) k;
      cout << "HitRate: " << hR << endl;
      myfile << "HitRate: " << hR << "\n";
      precision = dividirVector(precision, k);
      for (int i = 0; i < precision.size(); i++)
      {
        if (i != precision.size() - 1)
        {
          cout << "Precision de " << i << ": " << precision[i] << "\n";
          myfile << "Precision de " << i << ": " << precision[i] << "\n";
        }
        else
        {
          cout << "Precision promedio: " << precision[i] << "\n";
          myfile << "Precision promedio: " << precision[i] << "\n";
        }
      }
      recall = dividirVector(recall, k);
      for (int i = 0; i < recall.size(); i++)
      {
        if (i != recall.size() - 1)
        {
          cout << "Recall de " << i << ": " << recall[i] << "\n";
          myfile << "Recall de " << i << ": " << recall[i] << "\n";
        }
        else
        {
          cout << "Recall promedio: " << recall[i] << "\n";
          myfile << "Recall promedio: " << recall[i] << "\n";
        }
      }
      f1Score = dividirVector(f1Score, k);
      for (int i = 0; i < f1Score.size(); i++)
      {
        if (i != f1Score.size() - 1)
        {
          cout << "F1-score de " << i << ": " << f1Score[i] << "\n";
          myfile << "F1-score de " << i << ": " << f1Score[i] << "\n";
        }
        else
        {
          cout << "F1-score promedio: " << f1Score[i] << "\n";
          myfile << "F1-score promedio: " << f1Score[i] << "\n";
        }
      }

      imprimirMatConf(cout, matrizConf);
      imprimirMatConf(myfile, matrizConf);

      cantIm += 200; 
    }
    myfile.close();
  }
  else cout << "No se pudo abrir " << argv[3] << "\n";

  return 0;  

}