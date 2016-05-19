#include "parser.cpp"



int main(int argc, char* argv[]){

	char* file = argv[1];			// test.in
	

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

		iss2 >> a;

		iss2 >> k;

		iss2 >> alpha;

		iss2 >> gamma;

		iss2 >> K;
		str2.clear();
		for(int j=0; j<K; j++){

			char* file2 = argv[2]; 		// train.cvs
			ifstream in(file2);
			vector< vector <double> > mtxTest;
			vector< vector <double> > mtxTrain;
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
				vector<double> img;
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

			//usarPca(train,test,alpha,40,k);
			usarPls(train,test,gamma,40,k);

		}

		
	} else {
		cout << "No se pudo abrir el archivo." << endl;
	}

	return 0;
  
}