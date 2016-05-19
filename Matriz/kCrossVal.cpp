#include "parser.cpp"
#include <stdio.h>
#include <string.h>






int main(int argc, char* argv[]){
	if (argc != 8 && argc != 6){
		cout << "USO:" << endl;
		cout << "PSA: " << argv[0] << " pca [INPUT FILE] [CANT DE IMAGENES] [CANT DE AUTOVECTORES] [CANTIDAD ITERACIONES METODO POTENCIA] [CANTIDAD VECINOS] [K]" << endl;
		cout << "PLS: " << argv[0] << " pls [INPUT FILE] [CANT DE IMAGENES] [CANT DE ITERACIONES PLS] [CANTIDAD ITERACIONES METODO POTENCIA] [CANTIDAD VECINOS] [K]" << endl;
		cout << "KNN: " << argv[0] << " knn [INPUT FILE] [CANT DE IMAGENES] [CANTIDAD VECINOS] [K]" << endl;
		return 0;
	}

	if(strcmp(argv[1],"pca") == 0){
		int cantIm = atoi(argv[3]);
		Matriz imagenes = parser(argv[2],cantIm); 	// ENTRADA, CANTIDAD DE IMAGENES

		int cantAutov = atoi(argv[4]);
		int cantIterMetPot = atoi(argv[5]);
		int cantVecinos = atoi(argv[6]);
		int k = atoi(argv[7]);

		int tamConj = cantIm/k;
		vector<double> hitRate;
		for(int i = 0; i<k; i++){
			Matriz test = imagenes.subMatriz(i*tamConj,(i+1)*tamConj);
			Matriz train = imagenes.subMatriz(0,i*tamConj,(i+1)*tamConj,cantIm);
			double hR = usarPca(train,test,cantAutov,cantIterMetPot,cantVecinos);
			hitRate.push_back(hR);
		}
		double hR = 0;
		for (int i = 0; i < hitRate.size(); ++i){
			hR += hitRate[i];
		}
		hR = hR/(double) hitRate.size();
		cout << "HitRate: " << hR << endl;	
	} else if (strcmp(argv[1],"pls") == 0){
		int cantIm = atoi(argv[3]);
		Matriz imagenes = parser(argv[2],cantIm); 	// ENTRADA, CANTIDAD DE IMAGENES

		int cantIterPls = atoi(argv[4]);
		int cantIterMetPot = atoi(argv[5]);
		int cantVecinos = atoi(argv[6]);
		int k = atoi(argv[7]);

		int tamConj = cantIm/k;
		vector<double> hitRate;
		for(int i = 0; i<k; i++){
			Matriz test = imagenes.subMatriz(i*tamConj,(i+1)*tamConj);
			Matriz train = imagenes.subMatriz(0,i*tamConj,(i+1)*tamConj,cantIm);
			double hR = usarPls(train,test,cantIterPls,cantIterMetPot,cantVecinos);
			hitRate.push_back(hR);
		}
		double hR = 0;
		for (int i = 0; i < hitRate.size(); ++i){
			hR += hitRate[i];
		}
		hR = hR/(double) hitRate.size();
		cout << "HitRate: " << hR << endl;	
	} else if (strcmp(argv[1],"knn") == 0){
		int cantIm = atoi(argv[3]);
		Matriz imagenes = parser(argv[2],cantIm); 	// ENTRADA, CANTIDAD DE IMAGENES

		int cantVecinos = atoi(argv[4]);
		int k = atoi(argv[5]);

		int tamConj = cantIm/k;
		vector<double> hitRate;
		for(int i = 0; i<k; i++){
			Matriz test = imagenes.subMatriz(i*tamConj,(i+1)*tamConj);
			Matriz train = imagenes.subMatriz(0,i*tamConj,(i+1)*tamConj,cantIm);
			double hR = usarKnn(train,test,cantVecinos);
			hitRate.push_back(hR);
		}
		double hR = 0;
		for (int i = 0; i < hitRate.size(); ++i){
			hR += hitRate[i];
		}
		hR = hR/(double) hitRate.size();
		cout << "HitRate: " << hR << endl;
	}

	
	return 0;
  
}

