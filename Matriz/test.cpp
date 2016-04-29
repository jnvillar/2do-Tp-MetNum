#include "parser.cpp"



int main(int argc, char* argv[]){

	vector<float> fil1;
	vector<float> fil2;
	vector<float> fil3;
	fil1.push_back(1);
	fil1.push_back(2);
	fil1.push_back(3);

	fil2.push_back(4);
	fil2.push_back(5);
	fil2.push_back(6);

	fil3.push_back(7);
	fil3.push_back(8);
	fil3.push_back(9);

	vector< vector<float> > mtx;
	mtx.push_back(fil1); 
	mtx.push_back(fil2); 
	mtx.push_back(fil3); 

	vector<int> a;
	Matriz m(mtx,a);


	vector<float> fila1;
	vector<float> fila2;
	vector<float> fila3;
	fila1.push_back(1);
	fila1.push_back(0);

	fila2.push_back(3);
	fila2.push_back(5);

	fila3.push_back(4);
	fila3.push_back(2);

	vector< vector<float> > mtx2;
	mtx2.push_back(fila1); 
	mtx2.push_back(fila2); 
	mtx2.push_back(fila3);

	vector<int> b;
	Matriz m2(mtx2,b);

	Matriz res = m.mult(m2);
	res.imprimirMatriz(stdout);

	return 0;
  
}