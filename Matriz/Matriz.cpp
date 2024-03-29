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
bool imprimir = true;
class Matriz{

    private:
        vector< vector <double> > m;
        int filas;
        int cols;
        vector<int> digitos;
        // El vector en la posicion "i" de m es una imagen del digito en la posicion "i" de digitos

        //Devuelve el resultado de la resta vectorial entre v1 y v2 (v1-v2)
        vector<double> resta(const vector<double>& v1,const vector<double>& v2) const{
            vector<double> res;
            for (int i = 0; i < v1.size(); ++i) {
                res.push_back(v1[i]-v2[i]);
            }
            return res;
        }

        //Devuelve el resultado de la norma vectorial 2 realizada sobre el vector v
        double norma2(const vector<double>& v) const{
            double sum = 0;
            for (int i = 0; i < v.size(); ++i)
            {
                sum += v[i]*v[i];
            }
            return sqrt(sum);           
        }

        //Devuelve el digito que más cantidad de veces aparece como segunda coordenada en los pares contenidos por el vector 
        int masVotado(const vector<pair<double,int> >& v) const{
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
        
        int masVotadoMejorado(const vector<pair<double,int> >& v) const{
            vector<double> counting(10,0);
            for (int i = 0; i < v.size(); ++i) {
                if (v[i].first == 0){
                    return v[i].second;
                }
                counting[v[i].second] += 1/ (double) v[i].first;
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
            vector<double> fil(columnas,0);
            vector< vector<double> > mtx(fils,fil);
            m = mtx;
            filas = fils;
            cols = columnas;
            vector<int> dig(fils,0);
            digitos = dig;
        };

        //Constructor de matriz al cual le damos como argumentos el conjunto de imagenes (dado como un vector de vectores) y los digitos que representa cada una
        Matriz(vector< vector <double> > mtx, vector<int> num){
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
        void modValor(int i, int j, double v){
            m[i][j] = v;
            return;
        }

        //Devuelve el valor en la posicion i,j de la matriz
        double obtenerValor(int i, int j) const{
            return m[i][j];
        }

        //Devuelve la fila i de la matriz
        vector<double> obtenerFila(int i) const{
            return m[i];
        }
        
        //Devuelve el dígito que representa la imagen representada por la fila i de la matriz 
        int digitoRepresentado(int i) const{
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
        int caenene(int k, const vector<double>& img) const{
            
            vector<pair<double,int> > normas;
            vector<pair<double,int> > kmenores;
            pair<double,int> res;            
            for (int i = 0; i < filas; ++i) {       
                vector<double> rest = resta(m[i],img);
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


        int caeneneMejorado(int k, const vector<double>& img) const{
            
            vector<pair<double,int> > normas;
            vector<pair<double,int> > kmenores;
            pair<double,int> res;            
            for (int i = 0; i < filas; ++i) {       
                vector<double> rest = resta(m[i],img);
                res.first = norma2(rest);
                res.second = digitos[i];
                normas.push_back(res);                              
            }

            sort(normas.begin(), normas.end());
            for (int i = 0; i < k; ++i) {
                kmenores.push_back(normas[i]);
            }

            int result;
            result = masVotadoMejorado(kmenores);
            return result;
        }





        //Devuelve el resultado del producto matricial m*m2 
        Matriz mult(const Matriz &m2) const{
            if(debug == 1) cout << "mult" << endl;
            Matriz res(filas, m2.Columnas());
            if(debug == 1) cout << "ciclo" << endl;
            for (int i = 0; i < filas; ++i){
                for (int j = 0; j < m2.Columnas(); ++j){
                    double sumaProd = 0;
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

        Matriz multXtX() const{
            if(debug == 1) cout << "multXtX" << endl;
            Matriz res(cols, cols);
            if(debug == 1) cout << "ciclo" << endl;
            for (int i = 0; i < cols; ++i){
                for (int j = 0; j <=i; ++j){
                    double sumaProd = 0;
                    for (int h = 0; h < filas; ++h){
                        sumaProd += m[h][i] * m[h][j];
                    }
                    res.modValor(i,j,sumaProd);
                    res.modValor(j,i,sumaProd);
                }
            }
            if(debug == 1) cout << "ciclo 2" << endl;

            if(debug == 1) cout << "multXtX 2" << endl;

            return res;
        }

        Matriz multXXt() const{
            if(debug == 1) cout << "multXXt" << endl;
            Matriz res(filas, filas);
            if(debug == 1) cout << "ciclo" << endl;
            for (int i = 0; i < filas; ++i){
                for (int j = 0; j <=i; ++j){
                    double sumaProd = 0;
                    for (int h = 0; h < cols; ++h){
                        sumaProd += m[i][h] * m[j][h];
                    }
                    res.modValor(i,j,sumaProd);
                    res.modValor(j,i,sumaProd);
                }
            }
            if(debug == 1) cout << "ciclo 2" << endl;

            if(debug == 1) cout << "multXXt 2" << endl;

            return res;
        }


        //Devuelve el resultado del producto matricial m*v si lado = d (derecha); y v*m si lado = i (izquierda)  
        vector<double> multxVect(const vector<double>& v, char lado) const{
            vector<double> res;
            if (lado == 'i'){
                for (int i = 0; i < cols; ++i){
                    double num = 0;
                    for (int j = 0; j < v.size(); ++j){
                        num += v[j]*m[j][i];
                    }
                    res.push_back(num);
                }
            } else if (lado == 'd'){
                for (int i = 0; i < filas; ++i){
                    double num = 0;
                    for (int j = 0; j < v.size(); ++j){
                        num += v[j]*m[i][j];
                    }
                    res.push_back(num);
                }
            }
            return res;
        }

        // Modifica v
        void multxVect2(vector<double>& v, char lado) const{
            vector<double> copiaV = v;
            if (lado == 'i'){
                for (int i = 0; i < cols; ++i){
                    double num = 0;
                    for (int j = 0; j < v.size(); ++j){
                        num += copiaV[j]*m[j][i];
                    }
                    v[i] = num;
                }
            } else if (lado == 'd'){
                for (int i = 0; i < filas; ++i){
                    double num = 0;
                    for (int j = 0; j < v.size(); ++j){
                        num += copiaV[j]*m[i][j];
                    }
                    v[i] = num;
                }
            } 
            return;
        }

        //Calcula la media entre los elementos de cada una de las columnas de la matriz pasada como parametro y luego se la resta a cada elemento de la columna de la matriz del objeto respectivamente. Ademas divide por sqrt(n-1) cada elemento
        void restarMedia(const Matriz& mtx){
            // CALCULAMOS LAS MEDIAS
            vector<double> media(cols,0);
            for (int i = 0; i < filas; ++i){
                for (int j = 0; j < cols; ++j){
                    media[j] += mtx.obtenerValor(i,j);
                }
            }
            for (int i = 0; i<media.size(); i++){
                media[i] = media[i]/mtx.Filas();
            }

            // RESTAMOS Y DIVIDIMOS
            double divi = sqrt(filas-1);
            for (int i = 0; i < filas; ++i){
                for (int j = 0; j < cols; ++j){
                    m[i][j] = (m[i][j]-media[j])/divi;
                }
            }

        }

        void normalizarVector(vector<double>& v) const{
            double normV = norma2(v);
            for (int j = 0; j < v.size(); ++j)  {
                v[j] = v[j]/normV;
            }   
        }

        //Metodo de la potencia para obtener autovalor de modulo maximo y su autovector asociado
        pair<vector<double>,double> metodoPotencia(int iter) const{
            /*Genero Vector Random*/
            srand (time(NULL));
            vector<double> v;
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
            vector<double> Bv = multxVect(v,'d');
            double vtBv = 0;
            for (int i = 0; i < v.size(); ++i){
                vtBv += v[i]*Bv[i];
            }
            double vtv = pow(norma2(v),2);
            double autovalor = vtBv/vtv;
            /*Calculo Autovalor*/

            pair<vector<double>,double> res;
            res.first =  v;
            res.second = autovalor;

            if (imprimir == true){
                FILE* out = fopen("autov.out","a");
                fprintf(out, "%e\n", autovalor);
                fclose(out);
            }
         
            return res;
        }

        
        //Devuelve el conjunto de autovectores de la matriz calculados mediante el metodo de la potencia y luego aplicando deflacion
        vector< vector<double> > obtenerAutovectores(int cantAutov, int cantIterMetPot) const{
            if(debug == 1) cout << "obtenerAutovectores " << endl;

            vector< vector<double> > res;
            vector<int> a(filas,0);
            Matriz mtx(m,a);

            for (int h = 0; h<cantAutov; h++){
                if(debug == 1) cout << h << endl;

                //Aplico metodo de la potencia para obtener autovalor de modulo maximo y su autovector asociado
                pair<vector<double>,double> autov = mtx.metodoPotencia(cantIterMetPot);

                vector<double> v = autov.first;
                res.push_back(v);

                //Deflacion
                //Calculo v*vt
                vector< vector <double> > mat;
                for (int i = 0; i<v.size(); i++){
                    vector <double> fil;
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
            return res;
        }

        void restaMatrices(const Matriz& m2){
            for (int i = 0; i<filas; i++){
                for (int j = 0; j < cols; j++){
                    m[i][j] -= m2.obtenerValor(i,j);
                }
            }
        }

        Matriz cambioDeBase(const vector< vector<double> >& p){
            if(debug == 1) cout << "cambioDeBase " << endl;

            vector<int> a(p.size(),0);
            Matriz vt(p,a);
            Matriz xt = trasponer(); 
            Matriz rest = vt.mult(xt);

            Matriz res = rest.trasponer();


            return res;
        }


        //Devuelve la matriz traspuesta
        Matriz trasponer(){
            if(debug == 1) cout << "trasponer " << endl;

            vector<vector<double> > mtx;
            for (int i = 0; i < cols; ++i) {
                vector<double> fila;
                for (int j = 0; j < filas; ++j) {
                    fila.push_back(obtenerValor(j,i));
                }
                mtx.push_back(fila);
            }
            vector<int> digitos(cols,0);
            Matriz res(mtx,digitos);
            if(debug == 1) cout << "trasponer 2" << endl;

            return res;
        }

        


        vector< vector<double> > pca(int cantAutov, int cantIterMetPot) const{
            if(debug == 1) cout << "pca " << endl;
            Matriz aux = *this;
            aux.restarMedia(aux);

            if(debug == 1) cout << "Mx " << endl;   
            Matriz mx = aux.multXtX();

            vector< vector<double> > p = mx.obtenerAutovectores(cantAutov,cantIterMetPot);
            return p;
        }

        


        vector<vector<double> > pls_da(Matriz& X, Matriz& Y, int iteraciones, int metpot) const{
            

            X.restarMedia(X);

            vector< vector<double> > autovec;

            for (int i = 0; i < iteraciones; ++i) {

                /*Calculo M*/
                Matriz Xt = X.trasponer();
                Matriz XtY = Xt.mult(Y);
                Matriz mi = XtY.multXXt();         
                /*Calculo M*/


                /*Calculo autovector asociado al autovalor mas grande*/     
                pair<vector<double>,double> Mayor; //(Autovector Asociado, Mayor autovalor)

                Mayor = mi.metodoPotencia(metpot); //ya esta normalizado

                vector<double> ti = X.multxVect(Mayor.first,'d');    
                autovec.push_back(Mayor.first); // Guardo autovector
                normalizarVector(ti);
                /*Calculo autovector asociado al autovalor mas grande*/


                
                vector<double> tit_X = X.multxVect(ti,'i');


                vector< vector <double> > mat;
                for (int h = 0; h<ti.size(); h++){
                    vector <double> fil;
                    for (int j = 0; j < tit_X.size(); j++){
                        fil.push_back(ti[h]*tit_X[j]);
                    }
                    mat.push_back(fil);
                }
               

                vector<int> a(ti.size(),0);
                Matriz ti_tit_X(mat,a);
                X.restaMatrices(ti_tit_X);


                vector <double> tit_Y = Y.multxVect(ti,'i');
                vector< vector <double> > mat2;
                for (int h = 0; h<ti.size(); h++){
                    vector <double> fil;
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




        Matriz subMatriz(int desde, int hasta) const{
            vector< vector <double> > mtx;
            vector<int> dig;
            for (int i = desde; i < hasta; ++i){
                mtx.push_back(obtenerFila(i));
                dig.push_back(digitoRepresentado(i));
            }
            Matriz res(mtx,dig);
            return res;
        }
        
        Matriz subMatriz(int desde1, int hasta1, int desde2, int hasta2) const{
            vector< vector <double> > mtx;
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
    vector< vector<double> > mtx;
    for (int i = 0; i<dig.size(); i++){
        vector<double> fil(10,-1);
        fil[dig[i]] = 1;
        mtx.push_back(fil);
    }
    vector<int> a(dig.size(),0);
    Matriz res(mtx,a);
    return res;
}

vector< vector<double> > MatConf(){
    vector<double> fila(10,0);
    vector<vector<double> > mat;
    for (int i = 0; i < 10; ++i)
    {
        mat.push_back(fila);
    }
    return mat;
}


vector< vector<double> > calcularMetricas(vector<int> VP, vector<int> FP, vector<int> FN){

    //Calculo de precision
    vector<double> precision;
    double total_prec = 0;
    for (int i = 0; i < 10; i++)
    {
        //Calculo precision del digito i y lo sumo a total_prec para calcular promedio de precisiones
        double precision_i = (double ) VP[i]/((double ) VP[i] + (double ) FP[i]);
        precision.push_back(precision_i);
        total_prec += precision_i;
    }
    total_prec = total_prec/10;
    //La ultima posicion del vector contiene el promedio
    precision.push_back(total_prec);


    //Calculo de recall
    vector<double> recall;
    double total_recall = 0;
    for (int i = 0; i < 10; i++)
    {
        //Calculo recall del digito i y lo sumo a total_recall para calcular promedio de los recall
        double recall_i = (double ) VP[i]/((double ) VP[i] + (double ) FN[i]);
        recall.push_back(recall_i);
        total_recall += recall_i;
    }
    total_recall = total_recall/10;
    //La ultima posicion del vector contiene el promedio
    recall.push_back(total_recall);

    //Calculo de f1-score
    vector<double> f1Score;
    double total_f1Score = 0;
    for (int i = 0; i < 10; i++)
    {
        //Calculo recall del digito i y lo sumo a total_recall para calcular promedio de los recall
        double f1Score_i = (2 * precision[i] * recall[i]) / (precision[i] + recall[i]);
        f1Score.push_back(f1Score_i);
        total_f1Score += f1Score_i;
    }
    total_f1Score = total_f1Score/10;
    //La ultima posicion del vector contiene el promedio
    f1Score.push_back(total_f1Score);

    vector< vector<double> > res;
    res.push_back(precision);
    res.push_back(recall);
    res.push_back(f1Score);

    return res;
}


 double usarPca(Matriz imagenesTrain, Matriz imagenesTest, int cantAutov, int cantIterMetPot, int cantVecinos){
     vector<int> digitoRepr = imagenesTrain.obtenerDigitos();
     vector<int> digitoRepr2 = imagenesTest.obtenerDigitos();

     //Calculamos el cambio de base mediante pca
     vector< vector<double> > cambioBase = imagenesTrain.pca(cantAutov,cantIterMetPot);
    
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
         vector<double> fila = imagenesTestReducida.obtenerFila(i);
         int res = imagenesTrainReducida.caenene(cantVecinos, fila);
         if (res == digitoRepr2[i]){
             aciertos++;
           //  cout << i << ": Funciona bien" << endl;
         } else {
             //cout << i << ": Funciona mal" << endl;
         }
     }
     double hitRate = (double )aciertos/(double )imagenesTest.Filas();
 
     return hitRate;
 }



pair<vector< vector<double> >,vector< vector<double> > > usarPca2(Matriz imagenesTrain, Matriz imagenesTest, int cantAutov, int cantIterMetPot, int cantVecinos){
    vector<int> digitoRepr = imagenesTrain.obtenerDigitos();
    vector<int> digitoRepr2 = imagenesTest.obtenerDigitos();

    //Calculamos el cambio de base mediante pca
    vector< vector<double> > cambioBase = imagenesTrain.pca(cantAutov,cantIterMetPot);
    
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

    //Para calcular metricas precision, recall y f1-score 
    vector<int> VP(10, 0);
    vector<int> FP(10, 0);
    vector<int> FN(10, 0);
    vector<vector<double> > matConf = MatConf();

    for(int i = 0; i<imagenesTest.Filas(); i++){
        vector<double> fila = imagenesTestReducida.obtenerFila(i);
        int res = imagenesTrainReducida.caenene(cantVecinos, fila);
        if (res == digitoRepr2[i]){
            matConf[res][res]++;
            aciertos++;
            VP[res]++;
        } else {
            matConf[digitoRepr2[i]][res]++;
            FP[res]++;
            FN[digitoRepr2[i]]++;
        }
    }
    //Calculo de hit rate. En este caso es un vector de un elemento porque no es por digito
    vector<double> hitRate;
    hitRate.push_back((double )aciertos/(double )imagenesTest.Filas());

    //Calculo precision, recall y f1-score
    vector< vector<double> > metricas = calcularMetricas(VP, FP, FN);

    //Agregamos el hit rate
    metricas.push_back(hitRate);

    pair<vector< vector<double> >,vector< vector<double> > > res;
    res.first = metricas;
    res.second = matConf;

    return res;
}


 double usarPls(Matriz imagenesTrain, Matriz imagenesTest, int cantIterPls, int cantIterMetPot, int cantVecinos){

     //Guardamos digitos que representa cada imagen del train y del test
     vector<int> digitoRepr = imagenesTrain.obtenerDigitos();
     vector<int> digitoRepr2 = imagenesTest.obtenerDigitos();

     //Calculamos preY 
     Matriz Y = preY(digitoRepr);

     //Le restamos la media y dividimos por sqrt(n-1) para obtener Y
     Y.restarMedia(Y);

     Matriz X = imagenesTrain;

     //Calculamos el cambio de base mediante pls-da
     vector< vector<double> > cambioBase = imagenesTrain.pls_da(X,Y,cantIterPls,cantIterMetPot);


     //Le restamos la media del train y dividimos por sqrt(n-1) a las imagenes del test
     imagenesTest.restarMedia(imagenesTrain); 
     imagenesTrain.restarMedia(imagenesTrain); 


     //Aplicamos el cambio de base al train y al test
     Matriz imagenesTrainReducida = imagenesTrain.cambioDeBase(cambioBase); // imagenesTrain con o sin media?

    

     //Aplicamos el cambio de base al test
     Matriz imagenesTestReducida = imagenesTest.cambioDeBase(cambioBase);

     //Le asignamos los digitos que antes guardamos a la matriz (pues con las otras funciones sino se pierden)
     imagenesTrainReducida.cambiarDigitos(digitoRepr);

     //Hacemos el reconocimiento de digitos mediante kNN y comparamos los resultados con los valores reales
     int aciertos = 0;
     for(int i = 0; i<imagenesTest.Filas(); i++){
         vector<double> fila = imagenesTestReducida.obtenerFila(i);
         int res = imagenesTrainReducida.caenene(cantVecinos, fila);
         if (res == digitoRepr2[i]){
             aciertos++;
             //cout << i << ": Funciona bien" << endl;
         } else {
             //cout << i << ": Funciona mal" << endl;
         }
     }
     double hitRate = (double )aciertos/(double )imagenesTest.Filas();

     return hitRate;
 }



pair<vector< vector<double> >,vector< vector<double> > > usarPls2(Matriz imagenesTrain, Matriz imagenesTest, int cantIterPls, int cantIterMetPot, int cantVecinos){

    //Guardamos digitos que representa cada imagen del train y del test
    vector<int> digitoRepr = imagenesTrain.obtenerDigitos();
    vector<int> digitoRepr2 = imagenesTest.obtenerDigitos();

    //Calculamos preY 
    Matriz Y = preY(digitoRepr);

    //Le restamos la media y dividimos por sqrt(n-1) para obtener Y
    Y.restarMedia(Y);

    Matriz X = imagenesTrain;

    //Calculamos el cambio de base mediante pls-da
    vector< vector<double> > cambioBase = imagenesTrain.pls_da(X,Y,cantIterPls,cantIterMetPot);


    //Le restamos la media del train y dividimos por sqrt(n-1) a las imagenes del test
    imagenesTest.restarMedia(imagenesTrain); 
    imagenesTrain.restarMedia(imagenesTrain); 


    //Aplicamos el cambio de base al train y al test
    Matriz imagenesTrainReducida = imagenesTrain.cambioDeBase(cambioBase); // imagenesTrain con o sin media?

    

    //Aplicamos el cambio de base al test
    Matriz imagenesTestReducida = imagenesTest.cambioDeBase(cambioBase);

    //Le asignamos los digitos que antes guardamos a la matriz (pues con las otras funciones sino se pierden)
    imagenesTrainReducida.cambiarDigitos(digitoRepr);

    //Hacemos el reconocimiento de digitos mediante kNN y comparamos los resultados con los valores reales
    int aciertos = 0;

    //Para calcular metricas precision, recall y f1-score 
    vector<int> VP(10, 0);
    vector<int> FP(10, 0);
    vector<int> FN(10, 0);
    vector<vector<double> > matConf = MatConf();

    for(int i = 0; i<imagenesTest.Filas(); i++){
        vector<double> fila = imagenesTestReducida.obtenerFila(i);
        int res = imagenesTrainReducida.caenene(cantVecinos, fila);
        if (res == digitoRepr2[i]){
            matConf[res][res]++;
            aciertos++;
            VP[res]++;
        } else {
            matConf[digitoRepr2[i]][res]++;
            FP[res]++;
            FN[digitoRepr2[i]]++;
        }
    }
    //Calculo de hit rate. En este caso es un vector de un elemento porque no es por digito
    vector<double> hitRate;
    hitRate.push_back((double )aciertos/(double )imagenesTest.Filas());

    //Calculo precision, recall y f1-score
    vector< vector<double> > metricas = calcularMetricas(VP, FP, FN);

    //Agregamos el hit rate
    metricas.push_back(hitRate);
    pair<vector< vector<double> >,vector< vector<double> > > res;
    res.first = metricas;
    res.second = matConf;

    return res;
}


 double usarKnn(Matriz imagenesTrain, Matriz imagenesTest, int cantVecinos){
     int aciertos = 0;
     for(int i = 0; i<imagenesTest.Filas(); i++){
         vector<double> fila = imagenesTest.obtenerFila(i);
         int res = imagenesTrain.caenene(cantVecinos, fila);
         if (res == imagenesTest.digitoRepresentado(i)){
             aciertos++;
            //cout << i << ": Funciona bien" << endl;
         } else {
             //cout << i << ": Funciona mal" << endl;
         }
     }
     double hitRate = (double )aciertos/(double )imagenesTest.Filas();
     return hitRate;
 }

 double usarKnnMejorado(Matriz imagenesTrain, Matriz imagenesTest, int cantVecinos){
     int aciertos = 0;
     for(int i = 0; i<imagenesTest.Filas(); i++){
         vector<double> fila = imagenesTest.obtenerFila(i);
         int res = imagenesTrain.caeneneMejorado(cantVecinos, fila);
         if (res == imagenesTest.digitoRepresentado(i)){
             aciertos++;
            //cout << i << ": Funciona bien" << endl;
         } else {
             //cout << i << ": Funciona mal" << endl;
         }
     }
     double hitRate = (double )aciertos/(double )imagenesTest.Filas();
     return hitRate;
 }


pair<vector< vector<double> >,vector< vector<double> > > usarKnn2(Matriz imagenesTrain, Matriz imagenesTest, int cantVecinos){
    //Hacemos el reconocimiento de digitos mediante kNN y comparamos los resultados con los valores reales
    int aciertos = 0;
    //Para calcular metricas precision, recall y f1-score 
    vector<int> VP(10, 0);
    vector<int> FP(10, 0);
    vector<int> FN(10, 0);
    vector<vector<double> > matConf = MatConf();

    for(int i = 0; i<imagenesTest.Filas(); i++){
        vector<double> fila = imagenesTest.obtenerFila(i);
        int res = imagenesTrain.caenene(cantVecinos, fila);
        if (res == imagenesTest.digitoRepresentado(i)){
            matConf[res][res]++;
            aciertos++;
            VP[res]++;
        } else {
           matConf[imagenesTest.digitoRepresentado(i)][res]++;
            FP[res]++;
            FN[imagenesTest.digitoRepresentado(i)]++;
        }
    }
    //Calculo de hit rate. En este caso es un vector de un elemento porque no es por digito
    vector<double> hitRate;
    hitRate.push_back((double )aciertos/(double )imagenesTest.Filas());

    //Calculo precision, recall y f1-score
    vector< vector<double> > metricas = calcularMetricas(VP, FP, FN);
    metricas.push_back(hitRate);
    pair<vector< vector<double> >,vector< vector<double> > > res;
    res.first = metricas;
    res.second = matConf;


    //Agregamos el hit rate
   

    return res;
}










vector<int> utilizarKnn(Matriz imagenesTrain, Matriz imagenesTest, int cantVecinos){

    //Hacemos el reconocimiento de digitos mediante kNN 
    vector<int> res;
    for(int i = 0; i<imagenesTest.Filas(); i++){
        cout << "Hacemos kNN para clasificar la imagen " << i+1 << " del test\n";
        vector<double> fila = imagenesTest.obtenerFila(i);
        int digito = imagenesTrain.caenene(cantVecinos, fila);
        cout << "Resultado: " << digito << "\n";
        res.push_back(digito);
    }

    return res; 
}


vector<int> utilizarKnnMejorado(Matriz imagenesTrain, Matriz imagenesTest, int cantVecinos){

    //Hacemos el reconocimiento de digitos mediante kNN 
    vector<int> res;
    for(int i = 0; i<imagenesTest.Filas(); i++){
        cout << "Hacemos kNN para clasificar la imagen " << i+1 << " del test\n";
        vector<double> fila = imagenesTest.obtenerFila(i);
        int digito = imagenesTrain.caeneneMejorado(cantVecinos, fila);
        cout << "Resultado: " << digito << "\n";
        res.push_back(digito);
    }

    return res; 
}


vector<int> utilizarPlsMejorado(Matriz imagenesTrain, Matriz imagenesTest, int cantIterPls, int cantIterMetPot, int cantVecinos){

    //Guardamos digitos que representa cada imagen del train y del test
    vector<int> digitoRepr = imagenesTrain.obtenerDigitos();
    vector<int> digitoRepr2 = imagenesTest.obtenerDigitos();

    //Calculamos preY 
    Matriz Y = preY(digitoRepr);

    //Le restamos la media y dividimos por sqrt(n-1) para obtener Y
    Y.restarMedia(Y);

    Matriz X = imagenesTrain;

    //Calculamos el cambio de base mediante pls-da
    vector< vector<double> > cambioBase = imagenesTrain.pls_da(X,Y,cantIterPls,cantIterMetPot);


    //Le restamos la media del train y dividimos por sqrt(n-1) a las imagenes del test
    imagenesTest.restarMedia(imagenesTrain); 
    imagenesTrain.restarMedia(imagenesTrain); 


    //Aplicamos el cambio de base al train y al test
    Matriz imagenesTrainReducida = imagenesTrain.cambioDeBase(cambioBase); // imagenesTrain con o sin media?

    

    //Aplicamos el cambio de base al test
    Matriz imagenesTestReducida = imagenesTest.cambioDeBase(cambioBase);

    //Le asignamos los digitos que antes guardamos a la matriz (pues con las otras funciones sino se pierden)
    imagenesTrainReducida.cambiarDigitos(digitoRepr);

    //Hacemos el reconocimiento de digitos mediante kNN 
    vector<int> res;
    for(int i = 0; i<imagenesTest.Filas(); i++){
        cout << "Hacemos kNN para clasificar la imagen " << i+1 << " del test\n";
        vector<double> fila = imagenesTestReducida.obtenerFila(i);
        int digito = imagenesTrainReducida.caeneneMejorado(cantVecinos, fila);
        res.push_back(digito);
    }

    return res;    
}





vector<int> utilizarPcaMejorado(Matriz imagenesTrain, Matriz imagenesTest, int cantAutov, int cantIterMetPot, int cantVecinos){
    vector<int> digitoRepr = imagenesTrain.obtenerDigitos();
    vector<int> digitoRepr2 = imagenesTest.obtenerDigitos();

    //Calculamos el cambio de base mediante pca
    vector< vector<double> > cambioBase = imagenesTrain.pca(cantAutov,cantIterMetPot);
    
    //Le restamos la media del train y dividimos por sqrt(n-1) a las imagenes del test
    imagenesTest.restarMedia(imagenesTrain);        
    imagenesTrain.restarMedia(imagenesTrain);       

    //Aplicamos el cambio de base al train
    Matriz imagenesTrainReducida = imagenesTrain.cambioDeBase(cambioBase); // imagenesTrain con o sin media?
    
    
    //Aplicamos el cambio de base al test
    Matriz imagenesTestReducida = imagenesTest.cambioDeBase(cambioBase);

    //Le asignamos a la matriz los digitos que antes guardamos (pues con las otras funciones sino se pierden)
    imagenesTrainReducida.cambiarDigitos(digitoRepr);

    //Hacemos el reconocimiento de digitos mediante kNN 
    vector<int> res;
    for(int i = 0; i<imagenesTest.Filas(); i++){
        cout << "Hacemos kNN para clasificar la imagen " << i+1 << " del test\n";
        vector<double> fila = imagenesTestReducida.obtenerFila(i);
        int digito = imagenesTrainReducida.caeneneMejorado(cantVecinos, fila);
        res.push_back(digito);
    }

    return res;    
}