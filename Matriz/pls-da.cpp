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

	vector<vector<float> > autovec = pls_da(X,Y,iteraciones,argv[3]);

	X.cambioDeBase(autovec);


	
}