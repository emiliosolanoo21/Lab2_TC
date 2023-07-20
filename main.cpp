#include <fstream>
#include <iostream>
#include <stack>

using namespace std;

int main() {
    std::ifstream archivo("../datos.txt");

    if (archivo.is_open()) {
        std::string linea;
        while (std::getline(archivo, linea)) {
            std::cout << linea << std::endl;
        }
        archivo.close();
    } else {
        std::cout << "Error al abrir el archivo." << std::endl;
    }
    std::stack<int> miPila;

    miPila.push(10);
    miPila.push(20);
    miPila.push(30);

    std::cout << "Tamaño de la pila: " << miPila.size() << std::endl;

    while (!miPila.empty()) {
        int elemento = miPila.top();
        std::cout << "Elemento en el tope: " << elemento << std::endl;
        miPila.pop();
    }

    return 0;
}
