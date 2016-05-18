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

void imprimir(ostream &salida, string a ,vector<float> v){
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
	if (argc != 6){
		cout << "USO:" << endl;
		cout << "KNN: " << argv[0] << " knn [INPUT FILE] [CANT DE IMAGENES] [CANTIDAD VECINOS] [K]" << endl;
		return 0;
	}

	ofstream out; 
	out.open("mc.txt");

	
	vector<vector<float> > confKnn = crearvector(10,10);
	
	
	
	int cantIm = atoi(argv[3]);
	Matriz imagenes = parser(argv[2],cantIm); 	// ENTRADA, CANTIDAD DE IMAGENES

	int cantVecinos = atoi(argv[4]);
	int k = atoi(argv[5]);

	int tamConj = cantIm/k;
	vector<float> hitRate;
	for(int i = 0; i<k; i++){
		
		Matriz test = imagenes.subMatriz(i*tamConj,(i+1)*tamConj);
		Matriz train = imagenes.subMatriz(0,i*tamConj,(i+1)*tamConj,cantIm);
		//float hR = usarKnn(train,test,cantVecinos);
		
		pair<vector<vector<float> >,vector<vector<float> > > metricasKnn= usarKnn2(train,test,cantVecinos);	
		sumMat(confKnn,metricasKnn.second);

		//hitRate.push_back(hR);
	}
	
	imprimirMatConf(out,confKnn);

	
	return 0;
  
}

