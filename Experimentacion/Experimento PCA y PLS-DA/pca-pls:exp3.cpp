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

void imprimirVec(ostream &salida, string a ,vector<float> v){
	salida << a.c_str() << endl;
	for (int i = 0; i < v.size()-1; ++i){			
		salida << i << " "<< v[i] << endl;		
	}
	salida << "Promedio " << a.c_str() << endl;
	salida << v[v.size()-1] << endl;
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



int main(int argc, char* argv[]){
	bool debug = true;
	if (argc != 9){		
		cout << "USO " << argv[0] << "[1 INPUT FILE] [2 CANT DE IMAGENES] [3 CANT DE AUTOVECTORES] [4 CANTIDAD ITERACIONES METODO POTENCIA] [5 CANTIDAD VECINOS] [6 K-FOLD] [7 AUMENTAR AUTOV Y K EN] [8 ITERACIONES]" << endl;
		return 0;
	}
	ofstream out1; 
	out1.open("calidadPca.txt");
	ofstream out2; 
	out2.open("calidadPls.txt");
	ofstream out3; 
	out3.open("calidadKnn.txt");

	int cantIm = atoi(argv[2]);
	int cantAutov = atoi(argv[3]);
	int cantIterMetPot = atoi(argv[4]);
	int cantVecinos = atoi(argv[5]);
	int cantVecinosInicial = atoi(argv[5]);
	int k = atoi(argv[6]);
	int tamConj = cantIm/k;	
	int aumentar = atoi(argv[7]);
	int iteraciones = atoi(argv[8]);
	
	Matriz imagenesPca = parser(argv[1],cantIm); 	// ENTRADA, CANTIDAD DE IMAGENES
	Matriz imagenesPls = parser(argv[1],cantIm); 	// ENTRADA, CANTIDAD DE IMAGENES
	Matriz imagenesKnn = parser(argv[1],cantIm); 	// ENTRADA, CANTIDAD DE IMAGENES

	for (int u = 0; u < iteraciones; ++u){

		out1 << "Iteracion: " << u << " Alpha: " << cantAutov << endl;
		out2 << "Iteracion: " << u << " Gamma: " << cantAutov << endl;
		out3 << "Iteracion: " << u << " k: " << cantVecinos << endl;		
		if(debug)cout<<"Iteracion "<< u << endl;  		

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
			if(debug)cout<<"Grupo "<< i << "Iteracion" << u << endl;  
			Matriz testpca = imagenesPca.subMatriz(i*tamConj,(i+1)*tamConj);
			Matriz testplc = imagenesPls.subMatriz(i*tamConj,(i+1)*tamConj);
			Matriz testknn = imagenesKnn.subMatriz(i*tamConj,(i+1)*tamConj);
			Matriz trainpca = imagenesPca.subMatriz(0,i*tamConj,(i+1)*tamConj,cantIm);
			Matriz trainpls = imagenesPls.subMatriz(0,i*tamConj,(i+1)*tamConj,cantIm);
			Matriz trainknn = imagenesKnn.subMatriz(0,i*tamConj,(i+1)*tamConj,cantIm);

			if(debug)cout<< "metricas Pca" << endl;
			pair<vector<vector<float> >,vector<vector<float> > > metricasPca= usarPca2(trainpca,testpca,cantAutov,cantIterMetPot,cantVecinosInicial);
			if(debug)cout<< "Listo" << endl;
			if(debug)cout<< "Metricas Pls" << endl;
			pair<vector<vector<float> >,vector<vector<float> > > metricasPls= usarPls2(trainpls,testplc,cantAutov,cantIterMetPot,cantVecinosInicial);
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
		
		//A LA MATRIZ DE CONFUSION NO SE LE SACA EL PROMEDIO

		if(debug)cout<< "Imprimiendo" << endl;
		
		// IMPRIMO PRESICION
		
		for (int i = 0; i < 4; ++i){
			if (i==0){
				imprimirVec(out1,"Presicion:",metricasPromPca[i]);
				imprimirVec(out2,"Presicion:",metricasPromPls[i]);	
				imprimirVec(out3,"Presicion:",metricasPromKnn[i]);	
			}

			if (i==1){
				imprimirVec(out1,"Recall:",metricasPromPca[i]);
				imprimirVec(out2,"Recall:",metricasPromPls[i]);	
				imprimirVec(out3,"Recall:",metricasPromKnn[i]);
			}

			if (i==2){
				imprimirVec(out1,"F1-Score:",metricasPromPca[i]);
				imprimirVec(out2,"F1-Score:",metricasPromPls[i]);	
				imprimirVec(out3,"F1-Score:",metricasPromKnn[i]);
			}

			if(i==3){
				imprimirVec(out1,"Hitrate:",metricasPromPca[i]);
				imprimirVec(out2,"Hitrate:",metricasPromPls[i]);	
				imprimirVec(out3,"Hitrate:",metricasPromKnn[i]);
			}
		}		
		// IMPRIMO MATCONF

		imprimirMatConf(out1,confPca);
		imprimirMatConf(out2,confPls);
		imprimirMatConf(out3,confKnn);

		cantAutov+= aumentar;
		cantVecinos+= aumentar;
	}

return 0;

}