#include "../../Matriz/parser.cpp"
#include <stdio.h>
#include <string.h>
#include <fstream>


vector<float> sumarVectores(vector<float> v1, vector<float> v2)
{
  vector<float> res;
  for (int i = 0; i < v1.size(); i++)
  {
    res.push_back(v1[i] + v2[i]);
  }
  return res;
}

vector<float> dividirVector(vector<float> v, int divisor)
{
  vector<float> res;
  for (int i = 0; i < v.size(); i++)
  {
    res.push_back(v[i]/(float ) divisor);
  }
  return res;
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


  ofstream myfile (argv[3]);

  if (myfile.is_open())
  {

    int total_imag = atoi(argv[4]);
    int cantIm = 500;
    int k;
    while (cantIm < total_imag)
    {

      float hR = 0;
      vector<float> precision(11, 0);
      vector<float> recall(11, 0);
      vector<float> f1Score(11, 0);

      if(strcmp(argv[1],"pca") == 0)
      {
        //Parseo del archivo que contiene las imagenes 
        Matriz imagenes = parser(argv[2],cantIm);
        //Copio a cantAutov la cantidad de componentes a considerar (autovectores)
        int cantAutov = atoi(argv[5]);
        //Copio a cantIterMetPot la cantidad de iteraciones para el método de las potencias
        int cantIterMetPot = atoi(argv[6]);
        //Copio a cantVecinos la cantidad de vecinos para kNN
        int cantVecinos = atoi(argv[7]);
        //Copio a k la cantidad de particiones del train
        k = atoi(argv[8]);

        int tamConj = cantIm/k;

        for(int i = 0; i<k; i++)
        {
          //Hacemos la particion del conjunto de imagenes
          Matriz test = imagenes.subMatriz(i*tamConj,(i+1)*tamConj); 
          Matriz train = imagenes.subMatriz(0,i*tamConj,(i+1)*tamConj,cantIm);
          //Aplicamos pca con kNN
          vector< vector<float> > res = usarPca2(train,test,cantAutov,cantIterMetPot,cantVecinos);
          precision = sumarVectores(precision, res[0]);
          recall = sumarVectores(recall, res[1]);
          f1Score = sumarVectores(f1Score, res[2]);
          hR += res[3][0];
        }

      }
      else if (strcmp(argv[1],"pls") == 0)
      {
        //Parseo del archivo que contiene las imagenes 
        Matriz imagenes = parser(argv[2],cantIm);
        //Copio a cantIterPls la cantidad de componentes a considerar (autovectores)
        int cantIterPls = atoi(argv[5]);
        //Copio a cantIterMetPot la cantidad de iteraciones para el método de las potencias
        int cantIterMetPot = atoi(argv[6]);
        //Copio a cantVecinos la cantidad de vecinos para kNN
        int cantVecinos = atoi(argv[7]);
        //Copio a k la cantidad de particiones del train
        k = atoi(argv[8]);

        int tamConj = cantIm/k;

        for(int i = 0; i<k; i++)
        {
          //Hacemos la particion del conjunto de imagenes
          Matriz test = imagenes.subMatriz(i*tamConj,(i+1)*tamConj);
          Matriz train = imagenes.subMatriz(0,i*tamConj,(i+1)*tamConj,cantIm);
          //Aplicamos pls con kNN
          vector< vector<float> > res = usarPls2(train,test,cantIterPls,cantIterMetPot,cantVecinos);
          precision = sumarVectores(precision, res[0]);
          recall = sumarVectores(recall, res[1]);
          f1Score = sumarVectores(f1Score, res[2]);
          hR += res[3][0];
        }

      } 
      else if (strcmp(argv[1],"knn") == 0)
      {
        //Parseo del archivo que contiene las imagenes 
        Matriz imagenes = parser(argv[2],cantIm);
        //Copio a cantVecinos la cantidad de vecinos para kNN
        int cantVecinos = atoi(argv[5]);
         //Copio a k la cantidad de particiones del train
        k = atoi(argv[6]);

        int tamConj = cantIm/k;

        for(int i = 0; i<k; i++)
        {
          //Hacemos la particion del conjunto de imagenes
          Matriz test = imagenes.subMatriz(i*tamConj,(i+1)*tamConj);
          Matriz train = imagenes.subMatriz(0,i*tamConj,(i+1)*tamConj,cantIm);
          //Aplicamos kNN
          vector< vector<float> > res = usarKnn2(train,test,cantVecinos);
          precision = sumarVectores(precision, res[0]);
          recall = sumarVectores(recall, res[1]);
          f1Score = sumarVectores(f1Score, res[2]);
          hR += res[3][0];
        }

      }

      //Divido todas las sumas por k para calcular promedio e imprimio por std output
      hR = hR/(float) k;
      cout << "HitRate: " << hR << endl;
      precision = dividirVector(precision, k);
      for (int i = 0; i < precision.size(); i++)
      {
        if (i != precision.size() - 1)
          cout << "Precision de " << i << ": " << precision[i] << "\n";
        else
          cout << "Precision promedio: " << precision[i] << "\n";
      }
      recall = dividirVector(recall, k);
      for (int i = 0; i < recall.size(); i++)
      {
        if (i != recall.size() - 1)
          cout << "Recall de " << i << ": " << recall[i] << "\n";
        else
          cout << "Recall promedio: " << recall[i] << "\n";
      }
      f1Score = dividirVector(f1Score, k);
      for (int i = 0; i < f1Score.size(); i++)
      {
        if (i != f1Score.size() - 1)
          cout << "F1-score de " << i << ": " << f1Score[i] << "\n";
        else
          cout << "F1-score promedio: " << f1Score[i] << "\n";
      }
      cantIm += 500; 
    }
    myfile.close();
  }
  else cout << "No se pudo abrir " << argv[3] << "\n";

  return 0;  

}