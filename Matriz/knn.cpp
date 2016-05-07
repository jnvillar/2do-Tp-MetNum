#include "parser.cpp"



int main(int argc, char* argv[]){

	if (argc != 3){
		printf("%s  [INPUT FILE] [CANTIDAD DE VECINOS] \n", argv[0]);
		exit(1);
	}

	Matriz m = parser(argv[1],3000);
	Matriz imagenesTest = parserImgTest(argv[1],3001,3101);

	int cantVecinos = atoi(argv[2]);

	int aciertos = 0;
	for(int i = 0; i<imagenesTest.Filas(); i++){
		vector<float> fila = imagenesTest.obtenerFila(i);
		int res = m.caenene(cantVecinos, fila);
		if (res == imagenesTest.digitoRepresentado(i)){
			aciertos++;
			cout << i << ": Funciona bien" << endl;
		} else {
			cout << i << ": Funciona mal" << endl;
		}
	}
	float hitRate = (float )aciertos/(float )imagenesTest.Filas();
	cout << hitRate << endl;

	return 0;
  
}