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
		vector<float> resta(vector<float>& v1,vector<float>& v2){
			vector<float> res;
			for (int i = 0; i < v1.size(); ++i) {
				res.push_back(v1[i]-v2[i]);
			}
			return res;
		}

		//Devuelve el resultado de la norma vectorial 2 realizada sobre el vector v
		float norma2(vector<float>& v){
			float sum = 0;
			for (int i = 0; i < v.size(); ++i)
			{
				sum += v[i]*v[i];
			}
			return sqrt(sum);			
		}

		//Devuelve el digito que más cantidad de veces aparece como segunda coordenada en los pares contenidos por el vector 
		int masVotado(vector<pair<float,int> >& v){
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

		void cambiarDigitos(vector<int> dig){
			digitos = dig;
			return;
		}

		vector<int> obtenerDigitos(){
			return digitos;
		}

		//Imprime la matriz por cout
		void imprimirMatriz(){
			cout << "Imprimiendo matriz\n";
			for (int i = 0; i < filas; i++){	
				cout << "|";			
				for (int j = 0; j < cols; j++){
						if(m[i][j] < 0){					
							cout << m[i][j];
						}else{
							cout << " " << m[i][j];					} 
					if(j == cols-1){
						 // fprintf(out, "| %d \n", digitos[i]);
						 cout << "| \n" ;
					} else{ 
						cout << "  ";
					}									
				}			
			}
			cout << "\n";
		}

		//Método kNN para asignarle un digito a una imagen dada
		int caenene(int k, vector<float>& img){
			
			vector<pair<float,int> > normas;
			vector<pair<float,int> > kmenores;
			pair<float,int> res;			
			for (int i = 0; i < filas; ++i) {		
				vector<float> rest = resta(m[i],img);
				res.first = norma2(rest);
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
		Matriz mult(Matriz &m2){
			cout << "mult" << endl;
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
			cout << "mult 2" << endl;

			return res;
		}

		//Devuelve el resultado del producto matricial m*v si lado = d (derecha); y v*m si lado = i (izquierda)  
		vector<float> multxVect(vector<float>& v, char lado){
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
		void restarMedia(Matriz& mtx){
			// CALCULAMOS LAS MEDIAS
			vector<float> media(cols,0);
			for (int i = 0; i < filas; ++i){
				for (int j = 0; j < cols; ++j){
					media[j] += mtx.obtenerValor(i,j);
				}
			}
			for (int i = 0; i<media.size(); i++){
				media[i] = media[i]/mtx.Filas();
			}

			// RESTAMOS Y DIVIDIMOS
			float divi = sqrt(filas-1);
			for (int i = 0; i < filas; ++i){
				for (int j = 0; j < cols; ++j){
					m[i][j] = (m[i][j]-media[j])/divi;
				}
			}

		}

		void normalizarVector(vector<float>& v){
			float normV = norma2(v);
			for (int j = 0; j < v.size(); ++j)	{
				v[j] = v[j]/normV;
			}	
		}

		//Metodo de la potencia para obtener autovalor de modulo maximo y su autovector asociado
		pair<vector<float>,float> metodoPotencia(int iter){
			/*Genero Vector Random*/
			srand (time(NULL));
			vector<float> v;
			for (int i = 0; i < filas; ++i) {
				v.push_back(rand());
			}
			
			normalizarVector(v);
				
			/*Genero Vector Random*/

		
			
			/*Calculo Autovector*/
			for (int i = 0; i < iter; ++i) {
				vector<float> Bv = multxVect(v,'d');
				normalizarVector(Bv);
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

		
		//Devuelve el conjunto de autovectores de la matriz calculados mediante el metodo de la potencia y luego aplicando deflacion
		vector< vector<float> > obtenerAutovectores(){
			cout << "obtenerAutovectores " << endl;

			vector< vector<float> > res;
			vector<int> a(filas,0);
			Matriz mtx(m,a);

			for (int h = 0; h<filas; h++){
				cout << h << endl;

				//Aplico metodo de la potencia para obtener autovalor de modulo maximo y su autovector asociado
				pair<vector<float>,float> autov = mtx.metodoPotencia(15);

				vector<float> v = autov.first;
				res.push_back(v);

				//Deflacion
				//Calculo v*vt
				vector< vector <float> > mat;
				for (int i = 0; i<v.size(); i++){
					vector <float> fil;
					for (int j = 0; j < v.size(); j++){
						fil.push_back(v[i]*v[j]);
					}
					mat.push_back(fil);
				}

				// Deflacion
				// Generamos matriz que tiene el resto de los autovalores iguales y 0
				for (int i = 0; i<filas; i++){
					for (int j = 0; j < cols; j++){
						mtx.modValor(i,j, mtx.obtenerValor(i,j) - autov.second * mat[i][j]);
					}
				}	
			}

			return res;
		}

		void restaMatrices(Matriz& m2){
			for (int i = 0; i<filas; i++){
				for (int j = 0; j < cols; j++){
					m[i][j] -= m2.obtenerValor(i,j);
				}
			}
		}

		Matriz cambioDeBase(vector< vector<float> >& p){
			cout << "cambioDeBase " << endl;

			vector<int> a(p.size(),0);
			Matriz vt(p,a);
			Matriz xt = trasponer();
			Matriz rest = vt.mult(xt);
			Matriz res = rest.trasponer();

			return res;
		}



		Matriz trasponer(){
			cout << "trasponer " << endl;

			vector<vector<float> > mtx;
			for (int i = 0; i < cols; ++i) {
				vector<float> fila;
				for (int j = 0; j < filas; ++j) {
					fila.push_back(obtenerValor(j,i));
				}
				mtx.push_back(fila);
			}
			vector<int> digitos(cols,0);
			Matriz res(mtx,digitos);
			cout << "trasponer 2" << endl;

			return res;
		}

		//Devuelve la matriz resultante de hacer (Mt * M) 
		Matriz Mx(){
			cout << "Mx " << endl;

			Matriz traspuesta = trasponer();

			Matriz mtx = traspuesta.mult(*this);


			return mtx;
		}


		vector< vector<float> > pca(){
			cout << "pca " << endl;
			Matriz aux = *this;
			restarMedia(*this);
			Matriz mx = Mx();

			vector< vector<float> > p = mx.obtenerAutovectores();
			return p;
		}

		Matriz preY(vector<int> dig){
			vector< vector<float> > mtx;
			for (int i = 0; i<dig.size(); i++){
				vector<float> fil(10,-1);
				fil[dig[i]] = 1;
				mtx.push_back(fil);
			}
			vector<int> a(dig.size(),0);
			Matriz res(mtx,a);
		}


};

