#include "../Matriz/parser.cpp"





int main(int argc, char* argv[]){

	if (argc != 3){
		printf("%s  [INPUT FILE] [OUTPUT FILE]\n", argv[0]);
		exit(1);
	}


	FILE* out = fopen(argv[2], "w");

	char* file = argv[1];
	ifstream in(file);
	if (in.is_open()){
		vector< vector <float> > mtx;
		vector<int> numeroRepresentado;

		// Parseo de la primer línea
		string str;
		getline(in, str);

		fprintf(out, "Linea inutil\n");

		str.clear();


		// Parseo del resto del archivo
		string st;
		while (getline(in, st)){
			istringstream iss;
			iss.str(st);

			int numero;
			//Extraemos digito que representa la imagen
			iss>> numero;
			numeroRepresentado.push_back(numero);
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
			mtx.push_back(img);

		}
		for (int i = 0; i < 42000; ++i){
			int a = rand()%42000;
			int b = rand()%42000;
			if (a != b){
				vector<float> swap = mtx[a];
				mtx[a] = mtx[b];
				mtx[b] = swap;

				int swap2 = numeroRepresentado[a];
				numeroRepresentado[a] = numeroRepresentado[b];
				numeroRepresentado[b] = swap2;
			}
		}

		for (int i = 0; i < 42000; ++i){
			fprintf(out, "%d,", numeroRepresentado[i]);
			for (int j = 0; j<784; j++){
				if(j != 783){
					fprintf(out, "%d,", (int )mtx[i][j]);
				} else {
					fprintf(out, "%d \n", (int )mtx[i][j]);
				}
			}
		}

	}
	fclose(out);
	return 0;
  
}