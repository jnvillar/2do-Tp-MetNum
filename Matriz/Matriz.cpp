#include <vector>
#include <algorithm>
#include <cassert>
#include <iostream>
#include <sstream>
#include <vector>
#include <math.h>
#include <fstream>
#include <tuple>
 using namespace std;

class Matriz{

	private:
		vector< vector <float> > m;
		int filas;
		int cols;
		vector<int> digitos;
		// El vector en la posicion "i" de m es una imagen del digito en la posicion "i" de digitos

		//Devuelve el resultado de la resta vectorial entre v1 y v2 (v1-v2)
		vector<float> resta(vector<float> v1,vector<float> v2){
			vector<float> res;
			for (int i = 0; i < v1.size(); ++i) {
				res.push_back(v1[i]-v2[i]);
			}
			return res;
		}

		//Devuelve el resultado de la norma vectorial 2 realizada sobre el vector v
		float norma2(vector<float> v){
			float sum = 0;
			for (int i = 0; i < v.size(); ++i)
			{
				sum += v[i]*v[i];
			}
			return sqrt(sum);			
		}

		//Devuelve el digito que más cantidad de veces aparece como segunda coordenada en los pares contenidos por el vector 
		int masVotado(vector<pair<float,int> > v){
			vector<int> counting(10,0);
			for (int i = 0; i < v.size(); ++i) {
				counting[v[i].second]++;
			}
			int max = 0;
			for (int i = 0; i < 10; ++i)
			{
				if(counting[i]>counting[max]){
					max = i;
				}
			}
			return max;
		}
		
	public:	

		//Constructor de matriz por defecto
   		Matriz() {}

   		//Constructor de matriz llena de ceros dadas la cantidad de filas y columnas
   		Matriz(int fils, int columnas){
			m.clear();
			vector<float> fil(columnas,0);
			vector< vector<float> > mtx(fils,fil);
			m = mtx;
			filas = fils;
			cols = columnas;
			vector<int> dig(fils,0);
			digitos = dig;
		};

		//Constructor de matriz al cual le damos como argumentos el conjunto de imagenes (dado como un vector de vectores) y los digitos que representa cada una
		Matriz(vector< vector <float> > mtx, vector<int> num){
			m.clear();
			m = mtx;
			filas = mtx.size();
			cols = mtx[0].size();	
			digitos = num;
		};


		//Devuelve el numero de filas de la matriz 
		int Filas(){
			return filas;
		}

		//Devuelve el numero de columnas de la matriz
		int Columnas(){
			return cols;
		}

		//Reemplaza el valor en la posicion i,j de la matriz por v 
		void modValor(int i, int j, float v){
			m[i][j] = v;
			return;
		}

		//Devuelve el valor en la posicion i,j de la matriz
		float obtenerValor(int i, int j){
			return m[i][j];
		}

		//Devuelve la fila i de la matriz
		vector<float> obtenerFila(int i){
			return m[i];
		}
		
		//Devuelve el dígito que representa la imagen representada por la fila i de la matriz 
		int digitoRepresentado(int i){
			return digitos[i];
		}

		//Imprime la matriz en el directorio pasado como parametro
		void imprimirMatriz(FILE* out){
			fprintf(out, "Imprimiendo matriz\n");
			for (int i = 0; i < filas; i++){				
				for (int j = 0; j < cols; j++){
					if(j == 0){fprintf(out, "|");}
						if(m[i][j]<0){					
							fprintf(out, "%f", m[i][j]);
						}else{
							fprintf(out, " %f", m[i][j]);							
						} 
					if(j == cols-1){
						fprintf(out, "| %d \n", digitos[i]);
					} else{ 
						fprintf(out, "  ");
					}									
				}			
			}
			fprintf(out, "\n");
		}

		//Método kNN para asignarle un digito a una imagen dada
		int caenene(int k, vector<float> img){
			
			vector<pair<float,int> > normas;
			vector<pair<float,int> > kmenores;
			pair<float,int> res;			
			for (int i = 0; i < filas; ++i) {				
				res.first = norma2(resta(m[i],img));
				res.second = digitos[i];
				normas.push_back(res);								
			}

			sort(normas.begin(), normas.end());
			for (int i = 0; i < k; ++i)	{
				kmenores.push_back(normas[i]);
			}

			int result;
			result = masVotado(kmenores);
			return result;
		}

		//Devuelve el resultado del producto matricial m*m2 
		Matriz mult(Matriz m2){
			Matriz res(filas, m2.Columnas());
			for (int i = 0; i < filas; ++i){
				for (int j = 0; j < m2.Columnas(); ++j){
					float sumaProd = 0;
					for (int h = 0; h < cols; ++h){
						sumaProd += m[i][h] * m2.obtenerValor(h,j);
					}
					res.modValor(i,j,sumaProd);
				}
				
			}
			return res;
		}

		//Devuelve el resultado del producto matricial m*v si lado = d (derecha); y v*m si lado = i (izquierda)  
		vector<float> multxVect(vector<float> v, char lado){
			vector<float> res;
			if (lado == 'i'){
				for (int i = 0; i < cols; ++i){
					float num = 0;
					for (int j = 0; j < v.size(); ++j){
						num += v[j]*m[j][i];
					}
					res.push_back(num);
				}
			} else if (lado == 'd'){
				for (int i = 0; i < filas; ++i){
					float num = 0;
					for (int j = 0; j < v.size(); ++j){
						num += v[j]*m[i][j];
					}
					res.push_back(num);
				}
			} else {
				cout << "SOS UN GIL" << endl;
				exit(1);
			}
			return res;
		}

		//Calcula la media entre los elementos de cada una de las columnas de la matriz y luego se la resta a cada elemento de la columna respectivamente
		void restarMedia(){
			// CALCULAMOS LAS MEDIAS
			vector<float> media(cols,0);
			for (int i = 0; i < filas; ++i){
				for (int j = 0; j < cols; ++j){
					media[j] += m[i][j];
				}
			}
			for (int i = 0; i<media.size(); i++){
				media[i] = media[i]/filas;
			}

			// RESTAMOS
			for (int i = 0; i < filas; ++i){
				for (int j = 0; j < cols; ++j){
					m[i][j] -= media[j];
				}
			}

		}


		pair<vector<float>,float> metodoPotencia(int iter){
			/*Genero Vector Random*/
			srand (time(NULL));
			vector<float> v;
			for (int i = 0; i < filas; ++i) {
				v.push_back(rand());
			}
			float normV = norma2(v);
			for (int j = 0; j < v.size(); ++j)	{
				v[j] = v[j]/normV;
			}
			/*Genero Vector Random*/

			/*Calculo Autovector*/
			for (int i = 0; i < iter; ++i) {
				vector<float> Bv = multxVect(v,'d');
				float normBv = norma2(Bv);
				for (int j = 0; j < Bv.size(); ++j)	{
					Bv[j] = Bv[j]/normBv;
				}
				v = Bv;				
			}
			/*Calculo Autovector*/

			/*Calculo Autovalor*/
			vector<float> Bv = multxVect(v,'d');
			float vtBv = 0;
			for (int i = 0; i < v.size(); ++i){
				vtBv += v[i]*Bv[i];
			}
			float vtv = pow(norma2(v),2);
			float autovalor = vtBv/vtv;
			/*Calculo Autovalor*/

			pair<vector<float>,float> res;
			res.first =  v;
			res.second = autovalor;
			return res;
		}

		

		vector< vector<float> > obtenerAutovectores(){
			vector< vector<float> > res;
			vector<int> a(filas,0);
			Matriz mtx(m,a);

			for (int h = 0; h<filas; h++){

				pair<vector<float>,float> autov = mtx.metodoPotencia(30);

				vector<float> v = autov.first;
				res.push_back(v);

				vector< vector <float> > mat;
				for (int i = 0; i<v.size(); i++){
					vector <float> fil;
					for (int j = 0; j < v.size(); j++){
						fil.push_back(v[i]*v[j]);
					}
					mat.push_back(fil);
				}



				for (int i = 0; i<filas; i++){
					for (int j = 0; j < cols; j++){
						mtx.modValor(i,j, mtx.obtenerValor(i,j) - autov.second * mat[i][j]);
					}
				}	
			}

			return res;

		}
};
