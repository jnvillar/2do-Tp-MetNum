#include "parser.cpp"





int main(int argc, char* argv[]){

	if (argc != 5){
		printf("%s  [INPUT FILE] [CANTIDAD AUTOVECTORES] [CANTIDAD ITERACIONES METODO POTENCIA] [CANTIDAD VECINOS]\n", argv[0]);
		exit(1);
	}

	//Parseo de imagenes del train y del test
	Matriz imagenesTrain = parser(argv[1],3000);
	Matriz imagenesTest = parserImgTest(argv[1],3001,3101);

	int cantAutov = atoi(argv[2]);
	int cantIterMetPot = atoi(argv[3]);
	int cantVecinos = atoi(argv[4]);

	//Guardamos digitos que representa cada imagen del train y del test
	vector<int> digitoRepr = imagenesTrain.obtenerDigitos();
	vector<int> digitoRepr2 = imagenesTest.obtenerDigitos();

	//Calculamos el cambio de base mediante pca
	vector< vector<float> > cambioBase = imagenesTrain.pca(cantAutov,cantIterMetPot);
	
	//Le restamos la media del train y dividimos por sqrt(n-1) a las imagenes del test
	imagenesTest.restarMedia(imagenesTrain);		
	imagenesTrain.restarMedia(imagenesTrain);		

	//Aplicamos el cambio de base al train
	Matriz imagenesTrainReducida = imagenesTrain.cambioDeBase(cambioBase); // imagenesTrain con o sin media?


	
	
	//Aplicamos el cambio de base al test
	Matriz imagenesTestReducida = imagenesTest.cambioDeBase(cambioBase);

	//Le asignamos a la matriz los digitos que antes guardamos (pues con las otras funciones sino se pierden)
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