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
	public:	

   		Matriz() {}

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

		Matriz(vector< vector <float> > mtx, vector<int> num){
			m.clear();
			m = mtx;
			filas = mtx.size();
			cols = mtx[0].size();	
			digitos = num;
		};



		int Filas(){
			return filas;
		}

		int Columnas(){
			return cols;
		}

		void modValor(int i, int j, float v){
			m[i][j] = v;
			return;
		}

		float obtenerValor(int i, int j){
			return m[i][j];
		}

		vector<float> obtenerFila(int i){
			return m[i];
		}
		
		int digitoRepresentado(int i){
			return digitos[i];
		}

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

		vector<float> resta(vector<float> v1,vector<float> v2){
			vector<float> res;
			for (int i = 0; i < v1.size(); ++i) {
				res.push_back(v1[i]-v2[i]);
			}
			return res;
		}

		float norma2(vector<float> v){
			float sum = 0;
			for (int i = 0; i < v.size(); ++i)
			{
				sum += v[i]*v[i];
			}
			return sqrt(sum);			
		}

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

		Matriz mult(Matriz m2){
			Matriz res(filas, m2.Columnas());
			for (int i = 0; i < filas; ++i){
				for (int j = 0; j < m2.Columnas(); ++j){
					int sumaProd = 0;
					for (int h = 0; h < cols; ++h){
						sumaProd += m[i][h] * m2.obtenerValor(h,j);
					}
					res.modValor(i,j,sumaProd);
				}
				
			}
			return res;
		}

		vector<float> multVect(vector<float> v, char lado){
			vector<float> res;
			if (lado == 'i'){
				for (int i = 0; i < cols; ++i){
					for (int j = 0; j < v.size(); ++j){
						int num = v[j]*m[j][i];
						res.push_back(num);
					}
				}
			} else if (lado == 'd'){
				for (int i = 0; i < filas; ++i){
					for (int j = 0; j < v.size(); ++j){
						int num = v[j]*m[i][j];
						res.push_back(num);
					}
				}
			} else {
				cout << "SOS UN GIL" << endl;
				exit(1);
			}
			return res;
		}

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


		pair<vector<float>,float> dameAutovalorGuachin(int iter){
			/*Genero Vector Random*/
			srand (time(NULL));
			vector<float> v;
			for (int i = 0; i < filas; ++i) {
				v.push_back(rand());
			}
			/*Genero Vector Random*/

			/*Calculo Autovector*/
			for (int i = 0; i < iter; ++i) {
				vector<float> Bv = multVect(v,'d');
				float normBv = norma2(Bv);
				for (int j = 0; j < Bv.size(); ++j)	{
					Bv[i] = Bv[i]/normBv;
				}
				v = Bv;				
			}
			/*Calculo Autovector*/

			/*Calculo Autovalor*/
			vector<float> Bv = multVect(v,'d');
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
};
