#include "../../Matriz/parser.cpp"



int main(int argc, char* argv[]){

	if (argc != 5){
		printf("%s  [INPUT FILE] [CANTIDAD IMAGENES TRAIN] [CANTIDAD IMAGENES TEST] [CANTIDAD DE VECINOS] \n", argv[0]);
		exit(1);
	}

	int cantTrain = atoi(argv[2]);
	int cantTest = atoi(argv[3]);
	Matriz m = parser(argv[1],cantTrain);
	Matriz imagenesTest = parserImgTest(argv[1],cantTrain+1,cantTrain+1+cantTest);

	int cantVecinos = atoi(argv[4]);

	float tiempo = 0;
	float hitRate;
	for(int h = 0; h<50; h++){
		clock_t t = clock();


		int aciertos = 0;
		for(int i = 0; i<imagenesTest.Filas(); i++){
			vector<float> fila = imagenesTest.obtenerFila(i);
			int res = m.caenene(cantVecinos, fila);
			if (res == imagenesTest.digitoRepresentado(i)){
				aciertos++;
			} else {
			}
		}
		hitRate = (float )aciertos/(float )imagenesTest.Filas();
		t = clock() - t;
		tiempo += (((float)t)/CLOCKS_PER_SEC);
	}
		tiempo = tiempo/50;
		cout << "tiempo: " << tiempo << endl;
		cout << "hitRate: " << hitRate << endl;

	return 0;
  
}