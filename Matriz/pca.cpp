#include "parser.cpp"



int main(int argc, char* argv[]){

	Matriz m = parser(argv[1],3000);
	Matriz imagenesTest = parserImgTest(argv[1],3001,3101);
	vector<int> digitoRepr = m.obtenerDigitos();
	vector<int> digitoRepr2 = imagenesTest.obtenerDigitos();
	Matriz mReducida = m.pca();
	mReducida.cambiarDigitos(digitoRepr);
	for(int i = 0; i<imagenesTest.Filas(); i++){
		vector<float> fila = imagenesTest.obtenerFila(i);
		int res = mReducida.caenene(50, fila);
		if (res == digitoRepr[i]){
			cout << i << ": Funciona bien" << endl;
		} else {
			cout << i << ": Funciona mal" << endl;
		}
	}
	
	return 0;
  
}