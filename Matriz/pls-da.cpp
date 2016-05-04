#include "parser.cpp"

#include "parser.cpp"

int main(int argc, char* argv[]){
	// Iteraciones
	int iteraciones = argv[2];
	//Obtengo X a partir del train
	Matriz X = parser(argv[1],3000);
	//Obtengo Y
	vector<float> digitoRepr = imagenesTrain.obtenerDigitos();
	Matriz Y = preY(digitoRepr);
	Y.restarMedia(Y);


	for (int i = 0; i < iteraciones; ++i) {

		/*Calculo M*/
		Matriz multizq;
		Matriz multder;
		Matriz m;
		Matriz Yt = trasponer(Y);
		Matriz Xt = trasponer(X);
		multizq = Xt.mult(Y);
		multder = Yt.mult(X);
		m = multizq.mult(multder);
		/*Calculo M*/

		/*Calculo autovector asociado al autovalor mas grande*/		
		pair<vector<float>,float> Mayor; //(Autovector Asociado, Mayor autovalor)
		Mayor = m.metodoPotencia(argv[3]); //ya esta normalizado
		vector<float> ti = X.multder(Mayor.first);	
		normalizarVector(ti);
		/*Calculo autovector asociado al autovalor mas grande*/

		/*Auxiliares*/
		Matriz tit = trasponer(ti);
		Matriz ti_tit = ti.mult(tit);
		/*Auxiliares*/

		/*Actualizo X*/
		Matriz ti_tit_X = ti_tit.mult(X);
		X.restar(ti_tit_X);
		/*Actualizo X*/

		/*Actualizo Y*/
		Matriz ti_tit_Y = ti_tit.mult(Y);
		Y.restar(ti_tit_Y);
		/*Actualizo Y*/
	}
}