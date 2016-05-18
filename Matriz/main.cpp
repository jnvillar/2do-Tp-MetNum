#include "parser.cpp"



int main(int argc, char* argv[]){


	char* file = argv[1];			// archivo entrada
	char* fileOut = argv[2];			// archivo salida
	int metodo = atoi(argv[3]); 	// metodo


	imprimir = fileOut;


	Matriz test;
	Matriz train;
	
	
	ifstream inTest(file);
	if (inTest.is_open()){
		

		
		string str2;
		getline(inTest, str2);
		istringstream iss2;
		iss2.str(str2);

		string a;

		int k;
		int alpha;
		int gamma;
		int K;

		iss2 >> a;		// path

		string trainPath = a+"train.csv";
		string testPath = a+"test.csv";

		iss2 >> k;

		iss2 >> alpha;

		iss2 >> gamma;

		iss2 >> K;
		str2.clear();
		for(int j=0; j<K; j++){

			ifstream in(a);			// train.csv
			vector< vector <float> > mtxTest;
			vector< vector <float> > mtxTrain;
			vector<int> numeroReprTrain;
			vector<int> numeroReprTest;

			// Parseo de la primer línea
			string str;
			getline(in, str);
			str.clear();


			// Parseo test.in
			string strTest;

			getline(inTest, strTest);
			istringstream issTest;
			issTest.str(strTest);


			// Parseo del resto del archivo train
			string st;
			while (getline(in, st)){
				istringstream iss;
				iss.str(st);

				int numero;
				//Extraemos digito que representa la imagen
				iss>> numero;
				char aux;
				iss>> aux;
				//Aca extraemos la info de la línea en la que estamos
				vector<float> img;
				for (int i = 0; i<784; i++){

					int pixel;
					//Extraemos pixel
					iss>> pixel;
					//Extraemos espacio en blanco (solo para avanzar)
					iss>> aux;
					img.push_back(pixel);
				}

				int asd;
				issTest >> asd;
				if (asd == 1){
					mtxTrain.push_back(img);
					numeroReprTrain.push_back(numero);

				} else {
					mtxTest.push_back(img);
					numeroReprTest.push_back(numero);

				}

			}

			Matriz train(mtxTrain,numeroReprTrain);
			Matriz test(mtxTest,numeroReprTest);

			float hitRatePca = usarPca(train,test,alpha,40,k);
			float hitRatePls = usarPls(train,test,gamma,40,k);

			FILE* out = fopen("hitRate.out","a");
            fprintf(out, "Hit rate pca: Particion %d: %f\n", j+1, hitRatePca);
            fprintf(out, "Hit rate pls: Particion %d: %f\n", j+1, hitRatePls);
            fclose(out);
		}

		
	} else {
		cout << "No se pudo abrir el archivo." << endl;
	}

	return 0;
  
}