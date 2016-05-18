#include "../../Matriz/parser.cpp"



int main(int argc, char* argv[]){

	bool debug = true;

	if (argc != 9){
		printf("%s  [1 INPUT FILE] [2 CANTIDAD IMAGENES TRAIN INICIAL] [3 AUMTENTAR TRAIN EN] [4 ITERACIONES] [5 PSA: ALPHA] [6 PLS-DA: GAMMA] [7 CANTIDAD DE VECINOS] [8 OTLIERS]\n", argv[0]);
		exit(1);
	}

	int cantTrain = atoi(argv[2]);		
	int aumentarTrain = atoi(argv[3]);	
	int iteraciones = atoi(argv[4]);
	int alfa = atoi(argv[5]);
	int gamma = atoi(argv[6]);
	int cantVecinos = atoi(argv[7]);
	int outliers = atoi(argv[8]);

	ofstream out1; 
	out1.open("calidadPca.txt");
	ofstream out2; 
	out2.open("tiemposPls.txt");
	ofstream out3; 
	out3.open("tiemposKnn.txt");
	

	for(int j = 0; j<iteraciones; j++){
	
		if(debug) cout << "Iteracion: "<<  j <<  " Imagenes: " <<cantTrain+(aumentarTrain*j) << endl;

		if(debug) cout << "Parseando "<<  endl;
		Matriz trainPca = parser(argv[1],cantTrain+(aumentarTrain*j));
		Matriz trainPls = parser(argv[1],cantTrain+(aumentarTrain*j));
		Matriz trainKnn = parser(argv[1],cantTrain+(aumentarTrain*j));

		

		Matriz testPca = parserImgTest(argv[1],40000,42000);
		Matriz testPls = parserImgTest(argv[1],40000,42000);
		Matriz testKnn = parserImgTest(argv[1],40000,42000);

	

		float tiempoPca = 0;
		float tiempoPls = 0;
		float tiempoKnn = 0;			

		for(int h = 0; h<outliers; h++){

			if(debug) cout << "PCA" << endl;
			clock_t t1 = clock();
			float hitrate1 = usarPca(trainPca,testPca,alfa,20,cantVecinos);		
			t1 = clock() - t1;
			tiempoPca += (((float)t1)/CLOCKS_PER_SEC);
			if(debug) cout << "Tiempos PCA "<<  tiempoPca << endl;

			if(debug) cout << "PLS" << endl;
			clock_t t2 = clock();
			vector<int> digitoRepr = trainPls.obtenerDigitos(); digitoRepr = trainPls.obtenerDigitos();
			Matriz Y = preY(digitoRepr);
			Y.restarMedia(Y);
			float hitrate2 = usarPls(trainPls,testPls,alfa,20,cantVecinos);		
			t2 = clock() - t2;
			tiempoPls += (((float)t2)/CLOCKS_PER_SEC);
			if(debug) cout << "Tiempos PLS" << tiempoPls << endl;

			if(debug) cout << "Knn" << endl;
			clock_t t3 = clock();
			float hitrate3 = usarKnn(trainKnn,testKnn,20);		
			t1 = clock() - t1;
			tiempoKnn += (((float)t1)/CLOCKS_PER_SEC);
			if(debug) cout << "Tiempos Knn" << tiempoKnn << endl;
		}		

		tiempoPca = tiempoPca/outliers;
		tiempoPls = tiempoPls/outliers;	
		tiempoKnn = tiempoKnn/outliers;

		out1 << tiempoPca << endl;		
		out2 <<  tiempoPls << endl;
		out3 << tiempoPls << endl;		
		
	}

	out1.close();
	out2.close();
	out3.close();
	return 0;
  
}