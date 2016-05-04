#include <sstream>
#include <fstream>
#include "Matriz.cpp"




Matriz parser(char* file, int cantImagenes){ // cantImagenes con -1 es equivalente a leer todas las imagenes

	Matriz m;
	
	ifstream in(file);
	if (in.is_open()){
		vector< vector <float> > mtx;
		vector<int> numeroRepresentado;

		// Parseo de la primer línea
		string str;
		getline(in, str);
		str.clear();


		// Parseo del resto del archivo
		string st;
		while (getline(in, st) && (cantImagenes != 0)){
			cantImagenes--;
			istringstream iss;
			iss.str(st);

			int numero;
			iss>> numero;
			numeroRepresentado.push_back(numero);
			char aux;
			iss>> aux;
			//Aca extraemos la info de la línea en la que estamos
			vector<float> img;
			for (int i = 0; i<784; i++){

				int pixel;
				iss>> pixel;
				iss>> aux;
				img.push_back(pixel);
			}
			mtx.push_back(img);

		}
		Matriz m(mtx,numeroRepresentado);
		return m;
	} else {
		cout << "No se pudo abrir el archivo." << endl;
	}
	
	return m;
}




Matriz parserImgTest(char* file, int imgDesde, int imgHasta){ 

	Matriz m;
	
	ifstream in(file);
	if (in.is_open()){
		vector< vector <float> > mtx;
		vector<int> numeroRepresentado;

		// Parseo de la primer línea
		string str;
		getline(in, str);
		str.clear();

		for(int i = 0; i< imgDesde-1; i++){
			getline(in, str);
			str.clear();
		}

		// Parseo del resto del archivo
		string st;
		while (getline(in, st) && (imgHasta-imgDesde != 0)){
			imgHasta--;
			istringstream iss;
			iss.str(st);

			int numero;
			iss>> numero;
			numeroRepresentado.push_back(numero);
			char aux;
			iss>> aux;
			//Aca extraemos la info de la línea en la que estamos
			vector<float> img;
			for (int i = 0; i<784; i++){

				int pixel;
				iss>> pixel;
				iss>> aux;
				img.push_back(pixel);
			}
			mtx.push_back(img);

		}
		Matriz m(mtx,numeroRepresentado);
		return m;
	} else {
		cout << "No se pudo abrir el archivo." << endl;
	}
	
	return m;
}