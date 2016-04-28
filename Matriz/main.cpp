#include "parser.cpp"



int main(int argc, char* argv[]){

	Matriz m = parser(argv[1],300);
	Matriz imagenesTest = parserImgTest(argv[1],301,400);
	for(int i = 0; i<imagenesTest.Filas(); i++){
		int res = m.caenene(7, imagenesTest.obtenerFila(i));
		if (res == imagenesTest.digitoRepresentado(i)){
			cout << "Funciona bien" << endl;
		} else {
			cout << "Funciona mal" << endl;
		}
	}
	/*
	if (( argc != 4 ) || (argv[3][0] != '0' && argv[3][0] != '1' && argv[3][0] != '2') ){
		printf("%s  [INPUT FILE] [OUTPUT FILE] [METHOD]\n", argv[0]);
		printf("Mete 0 para Gauss, 1 para Cholesky, 2 para WP\n");
	} else{
		
		Matriz m = parser(argv[1]);
		if (argv[3][0] == '0'){
			m.Gauss0();
			m.resolverTriangSup();
		} else if (argv[3][0] == '1'){
			m.cholesky();
		    m.resolverTriangInf();
		    m.resolverTriangSupTraspuesta();		    
		} else {
			rankingWP(argv[1], argv[2]);
			return 0;
		}
		
		FILE* out = fopen(argv[2], "w");
		m.ImprimirSolucion(out);
		fclose(out);			
		
	}
	*/

	return 0;
  
}