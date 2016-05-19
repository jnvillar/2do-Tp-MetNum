#include "../../Matriz/parser.cpp"



int main(int argc, char* argv[]){

	if (argc != 5){
		printf("%s  [INPUT FILE] [CANTIDAD IMAGENES TRAIN] [CANTIDAD IMAGENES TEST] [CANTIDAD DE VECINOS] \n", argv[0]);
		exit(1);
	}

	FILE* out = fopen("k.txt","w");

	for(int j = 0; j<30; j++){

		int cantTrain = atoi(argv[2]);
		int cantTest = atoi(argv[3]);
		Matriz m = parser(argv[1],cantTrain);
		Matriz imagenesTest = parserImgTest(argv[1],cantTrain+1,cantTrain+1+cantTest);
		int cantVecinos = atoi(argv[4])+j*1;


		//double tiempo = 0;
		double hitRate;
		for(int h = 0; h<1; h++){
		//	clock_t t = clock();

			int aciertos = 0;
			for(int i = 0; i<imagenesTest.Filas(); i++){
				vector<double> fila = imagenesTest.obtenerFila(i);
				int res = m.caenene(cantVecinos, fila);
				if (res == imagenesTest.digitoRepresentado(i)){
					aciertos++;
				} else {
				}
			}
			hitRate = (double )aciertos/(double )imagenesTest.Filas();
		//	t = clock() - t;
		//	tiempo += (((double)t)/CLOCKS_PER_SEC);
		}
		//tiempo = tiempo/50;
		//fprintf(out, "%f\n", tiempo);
		//cout << "tiempo: " << tiempo << endl;
		fprintf(out, "k: %d %f\n", cantVecinos, hitRate);
		cout << "hitRate: " << hitRate << endl;


	}
	fclose(out);
	return 0;
  
}