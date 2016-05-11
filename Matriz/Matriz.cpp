#include <vector>
#include <algorithm>
#include <cassert>
#include <iostream>
#include <sstream>
#include <vector>
#include <math.h>
#include <fstream>
#include <tuple>
 using namespace std;

int debug = 0;

class Matriz{

    private:
        vector< vector <float> > m;
        int filas;
        int cols;
        vector<int> digitos;
        // El vector en la posicion "i" de m es una imagen del digito en la posicion "i" de digitos

        //Devuelve el resultado de la resta vectorial entre v1 y v2 (v1-v2)
        vector<float> resta(const vector<float>& v1,const vector<float>& v2) const{
            vector<float> res;
            for (int i = 0; i < v1.size(); ++i) {
                res.push_back(v1[i]-v2[i]);
            }
            return res;
        }

        //Devuelve el resultado de la norma vectorial 2 realizada sobre el vector v
        float norma2(const vector<float>& v) const{
            float sum = 0;
            for (int i = 0; i < v.size(); ++i)
            {
                sum += v[i]*v[i];
            }
            return sqrt(sum);           
        }

        //Devuelve el digito que más cantidad de veces aparece como segunda coordenada en los pares contenidos por el vector 
        int masVotado(const vector<pair<float,int> >& v) const{
            vector<int> counting(10,0);
            for (int i = 0; i < v.size(); ++i) {
                counting[v[i].second]++;
            }
            int max = 0;
            for (int i = 0; i < 10; ++i)
            {
                if(counting[i]>counting[max]){
                    max = i;
                }
            }
            return max;
        }
        
    public: 
        //Constructor de matriz por defecto
        Matriz() {}

        //Constructor de matriz llena de ceros dadas la cantidad de filas y columnas
        Matriz(int fils, int columnas){
            m.clear();
            vector<float> fil(columnas,0);
            vector< vector<float> > mtx(fils,fil);
            m = mtx;
            filas = fils;
            cols = columnas;
            vector<int> dig(fils,0);
            digitos = dig;
        };

        //Constructor de matriz al cual le damos como argumentos el conjunto de imagenes (dado como un vector de vectores) y los digitos que representa cada una
        Matriz(vector< vector <float> > mtx, vector<int> num){
            m.clear();
            m = mtx;
            filas = mtx.size();
            cols = mtx[0].size();   
            digitos = num;
        };


        //Devuelve el numero de filas de la matriz 
        int Filas() const{
            return filas;
        }

        //Devuelve el numero de columnas de la matriz
        int Columnas() const{
            return cols;
        }

        //Reemplaza el valor en la posicion i,j de la matriz por v 
        void modValor(int i, int j, float v){
            m[i][j] = v;
            return;
        }

        //Devuelve el valor en la posicion i,j de la matriz
        float obtenerValor(int i, int j) const{
            return m[i][j];
        }

        //Devuelve la fila i de la matriz
        vector<float> obtenerFila(int i) const{
            return m[i];
        }
        
        //Devuelve el dígito que representa la imagen representada por la fila i de la matriz 
        int digitoRepresentado(int i){
            return digitos[i];
        }

        void cambiarDigitos(vector<int> dig){
            digitos = dig;
            return;
        }

        vector<int> obtenerDigitos(){
            return digitos;
        }

        //Imprime la matriz por cout
        void imprimirMatriz(){
            cout << "Imprimiendo matriz\n";
            for (int i = 0; i < filas; i++){    
                cout << "|";            
                for (int j = 0; j < cols; j++){
                    if(m[i][j] < 0){                    
                        cout << m[i][j];
                    }else{
                        cout << " " << m[i][j]; 
                    } 
                    if(j == cols-1){
                         // fprintf(out, "| %d \n", digitos[i]);
                         cout << "| \n" ;
                    } else{ 
                        cout << "  ";
                    }                                   
                }           
            }
            cout << "\n";
        }

        //Método kNN para asignarle un digito a una imagen dada
        int caenene(int k, const vector<float>& img) const{
            
            vector<pair<float,int> > normas;
            vector<pair<float,int> > kmenores;
            pair<float,int> res;            
            for (int i = 0; i < filas; ++i) {       
                vector<float> rest = resta(m[i],img);
                res.first = norma2(rest);
                res.second = digitos[i];
                normas.push_back(res);                              
            }

            sort(normas.begin(), normas.end());
            for (int i = 0; i < k; ++i) {
                kmenores.push_back(normas[i]);
            }

            int result;
            result = masVotado(kmenores);
            return result;
        }

        //Devuelve el resultado del producto matricial m*m2 
        Matriz mult(const Matriz &m2) const{
            if(debug == 1) cout << "mult" << endl;
            Matriz res(filas, m2.Columnas());
            if(debug == 1) cout << "ciclo" << endl;
            for (int i = 0; i < filas; ++i){
                for (int j = 0; j < m2.Columnas(); ++j){
                    float sumaProd = 0;
                    for (int h = 0; h < cols; ++h){
                        sumaProd += m[i][h] * m2.obtenerValor(h,j);
                    }
                    res.modValor(i,j,sumaProd);
                }
            }
            if(debug == 1) cout << "ciclo 2" << endl;

            if(debug == 1) cout << "mult 2" << endl;

            return res;
        }

        Matriz* multXtX() const{
            if(debug == 1) cout << "multXtX" << endl;
            Matriz* res = new Matriz(cols, cols);
            if(debug == 1) cout << "ciclo" << endl;
            for (int i = 0; i < cols; ++i){
                for (int j = 0; j <=i; ++j){
                    float sumaProd = 0;
                    for (int h = 0; h < filas; ++h){
                        sumaProd += m[h][i] * m[h][j];
                    }
                    res->modValor(i,j,sumaProd);
                    res->modValor(j,i,sumaProd);
                }
            }
            if(debug == 1) cout << "ciclo 2" << endl;

            if(debug == 1) cout << "multXtX 2" << endl;

            return res;
        }

        Matriz* multXXt() const{
            if(debug == 1) cout << "multXXt" << endl;
            Matriz* res = new Matriz(filas, filas);
            if(debug == 1) cout << "ciclo" << endl;
            for (int i = 0; i < filas; ++i){
                for (int j = 0; j <=i; ++j){
                    float sumaProd = 0;
                    for (int h = 0; h < cols; ++h){
                        sumaProd += m[i][h] * m[j][h];
                    }
                    res->modValor(i,j,sumaProd);
                    res->modValor(j,i,sumaProd);
                }
            }
            if(debug == 1) cout << "ciclo 2" << endl;

            if(debug == 1) cout << "multXXt 2" << endl;

            return res;
        }


        //Devuelve el resultado del producto matricial m*v si lado = d (derecha); y v*m si lado = i (izquierda)  
        vector<float> multxVect(const vector<float>& v, char lado) const{
            vector<float> res;
            if (lado == 'i'){
                for (int i = 0; i < cols; ++i){
                    float num = 0;
                    for (int j = 0; j < v.size(); ++j){
                        num += v[j]*m[j][i];
                    }
                    res.push_back(num);
                }
            } else if (lado == 'd'){
                for (int i = 0; i < filas; ++i){
                    float num = 0;
                    for (int j = 0; j < v.size(); ++j){
                        num += v[j]*m[i][j];
                    }
                    res.push_back(num);
                }
            } else {
                if(debug == 1) cout << "SOS UN GIL" << endl;
                exit(1);
            }
            return res;
        }

        // Modifica v
        void multxVect2(vector<float>& v, char lado) const{
            vector<float> copiaV = v;
            if (lado == 'i'){
                for (int i = 0; i < cols; ++i){
                    float num = 0;
                    for (int j = 0; j < v.size(); ++j){
                        num += copiaV[j]*m[j][i];
                    }
                    v[i] = num;
                }
            } else if (lado == 'd'){
                for (int i = 0; i < filas; ++i){
                    float num = 0;
                    for (int j = 0; j < v.size(); ++j){
                        num += copiaV[j]*m[i][j];
                    }
                    v[i] = num;
                }
            } else {
                if(debug == 1) cout << "SOS UN GIL" << endl;
                exit(1);
            }
            return;
        }

        //Calcula la media entre los elementos de cada una de las columnas de la matriz pasada como parametro y luego se la resta a cada elemento de la columna de la matriz del objeto respectivamente. Ademas divide por sqrt(n-1) cada elemento
        void restarMedia(const Matriz& mtx){
            // CALCULAMOS LAS MEDIAS
            vector<float> media(cols,0);
            for (int i = 0; i < filas; ++i){
                for (int j = 0; j < cols; ++j){
                    media[j] += mtx.obtenerValor(i,j);
                }
            }
            for (int i = 0; i<media.size(); i++){
                media[i] = media[i]/mtx.Filas();
            }

            // RESTAMOS Y DIVIDIMOS
            float divi = sqrt(filas-1);
            for (int i = 0; i < filas; ++i){
                for (int j = 0; j < cols; ++j){
                    m[i][j] = (m[i][j]-media[j])/divi;
                }
            }

        }

        void normalizarVector(vector<float>& v) const{
            float normV = norma2(v);
            for (int j = 0; j < v.size(); ++j)  {
                v[j] = v[j]/normV;
            }   
        }

        //Metodo de la potencia para obtener autovalor de modulo maximo y su autovector asociado
        pair<vector<float>,float> metodoPotencia(int iter) const{
            /*Genero Vector Random*/
            srand (time(NULL));
            vector<float> v;
            for (int i = 0; i < filas; ++i) {
                v.push_back(rand());
            }
            
            normalizarVector(v);
                
            /*Genero Vector Random*/

        
            
            /*Calculo Autovector*/
            for (int i = 0; i < iter; ++i) {
                multxVect2(v,'d');
                normalizarVector(v);
            }
            /*Calculo Autovector*/
            

            /*Calculo Autovalor*/
            vector<float> Bv = multxVect(v,'d');
            float vtBv = 0;
            for (int i = 0; i < v.size(); ++i){
                vtBv += v[i]*Bv[i];
            }
            float vtv = pow(norma2(v),2);
            float autovalor = vtBv/vtv;
            /*Calculo Autovalor*/

            pair<vector<float>,float> res;
            res.first =  v;
            res.second = autovalor;
            FILE* out = fopen("test1.out","a");
            fprintf(out, "%e\n", autovalor);
            fclose(out);
            return res;
        }

        
        //Devuelve el conjunto de autovectores de la matriz calculados mediante el metodo de la potencia y luego aplicando deflacion
        vector< vector<float> > obtenerAutovectores(int cantAutov, int cantIterMetPot) const{
            if(debug == 1) cout << "obtenerAutovectores " << endl;

            vector< vector<float> > res;
            vector<int> a(filas,0);
            Matriz mtx(m,a);

            for (int h = 0; h<cantAutov; h++){
                if(debug == 1) cout << h << endl;

                //Aplico metodo de la potencia para obtener autovalor de modulo maximo y su autovector asociado
                pair<vector<float>,float> autov = mtx.metodoPotencia(cantIterMetPot);

                vector<float> v = autov.first;
                res.push_back(v);

                //Deflacion
                //Calculo v*vt
                vector< vector <float> > mat;
                for (int i = 0; i<v.size(); i++){
                    vector <float> fil;
                    for (int j = 0; j < v.size(); j++){
                        fil.push_back(v[i]*v[j]);
                    }
                    mat.push_back(fil);
                }

                // Deflacion
                // Generamos matriz que tiene el resto de los autovalores iguales y 0
                for (int i = 0; i<filas; i++){
                    for (int j = 0; j < cols; j++){
                        mtx.modValor(i,j, mtx.obtenerValor(i,j) - autov.second * mat[i][j]);
                    }
                }   
            }
exit(0);
            return res;
        }

        void restaMatrices(const Matriz& m2){
            for (int i = 0; i<filas; i++){
                for (int j = 0; j < cols; j++){
                    m[i][j] -= m2.obtenerValor(i,j);
                }
            }
        }

        Matriz* cambioDeBase(const vector< vector<float> >& p){
            if(debug == 1) cout << "cambioDeBase " << endl;

            vector<int> a(p.size(),0);
            Matriz vt(p,a);
            Matriz* xt = trasponer(); 
            Matriz rest = vt.mult(*xt);
            delete xt;

            Matriz* res = rest.trasponer();


            return res;
        }


        //Devuelve la matriz traspuesta
        Matriz* trasponer(){
            if(debug == 1) cout << "trasponer " << endl;

            vector<vector<float> > mtx;
            for (int i = 0; i < cols; ++i) {
                vector<float> fila;
                for (int j = 0; j < filas; ++j) {
                    fila.push_back(obtenerValor(j,i));
                }
                mtx.push_back(fila);
            }
            vector<int> digitos(cols,0);
            Matriz* res = new Matriz(mtx,digitos);
            if(debug == 1) cout << "trasponer 2" << endl;

            return res;
        }

        


        vector< vector<float> > pca(int cantAutov, int cantIterMetPot) const{
            if(debug == 1) cout << "pca " << endl;
            Matriz aux = *this;
            aux.restarMedia(aux);

            if(debug == 1) cout << "Mx " << endl;   
            Matriz* mx = aux.multXtX();

            vector< vector<float> > p = mx->obtenerAutovectores(cantAutov,cantIterMetPot);
            delete mx;
            return p;
        }

        


        vector<vector<float> > pls_da(Matriz& X, Matriz& Y, int iteraciones, int metpot) const{
            

            X.restarMedia(X);

            vector< vector<float> > autovec;

            for (int i = 0; i < iteraciones; ++i) {

                /*Calculo M*/
                Matriz* Xt = X.trasponer();
                Matriz XtY = Xt->mult(Y);
                delete Xt;
                Matriz* mi = XtY.multXXt();         
                /*Calculo M*/


                /*Calculo autovector asociado al autovalor mas grande*/     
                pair<vector<float>,float> Mayor; //(Autovector Asociado, Mayor autovalor)

                Mayor = mi->metodoPotencia(metpot); //ya esta normalizado
                delete mi;

                vector<float> ti = X.multxVect(Mayor.first,'d');    
                autovec.push_back(Mayor.first); // Guardo autovector
                normalizarVector(ti);
                /*Calculo autovector asociado al autovalor mas grande*/


                
                vector<float> tit_X = X.multxVect(ti,'i');


                vector< vector <float> > mat;
                for (int h = 0; h<ti.size(); h++){
                    vector <float> fil;
                    for (int j = 0; j < tit_X.size(); j++){
                        fil.push_back(ti[h]*tit_X[j]);
                    }
                    mat.push_back(fil);
                }
               

                vector<int> a(ti.size(),0);
                Matriz ti_tit_X(mat,a);
                X.restaMatrices(ti_tit_X);


                vector <float> tit_Y = Y.multxVect(ti,'i');
                vector< vector <float> > mat2;
                for (int h = 0; h<ti.size(); h++){
                    vector <float> fil;
                    for (int j = 0; j < tit_Y.size(); j++){
                        fil.push_back(ti[h]*tit_Y[j]);
                    }
                    mat2.push_back(fil);
                }
                vector<int> a2(ti.size(),0);
                Matriz ti_tit_Y(mat2,a);
                Y.restaMatrices(ti_tit_Y);
                
            }
            
            return autovec;
        }




        Matriz subMatriz(int desde, int hasta){
            vector< vector <float> > mtx;
            vector<int> dig;
            for (int i = desde; i < hasta; ++i){
                mtx.push_back(obtenerFila(i));
                dig.push_back(digitoRepresentado(i));
            }
            Matriz res(mtx,dig);
            return res;
        }
        
        Matriz subMatriz(int desde1, int hasta1, int desde2, int hasta2){
            vector< vector <float> > mtx;
            vector<int> dig;
            for (int i = desde1; i < hasta1; ++i){
                mtx.push_back(obtenerFila(i));
                dig.push_back(digitoRepresentado(i));
            }
            for (int i = desde2; i < hasta2; ++i){
                mtx.push_back(obtenerFila(i));
                dig.push_back(digitoRepresentado(i));
            }
            Matriz res(mtx,dig);
            return res;
        }


};

Matriz preY(vector<int> dig){
    vector< vector<float> > mtx;
    for (int i = 0; i<dig.size(); i++){
        vector<float> fil(10,-1);
        fil[dig[i]] = 1;
        mtx.push_back(fil);
    }
    vector<int> a(dig.size(),0);
    Matriz res(mtx,a);
    return res;
}



float usarPca(Matriz imagenesTrain, Matriz imagenesTest, int cantAutov, int cantIterMetPot, int cantVecinos){
    vector<int> digitoRepr = imagenesTrain.obtenerDigitos();
    vector<int> digitoRepr2 = imagenesTest.obtenerDigitos();

    //Calculamos el cambio de base mediante pca
    vector< vector<float> > cambioBase = imagenesTrain.pca(cantAutov,cantIterMetPot);
    
    //Le restamos la media del train y dividimos por sqrt(n-1) a las imagenes del test
    imagenesTest.restarMedia(imagenesTrain);        
    imagenesTrain.restarMedia(imagenesTrain);       

    //Aplicamos el cambio de base al train
    Matriz* imagenesTrainReducida = imagenesTrain.cambioDeBase(cambioBase); // imagenesTrain con o sin media?
    
    
    //Aplicamos el cambio de base al test
    Matriz* imagenesTestReducida = imagenesTest.cambioDeBase(cambioBase);

    //Le asignamos a la matriz los digitos que antes guardamos (pues con las otras funciones sino se pierden)
    imagenesTrainReducida->cambiarDigitos(digitoRepr);

    //Hacemos el reconocimiento de digitos mediante kNN y comparamos los resultados con los valores reales
    int aciertos = 0;
    for(int i = 0; i<imagenesTest.Filas(); i++){
        vector<float> fila = imagenesTestReducida->obtenerFila(i);
        int res = imagenesTrainReducida->caenene(cantVecinos, fila);
        if (res == digitoRepr2[i]){
            aciertos++;
            cout << i << ": Funciona bien" << endl;
        } else {
            cout << i << ": Funciona mal" << endl;
        }
    }
    float hitRate = (float )aciertos/(float )imagenesTest.Filas();
    delete imagenesTrainReducida;
    delete imagenesTestReducida;
    return hitRate;
}


float usarPls(Matriz imagenesTrain, Matriz imagenesTest, int cantIterPls, int cantIterMetPot, int cantVecinos){

    //Guardamos digitos que representa cada imagen del train y del test
    vector<int> digitoRepr = imagenesTrain.obtenerDigitos();
    vector<int> digitoRepr2 = imagenesTest.obtenerDigitos();

    //Calculamos preY 
    Matriz Y = preY(digitoRepr);

    //Le restamos la media y dividimos por sqrt(n-1) para obtener Y
    Y.restarMedia(Y);

    Matriz X = imagenesTrain;

    //Calculamos el cambio de base mediante pls-da
    vector< vector<float> > cambioBase = imagenesTrain.pls_da(X,Y,cantIterPls,cantIterMetPot);


    //Le restamos la media del train y dividimos por sqrt(n-1) a las imagenes del test
    imagenesTest.restarMedia(imagenesTrain); 
    imagenesTrain.restarMedia(imagenesTrain); 


    //Aplicamos el cambio de base al train y al test
    Matriz* imagenesTrainReducida = imagenesTrain.cambioDeBase(cambioBase); // imagenesTrain con o sin media?

    

    //Aplicamos el cambio de base al test
    Matriz* imagenesTestReducida = imagenesTest.cambioDeBase(cambioBase);

    //Le asignamos los digitos que antes guardamos a la matriz (pues con las otras funciones sino se pierden)
    imagenesTrainReducida->cambiarDigitos(digitoRepr);

    //Hacemos el reconocimiento de digitos mediante kNN y comparamos los resultados con los valores reales
    int aciertos = 0;
    for(int i = 0; i<imagenesTest.Filas(); i++){
        vector<float> fila = imagenesTestReducida->obtenerFila(i);
        int res = imagenesTrainReducida->caenene(cantVecinos, fila);
        if (res == digitoRepr2[i]){
            aciertos++;
            cout << i << ": Funciona bien" << endl;
        } else {
            cout << i << ": Funciona mal" << endl;
        }
    }
    float hitRate = (float )aciertos/(float )imagenesTest.Filas();
    delete imagenesTrainReducida;
    delete imagenesTestReducida;
    return hitRate;
}




float usarKnn(Matriz imagenesTrain, Matriz imagenesTest, int cantVecinos){
    int aciertos = 0;
    for(int i = 0; i<imagenesTest.Filas(); i++){
        vector<float> fila = imagenesTest.obtenerFila(i);
        int res = imagenesTrain.caenene(cantVecinos, fila);
        if (res == imagenesTest.digitoRepresentado(i)){
            aciertos++;
            cout << i << ": Funciona bien" << endl;
        } else {
            cout << i << ": Funciona mal" << endl;
        }
    }
    float hitRate = (float )aciertos/(float )imagenesTest.Filas();
    return hitRate;
}
