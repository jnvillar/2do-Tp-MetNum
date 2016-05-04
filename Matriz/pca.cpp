#include "parser.cpp"



int main(int argc, char* argv[]){

	Matriz imagenesTrain = parser(argv[1],3000);
	Matriz imagenesTest = parserImgTest(argv[1],3001,3101);
	vector<int> digitoRepr = imagenesTrain.obtenerDigitos();
	vector<int> digitoRepr2 = imagenesTest.obtenerDigitos();
	Matriz imagenesTrainReducida = imagenesTrain.pca();
	Matriz imagenesTestReducida = imagenesTest.pca();
	imagenesTrainReducida.cambiarDigitos(digitoRepr);
	for(int i = 0; i<imagenesTest.Filas(); i++){
		vector<float> fila = imagenesTestReducida.obtenerFila(i);
		int res = imagenesTrainReducida.caenene(7, fila);
		if (res == digitoRepr[i]){
			cout << i << ": Funciona bien" << endl;
		} else {
			cout << i << ": Funciona mal" << endl;
		}
	}
	
	return 0;
  
}