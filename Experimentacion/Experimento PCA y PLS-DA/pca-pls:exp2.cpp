#include "../../Matriz/parser.cpp"
#include <iostream>
#include <ctime>
#include <sstream>
#include <fstream>




int main(int argc, char* argv[]){

	if (argc != 7){
		printf("%s  [1 INPUT FILE] [2 ALPHA Y GAMMA INCIAL] [3 AUMENTAR ALPHA Y GAMMA] [4 ITERACIONES] [5 OUTLIERS] [6 CANT IMAGENES]\n", argv[0]);
		exit(1);
	}

	int cantTrain = atoi((argv[6]));	
	int alfa = atoi(argv[2]);
	int gamma = atoi(argv[2]);
	int aumento = atoi(argv[3]);
	int iteraciones = atoi(argv[4]);	
	int outliers = atoi(argv[5]);

	ofstream out1; 
	out1.open("resultPca2.txt");
	ofstream out2; 
	out2.open("resultPls2.txt");

	for(int j = 0; j<iteraciones; j++){				

		Matriz trainPca = parser(argv[1],cantTrain);
		Matriz trainPls = parser(argv[1],cantTrain);
		double tiempoPca = 0;
		double tiempoPls = 0;		

		for(int h = 0; h<outliers; h++){
			clock_t t1 = clock();
			vector< vector<double> > cambioBase1 = trainPca.pca(alfa+(aumento*j),20);		
			t1 = clock() - t1;
			tiempoPca += (((double)t1)/CLOCKS_PER_SEC);

			clock_t t2 = clock();
			vector<int> digitoRepr = trainPls.obtenerDigitos();
			Matriz Y = preY(digitoRepr);
			Y.restarMedia(Y);
			vector< vector<double> > cambioBase2 = trainPls.pls_da(trainPls,Y,gamma+(aumento*j),20);		
			t2 = clock() - t2;
			tiempoPls += (((double)t2)/CLOCKS_PER_SEC);
		}		

		tiempoPca = tiempoPca/outliers;
		tiempoPls = tiempoPls/outliers;

		
		out1 << tiempoPca << endl;				
		cout << "tiempoPca: " << tiempoPca << endl;		

		out2 << tiempoPls << endl;	
		cout << "tiempoPls: " << tiempoPls << endl;	

		cout << j << endl;
	}

	out1.close();
	out2.close();
	return 0;
  
}