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

	//Guardamos digitos que representa cada imagen del train y del test
	Matriz imagenesTrain = parser(argv[1],3000);
	Matriz imagenesTest = parserImgTest(argv[1],3001,3101);
	// Matriz imagenesTrain2 = imagenesTrain;
	
	int cantIterPls = atoi(argv[2]);
	int cantIterMetPot = atoi(argv[3]);
	int cantVecinos = atoi(argv[4]);

	//Guardamos digitos que representa cada imagen del train y del test
	vector<int> digitoRepr = imagenesTrain.obtenerDigitos();
	vector<int> digitoRepr2 = imagenesTest.obtenerDigitos();

	//Calculamos preY 
	Matriz Y = preY(digitoRepr);
	//Le restamos la media y dividimos por sqrt(n-1) para obtener Y
	Y.restarMedia(Y);

	//Calculamos el cambio de base mediante pls-da
	vector< vector<float> > cambioBase = imagenesTrain.pls_da(imagenesTrain,Y,cantIterPls,cantIterMetPot);

	//Aplicamos el cambio de base al train y al test
	Matriz imagenesTrainReducida = imagenesTrain.cambioDeBase(cambioBase);

	//Le restamos la media del train y dividimos por sqrt(n-1) a las imagenes del test
	imagenesTest.restarMedia(imagenesTrain); //ESTO FUNCIONA PORQUE EN pls_da imagenesTrain ya no se toma por referencia

	//Aplicamos el cambio de base al test
	Matriz imagenesTestReducida = imagenesTest.cambioDeBase(cambioBase);

	//Le asignamos los digitos que antes guardamos a la matriz (pues con las otras funciones sino se pierden)
	imagenesTrainReducida.cambiarDigitos(digitoRepr);

	//Hacemos el reconocimiento de digitos mediante kNN y comparamos los resultados con los valores reales
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