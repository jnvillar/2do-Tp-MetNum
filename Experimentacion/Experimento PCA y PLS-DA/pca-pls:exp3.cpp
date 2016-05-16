#include "../../Matriz/parser.cpp"
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]){
	if (argc != 8 && argc != 6){		
		cout << "USO " << argv[0] << "[1 INPUT FILE] [2 CANT DE IMAGENES] [3 CANT DE AUTOVECTORES] [4 CANTIDAD ITERACIONES METODO POTENCIA] [5 CANTIDAD VECINOS] [6 K]" << endl;
		return 0;
	}

	FILE* out1 = fopen("calidadPca.txt","w");
	FILE* out2 = fopen("calidadPls.txt","w");
	FILE* out3 = fopen("calidadKnn.txt","w");	

	int cantIm = atoi(argv[2]);
	int cantAutov = atoi(argv[3]);
	int cantIterMetPot = atoi(argv[4]);
	int cantVecinos = atoi(argv[5]);
	int k = atoi(argv[6]);
	int tamConj = cantIm/k;	
	
	Matriz imagenesPca = parser(argv[1],cantIm); 	// ENTRADA, CANTIDAD DE IMAGENES
	Matriz imagenesPls = parser(argv[1],cantIm); 	// ENTRADA, CANTIDAD DE IMAGENES
	Matriz imagenesKnn = parser(argv[1],cantIm); 	// ENTRADA, CANTIDAD DE IMAGENES

	
	vector<float> hitRatePca;
	vector<float> hitRatePls;
	vector<float> hitRateKnn;

	for(int i = 0; i<k; i++){
		Matriz testpca = imagenesPca.subMatriz(i*tamConj,(i+1)*tamConj);
		Matriz testplc = imagenesPls.subMatriz(i*tamConj,(i+1)*tamConj);
		Matriz testknn = imagenesKnn.subMatriz(i*tamConj,(i+1)*tamConj);
		Matriz trainpca = imagenesPca.subMatriz(0,i*tamConj,(i+1)*tamConj,cantIm);
		Matriz trainpls = imagenesPls.subMatriz(0,i*tamConj,(i+1)*tamConj,cantIm);
		Matriz trainknn = imagenesKnn.subMatriz(0,i*tamConj,(i+1)*tamConj,cantIm);
		float hRPca = usarPca(trainpca,testpca,cantAutov,cantIterMetPot,cantVecinos);
		float hRPls = usarPls(trainpls,testplc,cantAutov,cantIterMetPot,cantVecinos);
		float hRKnn = usarKnn(trainknn,testknn,cantVecinos);
		hitRatePca.push_back(hRPca);
		hitRatePls.push_back(hRPls);
		hitRateKnn.push_back(hRKnn);
	}

	float hRPca = 0;
	float hRPls = 0;
	float hRKnn = 0;

	for (int i = 0; i < hitRatePca.size(); ++i){
		hRPca += hitRatePca[i];
		hRPls += hitRatePls[i];
		hRKnn += hitRateKnn[i];
	}

	hRPca = hRPca/(float) hitRatePca.size();
	hRPls = hRPls/(float) hitRatePls.size();
	hRKnn = hRKnn/(float) hitRateKnn.size();

	fprintf(out1, "%f\n", hRPca);	
	cout << "HitRate: " << hRPca << endl;
	fprintf(out2, "%f\n", hRPls);	
	cout << "HitRate: " << hRPls << endl;
	fprintf(out3, "%f\n", hRKnn);	
	cout << "HitRate: " << hRKnn << endl;	

return 0;

}