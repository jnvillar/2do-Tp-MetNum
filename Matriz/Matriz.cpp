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
		

		void ImprimirMatriz(FILE* out){
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

			sort(normas);
			for (int i = 0; i < k; ++i)	{
				kmenores.push_back(normas[i])
			}

			int result = masVotado(menores);
			return result;
		}

		vector<float> resta(vector<float> v1,vector<float> v2){
			vector<float> res;
			for (int i = 0; i < v1.size(); ++i) {
				res.push(v1[i]-v2[i]);
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

		int masVotado(vector<float,int> v){
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


};
