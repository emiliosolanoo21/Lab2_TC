#include <fstream>
#include <iostream>
#include <stack>

using namespace std;

// Función para mostrar los elementos de la pila sin vaciarla
void mostrarPila(const stack<char>& pila) {
    // Creamos una pila auxiliar para almacenar temporalmente los elementos
    stack<char> pilaAux = pila;
    cout<< "Datos en la pila: [";
    // Mostramos los elementos de la pila auxiliar
    while (!pilaAux.empty()) {


        cout << pilaAux.top();
        pilaAux.pop();
    }

    cout<<"]"<< endl;
}

char contraParte(const char caracter){
    switch (caracter) {
        case '(':
            return ')';
            break;
        case '[':
            return ']';
            break;
        case '{':
            return '}';
        default:
            return ' ';
    }
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
