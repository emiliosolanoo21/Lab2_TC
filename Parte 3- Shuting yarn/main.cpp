#include <iostream>
#include <fstream>
#include <stack>
#include <map>
#include <string>
#include <regex>

using namespace std;

// Función para determinar si un token es un operador
bool isOperator(const char& token) {

    static const string operators = "|?.+*^";
    return operators.find(token) != string::npos;
}

bool isBinary(const char& token) {
    static const string operators = "^|";
    return operators.find(token) != string::npos;
}

// Función para asignar prioridades a los operadores
// Función para asignar prioridades a los operadores
int precedence(const char& op) {
    static const map<char, int> prec = {
        {'(', 1}, {')', 1}, {'|', 2}, {'.', 3}, {'?', 4}, {'*', 4}, {'+', 4}, {'^', 5}, {'∗', 4}
    };
    auto it = prec.find(op);
    if (it != prec.end()) {
        return it->second;
    }
    // Si el operador no se encuentra en el mapa, devolvemos una prioridad por defecto
    return -1;
}
// Formatear la expresión regular para incluir concatenaciones explícitas
string formatRegEx(const string linea) {
    string resultado;
    bool escaped = false;
    for (size_t i = 0; i < linea.length(); ++i) {
        char c1 = linea[i];
        if (i + 1 < linea.length()) {
            char c2 = linea[i + 1];
            resultado += c1;

            // Verificar si el caracter actual es '\' (carácter de escape)
            if (c1 == '\\' && !escaped) {
                resultado += c2; // Agregar el siguiente caracter sin formato
                ++i; // Avanzar al siguiente caracter
                escaped =true;
                continue;
            }

            if ((c1 != '(' && c2 != ')' && !isOperator(c2) && !isBinary(c1)) || escaped) {
                resultado += '.';
                escaped=false;
            }
        }
    }
    resultado += linea[linea.length() - 1];
    return resultado;
}

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

string infixToPostfix(string regex) {
    string postfix;
    stack<char> pilaPostfix;
    bool escapeChar = false;
    cout<<"Se convierte reformatea:"<<endl;
    string formattedRegEx = formatRegEx(regex);
    cout<<"Expresion infix: "<<formattedRegEx<<endl;

    for (char caracter : formattedRegEx) {
        cout<<"caracter Evaluado: "<<caracter<<endl;
        switch (caracter) {
            case '\\':
                escapeChar =true;
                break;
            case '(':
                if(!escapeChar){
                    pilaPostfix.push(caracter);
                    break;
                }
            case ')':
                if(!escapeChar){
                    while (pilaPostfix.top() != '(') {
                        postfix += pilaPostfix.top();
                        pilaPostfix.pop();
                    }
                    pilaPostfix.pop(); // Eliminar el paréntesis izquierdo '(' de la pila
                    break;
                }

            default:
                if((!isOperator(caracter) && !isBinary(caracter)) || escapeChar){
                    escapeChar = false;
                    postfix+=caracter;
                }else {
                    while (!pilaPostfix.empty()) {
                        char caracterTomado = pilaPostfix.top();

                        int precedenciaCaracterTomado = precedence(caracterTomado);
                        int precedenciaCaracterActual = precedence(caracter);
                        cout<<"Caracter Tomado: "<<caracterTomado<<" Caracter Actual: "<<caracter<<endl;
                        if (precedenciaCaracterTomado >= precedenciaCaracterActual) {
                            postfix += pilaPostfix.top();
                            pilaPostfix.pop();
                        } else {
                            break;
                        }
                    }
                    pilaPostfix.push(caracter);
                }


                break;
        }
        cout<<"Cadena Postfix: "<<postfix<<endl;
        mostrarPila(pilaPostfix);
    }

    while (!pilaPostfix.empty()) {
        postfix += pilaPostfix.top();
        pilaPostfix.pop();
    }

    return postfix;
}


string replaceUnicodeCharacters(const string& input) {
    // Caracteres Unicode a reemplazar
    map<string, string> unicodeMap = {
        {"𝑎", "a"},
        {"𝑏", "b"},
        {"𝑐", "c"},
        {"𝑑", "d"},
        {"𝑒", "e"},
        {"𝑓", "f"},
        {"𝑔", "g"},
        {"𝑎𝑧", "az"},
        {"𝐴𝑍", "AZ"},
        {"∗", "*"}, // Reemplazar el carácter unicode '∗' con '*'
    };

    string output = input;
    for (const auto& entry : unicodeMap) {
        regex pattern(entry.first);
        output = regex_replace(output, pattern, entry.second);
    }

    return output;
}

int main() {
    ifstream archivo("../datos.txt");
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo." << endl;
        return 1;
    }

    string linea;
    while (getline(archivo, linea)) {
        linea = replaceUnicodeCharacters(linea);
        cout << "Expresión Regular en Infix: " << linea << endl;
        string postfix = infixToPostfix(linea);
        cout << "Expresión Regular en Postfix: " << postfix << endl;
        cout << "-------------------------" << endl;
    }

    archivo.close();
    return 0;
}
