#include "../../Matriz/parser.cpp"
#include <stdio.h>
#include <string.h>






int main(int argc, char* argv[]){
	if (argc != 6){
		cout << "USO:" << endl;
		cout << "KNN: " << argv[0] << " knn [INPUT FILE] [CANT DE IMAGENES] [CANTIDAD VECINOS] [K]" << endl;
		return 0;
	}

	FILE* out = fopen("kAux.txt","w");

	for(int j = 0; j<10; j++){
	
		int cantIm = atoi(argv[3]);
		Matriz imagenes = parser(argv[2],cantIm); 	// ENTRADA, CANTIDAD DE IMAGENES

		int cantVecinos = atoi(argv[4])+j;
		int k = atoi(argv[5]);

		int tamConj = cantIm/k;
		vector<float> hitRate;
		for(int i = 0; i<k; i++){
			cout << "j " << j << endl;

			cout << "i " << i << endl;
			Matriz test = imagenes.subMatriz(i*tamConj,(i+1)*tamConj);
			Matriz train = imagenes.subMatriz(0,i*tamConj,(i+1)*tamConj,cantIm);
			float hR = usarKnn(train,test,cantVecinos);
			hitRate.push_back(hR);
		}
		float hR = 0;
		for (int i = 0; i < hitRate.size(); ++i){
			hR += hitRate[i];
		}
		hR = hR/(float) hitRate.size();
		fprintf(out, "k: %d %f\n", cantVecinos, hR);

	}
	fclose(out);
	return 0;
  
}

