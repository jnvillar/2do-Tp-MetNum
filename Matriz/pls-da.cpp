#include "parser.cpp"


Matriz preY(vector<int> dig){
	vector< vector<float> > mtx;
	for (int i = 0; i<dig.size(); i++){
		vector<float> fil(10,-1);
		fil[dig[i]] = 1;
		mtx.push_back(fil);
	}
	vector<int> a(dig.size(),0);
	Matriz res(mtx,a);
	return res;
}


int main(int argc, char* argv[]){

	if (argc != 5){
		printf("%s  [INPUT FILE] [CANTIDAD ITERACIONES PLS] [CANTIDAD ITERACIONES METODO POTENCIA] [CANTIDAD VECINOS]\n", argv[0]);
		exit(1);
	}

	Matriz imagenesTrain = parser(argv[1],3000);
	Matriz imagenesTest = parserImgTest(argv[1],3001,3101);

	int cantIterPls = atoi(argv[2]);
	int cantIterMetPot = atoi(argv[3]);
	int cantVecinos = atoi(argv[4]);

	vector<int> digitoRepr = imagenesTrain.obtenerDigitos();
	vector<int> digitoRepr2 = imagenesTest.obtenerDigitos();

	Matriz Y = preY(digitoRepr);
	Y.restarMedia(Y);


	vector< vector<float> > cambioBase = imagenesTrain.pls_da(imagenesTrain,Y,cantIterPls,cantIterMetPot);

	Matriz imagenesTrainReducida = imagenesTrain.cambioDeBase(cambioBase);
	Matriz imagenesTestReducida = imagenesTest.cambioDeBase(cambioBase);

	imagenesTrainReducida.cambiarDigitos(digitoRepr);
	imagenesTestReducida.cambiarDigitos(digitoRepr2);

	for(int i = 0; i<imagenesTest.Filas(); i++){
		vector<float> fila = imagenesTestReducida.obtenerFila(i);
		int res = imagenesTrainReducida.caenene(cantVecinos, fila);
		if (res == digitoRepr2[i]){
			cout << i << ": Funciona bien" << endl;
		} else {
			cout << i << ": Funciona mal" << endl;
		}
	}
	



	return 0;
	
}