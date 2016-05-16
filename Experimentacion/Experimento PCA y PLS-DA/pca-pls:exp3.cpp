#include "../../Matriz/parser.cpp"
#include <stdio.h>
#include <string.h>

vector<vector<float> > crearvector(){
	vector<float> aux(11,0);
	vector<float> aux2(1,0);
	vector<vector<float> > res;
	res.push_back(aux);
	res.push_back(aux);
	res.push_back(aux);
	res.push_back(aux2);
	return res;
}

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


	vector<vector<float> > metricasPromPca = crearvector();
	vector<vector<float> > metricasPromPls = crearvector();
	vector<vector<float> > metricasPromKnn = crearvector();

	for(int i = 0; i<k; i++){
		Matriz testpca = imagenesPca.subMatriz(i*tamConj,(i+1)*tamConj);
		Matriz testplc = imagenesPls.subMatriz(i*tamConj,(i+1)*tamConj);
		Matriz testknn = imagenesKnn.subMatriz(i*tamConj,(i+1)*tamConj);
		Matriz trainpca = imagenesPca.subMatriz(0,i*tamConj,(i+1)*tamConj,cantIm);
		Matriz trainpls = imagenesPls.subMatriz(0,i*tamConj,(i+1)*tamConj,cantIm);
		Matriz trainknn = imagenesKnn.subMatriz(0,i*tamConj,(i+1)*tamConj,cantIm);

		vector<vector<float> > metricasPca= usarPca(trainpca,testpca,cantAutov,cantIterMetPot,cantVecinos);
		vector<vector<float> > metricasPls= usarPls(trainpls,testplc,cantAutov,cantIterMetPot,cantVecinos);
		vector<vector<float> > metricasKnn= usarKnn(trainknn,testknn,cantVecinos);	

		for (int i = 0; i < 11; ++i){			
			metricasPromPca[0][i] += metricasPca[0][i];
			metricasPromPls[0][i] += metricasPca[0][i];
			metricasPromKnn[0][i] += metricasPca[0][i];

			metricasPromPca[1][i] += metricasPca[1][i];
			metricasPromPls[1][i] += metricasPls[1][i];
			metricasPromKnn[1][i] += metricasPca[1][i];

			metricasPromPca[2][i] += metricasPca[2][i];
			metricasPromPls[2][i] += metricasPls[2][i];
			metricasPromKnn[2][i] += metricasKnn[2][i];
		}
			metricasPromPca[3][0] += metricasPca[3][0];
			metricasPromPls[3][0] += metricasPls[3][0];
			metricasPromKnn[3][0] += metricasKnn[3][0];	
	}

	//SACO PROMEDIO

	for (int i = 0; i < 11; ++i){
		metricasPromPca[0][i] = metricasPromPca[0][i]/k;
		metricasPromPls[0][i] = metricasPromPls[0][i]/k;
		metricasPromKnn[0][i] = metricasPromKnn[0][i]/k;

		metricasPromPca[1][i] = metricasPromPca[1][i]/k;
		metricasPromPls[1][i] = metricasPromPls[1][i]/k;
		metricasPromKnn[1][i] = metricasPromKnn[1][i]/k;

		metricasPromPca[2][i] = metricasPromPca[2][i]/k;
		metricasPromPls[2][i] = metricasPromPls[2][i]/k;
		metricasPromKnn[2][i] = metricasPromKnn[2][i]/k;		
	}

		metricasPromPca[3][0] = metricasPromPca[3][0]/k;
		metricasPromPls[3][0] = metricasPromPls[3][0]/k;
		metricasPromKnn[3][0] = metricasPromKnn[3][0]/k;	

	// IMPRIMO	

		for (int i = 0; i < 11; ++i){
			fprintf(out1, "%s\n", "Precision");			
			fprintf(out2, "%s\n", "Presicion");				
			fprintf(out3, "%s\n", "Presicion");	

			fprintf(out1, "Numero: %d ,%f\n", i, metricasPromPca[0][i]);			
			fprintf(out2, "Numero: %d ,%f\n", i, metricasPromPls[0][i]);				
			fprintf(out3, "Numero: %d ,%f\n", i, metricasPromKnn[0][i]);			
		}

		for (int i = 0; i < 11; ++i){
			fprintf(out1, "%s\n", "Recall");			
			fprintf(out2, "%s\n", "Recall");				
			fprintf(out3, "%s\n", "Recall");	

			fprintf(out1, "Numero: %d ,%f\n", i, metricasPromPca[1][i]);			
			fprintf(out2, "Numero: %d ,%f\n", i, metricasPromPls[1][i]);				
			fprintf(out3, "Numero: %d ,%f\n", i, metricasPromKnn[1][i]);			
		}

		for (int i = 0; i < 11; ++i){
			fprintf(out1, "%s\n", "F1-Score");			
			fprintf(out2, "%s\n", "F1-Score");				
			fprintf(out3, "%s\n", "F1-Score");	

			fprintf(out1, "Numero: %d ,%f\n", i, metricasPromPca[2][i]);			
			fprintf(out2, "Numero: %d ,%f\n", i, metricasPromPls[2][i]);				
			fprintf(out3, "Numero: %d ,%f\n", i, metricasPromKnn[2][i]);			
		}

	fprintf(out1, "%s\n", "Hit rate");			
	fprintf(out2, "%s\n", "Hit rate");				
	fprintf(out3, "%s\n", "Hit rate");	

	fprintf(out1, "%f\n", metricasPromPca[3][0]);			
	fprintf(out2, "%f\n", metricasPromPls[3][0]);				
	fprintf(out3, "%f\n", metricasPromKnn[3][0]);

return 0;

}