#include "parser.cpp"
#include <stdio.h>
#include <string.h>


float usarPca(Matriz imagenesTrain, Matriz imagenesTest, int cantAutov, int cantIterMetPot, int cantVecinos){
	vector<int> digitoRepr = imagenesTrain.obtenerDigitos();
	vector<int> digitoRepr2 = imagenesTest.obtenerDigitos();

	//Calculamos el cambio de base mediante pca
	vector< vector<float> > cambioBase = imagenesTrain.pca(cantAutov,cantIterMetPot);
	
	//Le restamos la media del train y dividimos por sqrt(n-1) a las imagenes del test
	imagenesTest.restarMedia(imagenesTrain);		
	imagenesTrain.restarMedia(imagenesTrain);		

	//Aplicamos el cambio de base al train
	Matriz imagenesTrainReducida = imagenesTrain.cambioDeBase(cambioBase); // imagenesTrain con o sin media?
	
	
	//Aplicamos el cambio de base al test
	Matriz imagenesTestReducida = imagenesTest.cambioDeBase(cambioBase);

	//Le asignamos a la matriz los digitos que antes guardamos (pues con las otras funciones sino se pierden)
	imagenesTrainReducida.cambiarDigitos(digitoRepr);

	//Hacemos el reconocimiento de digitos mediante kNN y comparamos los resultados con los valores reales
	int aciertos = 0;
	for(int i = 0; i<imagenesTest.Filas(); i++){
		vector<float> fila = imagenesTestReducida.obtenerFila(i);
		int res = imagenesTrainReducida.caenene(cantVecinos, fila);
		if (res == digitoRepr2[i]){
			aciertos++;
			cout << i << ": Funciona bien" << endl;
		} else {
			cout << i << ": Funciona mal" << endl;
		}
	}
	float hitRate = (float )aciertos/(float )imagenesTest.Filas();
	return hitRate;
}




int main(int argc, char* argv[]){
	if(strcmp(argv[1],"pca") == 0){
		int cantIm = atoi(argv[3]);
		Matriz imagenes = parser(argv[2],cantIm); 	// ENTRADA, CANTIDAD DE IMAGENES

		int cantAutov = atoi(argv[4]);
		int cantIterMetPot = atoi(argv[5]);
		int cantVecinos = atoi(argv[6]);
		int k = atoi(argv[7]);

		int tamConj = cantIm/k;
		vector<float> hitRate;
		for(int i = 0; i<k; i++){
			Matriz test = imagenes.subMatriz(i*tamConj,(i+1)*tamConj);
			Matriz train = imagenes.subMatriz(0,i*tamConj,(i+1)*tamConj,cantIm);
			float hR = usarPca(train,test,cantAutov,cantIterMetPot,cantVecinos);
			hitRate.push_back(hR);
		}
		float hR = 0;
		for (int i = 0; i < hitRate.size(); ++i){
			hR += hitRate[i];
		}
		hR = hR/(float) hitRate.size();
		cout << "HitRate: " << hR << endl;	
	}

	
	return 0;
  
}

/*
int main(int argc, char* argv[]){


	Matriz imagenes = parser(argv[1],5000);

	int cantAutov = atoi(argv[2]);
	int cantIterMetPot = atoi(argv[3]);
	int cantVecinos = atoi(argv[4]);
	int k = atoi(argv[5]);

	int tamConj = 5000/k;
	vector<float> hitRate;
	for(int i = 0; i<k; i++){
		Matriz test = imagenes.subMatriz(i*tamConj,(i+1)*tamConj);
		Matriz train = imagenes.subMatriz(0,i*tamConj,(i+1)*tamConj,5000);
		float hR = usarPca(train,test,cantAutov,cantIterMetPot,cantVecinos);
		hitRate.push_back(hR);
	}
	float hR = 0;
	for (int i = 0; i < hitRate.size(); ++i){
		hR += hitRate[i];
	}
	hR = hR/(float) hitRate.size();
	cout << "HitRate: " << hR << endl;
	return 0;
  
}
*/