#include "../../Matriz/parser.cpp"
#include <stdio.h>
#include <string.h>

vector<vector<float> > crearvector(int k,int j){
	vector<float> aux(k,0);
	vector<vector<float> > res;
	for (int i = 0; i < j; ++i){
		res.push_back(aux);
	}		
	return res;
}

void sumMat(vector<vector<float> > &m1,vector<vector<float> > &m2){
	for (int i = 0; i < m1.size() ; ++i){
		for (int j = 0; j < m1[i].size(); ++j){
			m1[i][j] = m1[i][j]+m2[i][j];
		}			
	}	
}

void promedio(vector<vector<float> > &m, float k){
	for (int i = 0; i < m.size(); ++i){
		for (int j = 0; j < m[i].size(); ++j){
			m[i][j] = m[i][j]/k;
		}
	}
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

	vector<float> aux(1,0);
	vector<vector<float> > metricasPromPca = crearvector(11,3);
	metricasPromPca.push_back(aux);
	vector<vector<float> > metricasPromPls = crearvector(11,3);
	metricasPromPls.push_back(aux);
	vector<vector<float> > metricasPromKnn = crearvector(11,3);
	metricasPromKnn.push_back(aux);

	vector<vector<float> > confPca = crearvector(10,10);
	vector<vector<float> > confPls = crearvector(10,10);
	vector<vector<float> > confKnn = crearvector(10,10);

	for(int i = 0; i<k; i++){
		Matriz testpca = imagenesPca.subMatriz(i*tamConj,(i+1)*tamConj);
		Matriz testplc = imagenesPls.subMatriz(i*tamConj,(i+1)*tamConj);
		Matriz testknn = imagenesKnn.subMatriz(i*tamConj,(i+1)*tamConj);
		Matriz trainpca = imagenesPca.subMatriz(0,i*tamConj,(i+1)*tamConj,cantIm);
		Matriz trainpls = imagenesPls.subMatriz(0,i*tamConj,(i+1)*tamConj,cantIm);
		Matriz trainknn = imagenesKnn.subMatriz(0,i*tamConj,(i+1)*tamConj,cantIm);

		pair<vector<vector<float> >,vector<vector<float> > > metricasPca= usarPca2(trainpca,testpca,cantAutov,cantIterMetPot,cantVecinos);
		pair<vector<vector<float> >,vector<vector<float> > > metricasPls= usarPls2(trainpls,testplc,cantAutov,cantIterMetPot,cantVecinos);
		pair<vector<vector<float> >,vector<vector<float> > > metricasKnn= usarKnn2(trainknn,testknn,cantVecinos);	
		
		sumMat(metricasPromPca,metricasPca.first);
		sumMat(metricasPromPls,metricasPls.first);
		sumMat(metricasPromKnn,metricasKnn.first);

		sumMat(confPca,metricasPca.second);
		sumMat(confPls,metricasPls.second);
		sumMat(confKnn,metricasKnn.second);
		
	}

	//SACO PROMEDIO

	promedio(metricasPromPca,k);
	promedio(metricasPromPls,k);
	promedio(metricasPromKnn,k);
	promedio(confPca,k);
	promedio(confPls,k);
	promedio(confKnn,k);
	
	// IMPRIMO PRESICION
		fprintf(out1, "%s\n", "Precision");			
		fprintf(out2, "%s\n", "Presicion");				
		fprintf(out3, "%s\n", "Presicion");	

	for (int i = 0; i < 11; ++i){			
		fprintf(out1, "Numero: %d ,%f\n", i, metricasPromPca[0][i]);			
		fprintf(out2, "Numero: %d ,%f\n", i, metricasPromPls[0][i]);				
		fprintf(out3, "Numero: %d ,%f\n", i, metricasPromKnn[0][i]);			
	}

	// IMPRIMO RECALL
		fprintf(out1, "%s\n", "Recall");			
		fprintf(out2, "%s\n", "Recall");				
		fprintf(out3, "%s\n", "Recall");	

	for (int i = 0; i < 11; ++i){
		fprintf(out1, "Numero: %d ,%f\n", i, metricasPromPca[1][i]);			
		fprintf(out2, "Numero: %d ,%f\n", i, metricasPromPls[1][i]);				
		fprintf(out3, "Numero: %d ,%f\n", i, metricasPromKnn[1][i]);			
	}

	// IMPRIMO F1-SCORE
		fprintf(out1, "%s\n", "F1-Score");			
		fprintf(out2, "%s\n", "F1-Score");				
		fprintf(out3, "%s\n", "F1-Score");	

	for (int i = 0; i < 11; ++i){
		fprintf(out1, "Numero: %d ,%f\n", i, metricasPromPca[2][i]);			
		fprintf(out2, "Numero: %d ,%f\n", i, metricasPromPls[2][i]);				
		fprintf(out3, "Numero: %d ,%f\n", i, metricasPromKnn[2][i]);			
	}

	// IMPRIMO HITRATE

	fprintf(out1, "%s\n", "Hit rate");			
	fprintf(out2, "%s\n", "Hit rate");				
	fprintf(out3, "%s\n", "Hit rate");	
	fprintf(out1, "%f\n", metricasPromPca[3][0]);			
	fprintf(out2, "%f\n", metricasPromPls[3][0]);				
	fprintf(out3, "%f\n", metricasPromKnn[3][0]);

	// IMPRIMO MATCONF

	fprintf(out1, "%s\n", "MatConf");			
	fprintf(out2, "%s\n", "MatConf");				
	fprintf(out3, "%s\n", "MatConf");	

	for (int i = 0; i < 10; ++i){
		for (int j = 0; j < 10; ++j){
		fprintf(out1, "%f,", confPca[i][j]);			
		fprintf(out2, "%f,", confPls[i][j]);				
		fprintf(out3, "%f,", confKnn[i][j]);	
		}
		fprintf(out1, "\n");			
		fprintf(out2, "\n");				
		fprintf(out3, "\n");	
	}



return 0;

}