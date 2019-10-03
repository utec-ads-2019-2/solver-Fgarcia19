#include <iostream>
#include <stack>
#include <map>
#include <stdlib.h>
#include <vector>
#include <math.h>
#include <algorithm>
using namespace std;

map<char,int> prioridad;

vector<string> postfijo(string ecuacion){
    stack<char> s;
    vector<string> prueba;
    string numero;
    for(auto i:ecuacion){
        if(isdigit(i)|| (i >= 'a' && i <= 'z' ) || (i >= 'A' && i <= 'Z' )){

            if(isdigit(i)){
                numero+=i;
            }
            else{
                prueba.push_back(string (1,i));
            }
        }
        else{
            if(!numero.empty()){
                prueba.push_back(numero);
                numero.clear();
            }
            if(i=='('){
                s.push(i);
            }
            else {
                if (i == ')') {
                    while (s.top() != '(') {
                        prueba.push_back(string(1, s.top()));
                        s.pop();
                    }
                    s.pop();


                } else {
                    if (!s.empty()) {
                        if (prioridad[s.top()] == prioridad[i]) {
                            prueba.push_back(string(1, s.top()));
                            s.pop();
                            s.push(i);
                        } else if (prioridad[s.top()] < prioridad[i]) {
                            s.push(i);
                        } else if (prioridad[s.top()] > prioridad[i]) {
                            while (!s.empty() && s.top() != '(') {
                                prueba.push_back(string(1, s.top()));
                                s.pop();
                            }
                            s.push(i);
                        }
                    }
                    else{
                        s.push(i);
                    }
                }
            }
        }
    }
    if(!numero.empty()){
        prueba.push_back(numero);
        numero.clear();
    }
    while(!s.empty()){
        if(s.top()!='('&&s.top()!=')') {
            prueba.push_back(string (1,s.top()));
        }
        s.pop();
    }
    return prueba;

}


float operar(vector<string> ecuacion){
    vector<string>variables;
    map<string,int> valores;
    stack<float> s;
    float aux;
    for(auto i:ecuacion) {
        if(i=="+"){
            aux=s.top();
            s.pop();
            s.top()+=aux;
        }
        else if(i=="-"){
            aux=s.top();
            s.pop();
            s.top()-=aux;
        }
        else if(i=="*"){
            aux=s.top();
            s.pop();
            s.top()*=aux;
        }
        else if(i=="/"){
            aux=s.top();
            s.pop();
            s.top()/=aux;
        }
        else if(i=="^"){
            aux=s.top();
            s.pop();
            s.top()=pow(s.top(),aux);
        }
        else if((i >= "a" && i <= "z" ) || (i >= "A" && i <= "Z" )){
            if ( std::find(variables.begin(), variables.end(), i) == variables.end() )
            {
                int valor;
                cout<<"Inserte el valor de "<<i<<endl;
                cin>>valor;
                valores[i]=valor;
                variables.push_back(i);
            }
            s.push(valores[i]);

        }
        else{
            s.push(stof(i));
        }
    }
    return s.top();
}



int main() {
    prioridad.insert(pair<char,int>('+',1));
    prioridad.insert(pair<char,int>('-',1));
    prioridad.insert(pair<char,int>('*',2));
    prioridad.insert(pair<char,int>('/',2));
    prioridad.insert(pair<char,int>('^',3));
    prioridad.insert(pair<char,int>('(',0));
    string ecuacion;
    cin>>ecuacion;
    cout<<operar(postfijo(ecuacion));
    return 0;
}