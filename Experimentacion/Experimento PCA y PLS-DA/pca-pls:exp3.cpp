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

void imprimir(FILE* salida, string a ,vector<float> v){
	fprintf(salida, "%s:\n", a.c_str() );
	for (int i = 0; i < v.size(); ++i){			
		fprintf(salida, "%d ,%f\n", i, v[i]);		
	}
}

void imprimirMatConf(FILE* salida, string a, vector<vector<float> > v){
	fprintf(salida, "%s\n", "MatConf:");
	for (int i = 0; i < v.size(); ++i){
		fprintf(salida, "%s\n", "|");
		for (int j = 0; j < v[i].size(); ++j){
		fprintf(salida, "%f   ", v[i][j]);		
		}
		fprintf(salida, "%s\n", "|");	
	}
}



int main(int argc, char* argv[]){
	bool debug = true;
	if (argc != 7){		
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
		if(debug)cout<<"Grupo "<< i << endl;  
		Matriz testpca = imagenesPca.subMatriz(i*tamConj,(i+1)*tamConj);
		Matriz testplc = imagenesPls.subMatriz(i*tamConj,(i+1)*tamConj);
		Matriz testknn = imagenesKnn.subMatriz(i*tamConj,(i+1)*tamConj);
		Matriz trainpca = imagenesPca.subMatriz(0,i*tamConj,(i+1)*tamConj,cantIm);
		Matriz trainpls = imagenesPls.subMatriz(0,i*tamConj,(i+1)*tamConj,cantIm);
		Matriz trainknn = imagenesKnn.subMatriz(0,i*tamConj,(i+1)*tamConj,cantIm);

		if(debug)cout<< "metricas Pca" << endl;
		pair<vector<vector<float> >,vector<vector<float> > > metricasPca= usarPca2(trainpca,testpca,cantAutov,cantIterMetPot,cantVecinos);
		if(debug)cout<< "Listo" << endl;
		if(debug)cout<< "Metricas Pls" << endl;
		pair<vector<vector<float> >,vector<vector<float> > > metricasPls= usarPls2(trainpls,testplc,cantAutov,cantIterMetPot,cantVecinos);
		if(debug)cout<< "Listo" << endl;
		if(debug)cout<< "Metricas Knn" << endl;
		pair<vector<vector<float> >,vector<vector<float> > > metricasKnn= usarKnn2(trainknn,testknn,cantVecinos);	
		if(debug)cout<< "Listo" << endl;

		if(debug)cout<< "Guardando Metricas" << endl;
		sumMat(metricasPromPca,metricasPca.first);
		sumMat(metricasPromPls,metricasPls.first);
		sumMat(metricasPromKnn,metricasKnn.first);
		sumMat(confPca,metricasPca.second);
		sumMat(confPls,metricasPls.second);
		sumMat(confKnn,metricasKnn.second);
		if(debug)cout<< "Listo" << endl;
		
	}

	//SACO PROMEDIO

	if(debug)cout<< "Promedios" << endl;

	promedio(metricasPromPca,k);
	promedio(metricasPromPls,k);
	promedio(metricasPromKnn,k);
	promedio(confPca,k);
	promedio(confPls,k);
	promedio(confKnn,k);

	if(debug)cout<< "Imprimiendo" << endl;
	
	// IMPRIMO PRESICION
	
	for (int i = 0; i < 4; ++i){
		if (i==0){
			imprimir(out1,"Presicion",metricasPromPca[i]);
			imprimir(out2,"Presicion",metricasPromPls[i]);	
			imprimir(out3,"Presicion",metricasPromKnn[i]);	
		}

		if (i==1){
			imprimir(out1,"Recall",metricasPromPca[i]);
			imprimir(out2,"Recall",metricasPromPls[i]);	
			imprimir(out3,"Recall",metricasPromKnn[i]);
		}

		if (i==2){
			imprimir(out1,"F1-Score",metricasPromPca[i]);
			imprimir(out2,"F1-Score",metricasPromPls[i]);	
			imprimir(out3,"F1-Score",metricasPromKnn[i]);
		}

		if(i==3){
			imprimir(out1,"Hitrate",metricasPromPca[i]);
			imprimir(out2,"Hitrate",metricasPromPls[i]);	
			imprimir(out3,"Hitrate",metricasPromKnn[i]);
		}
	}		
	// IMPRIMO MATCONF

	imprimirMatConf(out1,"MatConf",confPca);
	imprimirMatConf(out2,"MatConf",confPls);
	imprimirMatConf(out3,"MatConf",confKnn);

return 0;

}