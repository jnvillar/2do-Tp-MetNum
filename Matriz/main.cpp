#include "parser.cpp"
#include <stdio.h>
#include <string.h>


int main(int argc, char* argv[]){


	char* file = argv[1];			// archivo entrada
	char* fileOut = argv[2];			// archivo salida
	int metodo = atoi(argv[3]); 	// metodo




	Matriz test;
	Matriz train;
	
	
	ifstream inTest(file);


		
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
		ifstream in(trainPath);			// train.csv
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

		double hitRatePca = usarPca(train,test,alpha,40,k);
		double hitRatePls = usarPls(train,test,gamma,40,k);

		FILE* out = fopen("hitRate.out","a");
        fprintf(out, "Hit rate pca: Particion %d: %f\n", j+1, hitRatePca);
        fprintf(out, "Hit rate pls: Particion %d: %f\n", j+1, hitRatePls);
        fclose(out);
	}
	



	char* trainPath2 = new char[trainPath.length() + 1];
	strcpy(trainPath2, trainPath.c_str());
	

	char* testPath2 = new char[testPath.length() + 1];
	strcpy(testPath2, testPath.c_str());



	train = parser(trainPath2,-1);
	test = parserTest2(testPath2,-1);

	delete [] trainPath2;
	delete [] testPath2;

	vector<int> res;

	imprimir = false;
	if (metodo == 0){
		res = utilizarKnn(train,test,k);
	} else if (metodo == 1){
		res = utilizarPcaMejorado(train,test,alpha,40,k);
	} else if (metodo == 2){
		res = utilizarPlsMejorado(train,test,gamma,40,k);
	}

	FILE* testOut = fopen(fileOut,"a");
	fprintf(testOut, "ImageId,Label\n");
	for (int i = 0; i < res.size(); ++i){
		fprintf(testOut, "%d,%d\n", i+1,res[i]);
	}
	fclose(testOut);
	


	return 0;
  
}