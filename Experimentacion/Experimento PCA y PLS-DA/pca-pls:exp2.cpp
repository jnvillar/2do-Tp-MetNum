#include "../../Matriz/parser.cpp"



int main(int argc, char* argv[]){

	if (argc != 6){
		printf("%s  [1 INPUT FILE] [2 ALPHA Y GAMMA INCIAL] [3 AUMENTAR ALPHA Y GAMMA] [4 ITERACIONES] [5 OUTLIERS] \n", argv[0]);
		exit(1);
	}

	int cantTrain = 20000;	
	int alfa = atoi(argv[2]);
	int gamma = atoi(argv[2]);
	int aumento = atoi(argv[3]);
	int iteraciones = atoi(argv[4]);	
	int outliers = atoi(argv[5]);

	FILE* out1 = fopen("resultPca2.txt","w");
	FILE* out2 = fopen("resultPls2.txt","w");

	for(int j = 0; j<iteraciones; j++){				

		Matriz trainPca = parser(argv[1],cantTrain);
		Matriz trainPls = parser(argv[1],cantTrain);
		float tiempoPca = 0;
		float tiempoPls = 0;		

		for(int h = 0; h<outliers; h++){
			clock_t t1 = clock();
			vector< vector<float> > cambioBase1 = trainPca.pca(alfa+(aumento*j),20);		
			t1 = clock() - t1;
			tiempoPca += (((float)t1)/CLOCKS_PER_SEC);

			clock_t t2 = clock();
			vector<int> digitoRepr = trainPls.obtenerDigitos();
			Matriz Y = preY(digitoRepr);
			Y.restarMedia(Y);
			vector< vector<float> > cambioBase2 = trainPls.pls_da(trainPls,Y,(gamma+(aumento*j),20);		
			t2 = clock() - t2;
			tiempoPls += (((float)t2)/CLOCKS_PER_SEC);
		}		

		tiempoPca = tiempoPca/outliers;
		tiempoPls = tiempoPls/outliers;		

		fprintf(out1, "%f\n", tiempoPca);		
		cout << "tiempoPca: " << tiempoPca << endl;		

		fprintf(out2, "%f\n", tiempoPls);		
		cout << "tiempoPls: " << tiempoPls << endl;	

		cout << j << endl;
	}

	fclose(out1);
	fclose(out2);
	return 0;
  
}