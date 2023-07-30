#include <fstream>
#include <iostream>
#include <stack>
#include <map>
#include <string>

using namespace std;

// Función para determinar si un token es un operador
bool isOperator(const char& token) {
    static const string operators = "|?+*^";
    return operators.find(token) != string::npos;
}

bool isBinary(const char& token) {
    static const string operators = "^|";
    return operators.find(token) != string::npos;
}

// Función para asignar prioridades a los operadores
int precedence(const char& op) {
    static const map<char, int> prec = {
        {'(', 1}, {'|', 2}, {'.', 3}, {'?', 4}, {'*', 4}, {'+', 4}, {'^', 5}
    };
    return prec.at(op);
}


string formatRegEx(const string linea){

    string resultado;

    for (size_t i = 0; i < linea.length(); ++i) {
        char c1 = linea[i];

        if(i + 1 < linea.length()){
            char c2 = linea[i+1];

            resultado+=c1;

            if(
                c1 != '(' && c2 != ')' && !isOperator(c2) && !isBinary(c1)
            ){

                resultado+='.';
            }
        }
    }

    resultado+=linea[linea.length()-1];

    return resultado;
}

string infixToPostfix(string regex){
    string postfix;

    stack<char> pilaPostfix;

    string formattedRegEx = formatRegEx(regex);

    for (char caracter: formattedRegEx){
        switch (caracter) {
            case '(':
                pilaPostfix.push(caracter);
                break;
            case ')':
                while (pilaPostfix.top() != '(') {
                    postfix+=pilaPostfix.top();
                    pilaPostfix.pop();
                }
                pilaPostfix.pop();
                break;
            default:
                while (pilaPostfix.size()>0) {
                    char caracterTomado = pilaPostfix.top();
                    int precedenciaCaracterTomado = precedence(caracterTomado);
                    int precedenciaCaracterActual = precedence(caracter);


                    if(precedenciaCaracterTomado >= precedenciaCaracterActual){
                        postfix += pilaPostfix.top();
                        pilaPostfix.pop();
                    } else{
                        break;
                    }
                }

                pilaPostfix.push(caracter);
                break;
        }

    }

    while (!pilaPostfix.empty()) {
        postfix+= pilaPostfix.top();
        pilaPostfix.pop();
    }

    return postfix;
}



int main() {
    ifstream archivo("../datos.txt");
    stack<char> pila_regex;
    bool test= true;






    if (archivo.is_open()) {
        string linea;
        while (std::getline(archivo, linea)) {
            cout<<">>Linea a evaluar: "<<linea<<endl;
            for (char caracter : linea) {
                cout<<caracter<<endl;
                if(caracter=='('|| caracter == '[' || caracter =='{'){
                    cout<< "Se mete a la pila"<<endl;
                    pila_regex.push(caracter);
                }else if (caracter==')'|| caracter == ']' || caracter =='}') {
                    cout<< "Se evalua el ultimo caracter de la pila"<<endl;

                    if(!pila_regex.empty()){
                        if(contraParte(pila_regex.top())==caracter){
                            cout<<endl;
                            cout<<"o ¡Perfecto!, se hace pop de la pila o"<<endl;
                            cout<<endl;
                            pila_regex.pop();
                        }else {
                            cout<< "El caracter no coincide :("<< endl;
                            test = false;
                            break;
                        }
                    }else {
                        cout<<"La pila ya estaba vacia :("<< endl;
                        test =false;
                        break;
                    }
                }

                mostrarPila(pila_regex);

            }
            if(!pila_regex.empty()){
                 cout<<endl;
                 cout<<"*****Lastima, la expresion no esta balanceada. Ya que la pila no esta vacia.****"<< endl;
                 while (!pila_regex.empty()) {
                     pila_regex.pop();
                 }
                 cout<<endl;
            } else if(!test){
                cout<<endl;
                 cout<<"*****Lastima, la expresion no esta balanceada.:(****"<< endl;
                 while (!pila_regex.empty()) {
                     pila_regex.pop();
                 }
                 cout<<endl;
            }else {
                cout<<endl;
                cout<<"////La linea esta correctamente balanceada///"<<endl;
                cout<<endl;
            }
            test = true;

        }
        archivo.close();
    } else {
        cout << "Error al abrir el archivo." << endl;
    }

    return 0;
}
