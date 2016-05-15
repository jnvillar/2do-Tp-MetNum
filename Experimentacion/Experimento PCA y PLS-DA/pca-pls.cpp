#include "../../Matriz/parser.cpp"



int main(int argc, char* argv[]){

	if (argc != 6){
		printf("%s  [1 INPUT FILE] [2 CANTIDAD IMAGENES TRAIN INICIAL] [3 AUMTENTAR TRAIN EN] [4 ITERACIONES] [5 PSA: ALPHA] [6 PLS-DA: GAMMA] \n", argv[0]);
		exit(1);
	}

	int cantTrain = atoi(argv[2]);		
	int aumentarTrain = atoi(argv[3]);	
	int iteraciones = atoi(argv[4]);
	int alfa = atoi(argv[5]);
	int gamma = atoi(argv[6]);
	FILE* out1 = fopen("resultPca.txt","w");
	FILE* out2 = fopen("resultPls.txt","w");

	for(int j = 0; j<iteraciones; j++){				

		Matriz trainPca = parser(argv[1],cantTrain+(aumentarTrain*j));
		Matriz trainPls = parser(argv[1],cantTrain+(aumentarTrain*j));
		float tiempoPca = 0;
		float tiempoPls = 0;		

		for(int h = 0; h<20; h++){
			clock_t t1 = clock();
			vector< vector<float> > cambioBase1 = trainPca.pca(alfa,20);		
			t1 = clock() - t1;
			tiempoPca += (((float)t1)/CLOCKS_PER_SEC);

			clock_t t2 = clock();
			vector<int> digitoRepr = trainPls.obtenerDigitos();
			Matriz Y = preY(digitoRepr);
			Y.restarMedia(Y);
			vector< vector<float> > cambioBase2 = trainPls.pls_da(trainPls,Y,gamma,20);		
			t2 = clock() - t2;
			tiempoPls += (((float)t2)/CLOCKS_PER_SEC);
		}		

		tiempoPca = tiempoPca/20;
		tiempoPls = tiempoPls/20;		

		fprintf(out1, "%f\n", tiempoPca);		
		cout << "tiempoPca: " << tiempoPca << endl;		

		fprintf(out2, "%f\n", tiempoPls);		
		cout << "tiempoPls: " << tiempoPls << endl;	
	}

	fclose(out1);
	fclose(out2);
	return 0;
  
}