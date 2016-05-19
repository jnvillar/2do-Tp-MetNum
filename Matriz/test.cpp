#include "parser.cpp"



int main(int argc, char* argv[]){

	/* 				
	//					TEST MULTIPLICACION MATRIZ
	vector<double> fil1;
	vector<double> fil2;
	vector<double> fil3;
	fil1.push_back(1);
	fil1.push_back(2);
	fil1.push_back(3);

	fil2.push_back(4);
	fil2.push_back(5);
	fil2.push_back(6);

	fil3.push_back(7);
	fil3.push_back(8);
	fil3.push_back(9);

	vector< vector<double> > mtx;
	mtx.push_back(fil1); 
	mtx.push_back(fil2); 
	mtx.push_back(fil3); 

	vector<int> a;
	Matriz m(mtx,a);


	vector<double> fila1;
	vector<double> fila2;
	vector<double> fila3;
	fila1.push_back(1);
	fila1.push_back(0);

	fila2.push_back(3);
	fila2.push_back(5);

	fila3.push_back(4);
	fila3.push_back(2);

	vector< vector<double> > mtx2;
	mtx2.push_back(fila1); 
	mtx2.push_back(fila2); 
	mtx2.push_back(fila3);

	vector<int> b;
	Matriz m2(mtx2,b);

	Matriz res = m.mult(m2);
	res.imprimirMatriz(stdout);
	*/

/*
// 					MULTIPLICACION POR VECTOR
	vector<double> fil1;
	vector<double> fil2;
	vector<double> fil3;
	fil1.push_back(1);
	fil1.push_back(2);
	fil1.push_back(3);

	fil2.push_back(4);
	fil2.push_back(5);
	fil2.push_back(6);

	fil3.push_back(7);
	fil3.push_back(8);
	fil3.push_back(9);

	vector< vector<double> > mtx;
	mtx.push_back(fil1); 
	mtx.push_back(fil2); 
	mtx.push_back(fil3); 

	vector<int> a(3,0);
	Matriz m(mtx,a);

	vector<double> v;
	v.push_back(3);
	v.push_back(1);
	v.push_back(4);

	v = m.multVect(v,'d');
	for (int i = 0; i < v.size(); ++i)
	{
		cout << v[i] << "  ";
	}
	cout << endl;
*/



/*
	// 					TEST AUTOVALORES Y AUTOVECTORES
	vector<double> fil1;
	vector<double> fil2;
	vector<double> fil3;

	fil1.push_back(1);
	fil1.push_back(0);
	fil1.push_back(0);

	fil2.push_back(1);
	fil2.push_back(2);
	fil2.push_back(0);

	fil3.push_back(0);
	fil3.push_back(0);
	fil3.push_back(3);



	vector< vector<double> > mtx;
	mtx.push_back(fil1); 
	mtx.push_back(fil2); 
	mtx.push_back(fil3); 

	vector<int> a(3,0);
	Matriz m(mtx,a);
	//m.imprimirMatriz(stdout);
	vector< vector<double> > res = m.obtenerAutovectores(3,200);
	
	for (int i = 0; i < res.size(); ++i){
		for (int j = 0; j < res[i].size(); ++j){
			cout << res[i][j] << "   ";
		}
		cout << endl;
	}
*/

	/*
	// 					TEST TRASPONER
	vector<double> fil1;
	vector<double> fil2;
	vector<double> fil3;
	fil1.push_back(15);
	fil1.push_back(3);

	fil2.push_back(1);
	fil2.push_back(7);

	fil3.push_back(2);
	fil3.push_back(4);



	vector< vector<double> > mtx;
	mtx.push_back(fil1); 
	mtx.push_back(fil2); 
	mtx.push_back(fil3); 

	vector<int> a(3,0);
	Matriz m(mtx,a);
	m.imprimirMatriz();
	Matriz t = m.trasponer();
	t.imprimirMatriz();
	*/

/*
	//					TEST MULTIPLICACION MATRIZ MEJORADA
	vector<double> fil1;
	vector<double> fil2;
	vector<double> fil3;
	fil1.push_back(1);
	fil1.push_back(2);

	fil2.push_back(4);
	fil2.push_back(5);

	fil3.push_back(7);
	fil3.push_back(8);

	vector< vector<double> > mtx;
	mtx.push_back(fil1); 
	mtx.push_back(fil2); 
	mtx.push_back(fil3); 

	vector<int> a;
	Matriz m(mtx,a);


	Matriz m2 = m.trasponer();


	Matriz res = m2.mult(m);
	res.imprimirMatriz();

	Matriz res2 = m.multXtX();
	res2.imprimirMatriz();
*/


	return 0;
  
}