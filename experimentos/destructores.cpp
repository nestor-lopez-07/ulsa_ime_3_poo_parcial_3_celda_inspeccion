// Experimento 2: destructor virtual vs. no virtual al destruir por puntero base.
// Programa independiente: no usa las clases del proyecto.
// Sin virtual: g++ -Wall -Wextra -std=c++17 experimentos/destructores.cpp -o destructores
// Con virtual: g++ -Wall -Wextra -std=c++17 -DCON_VIRTUAL experimentos/destructores.cpp -o destructores_virtual
#include <iostream>

class Base {
public:
    Base() { std::cout << "Constructor Base\n"; }
#ifdef CON_VIRTUAL
    virtual ~Base() { std::cout << "Destructor Base\n"; }
#else
    ~Base() { std::cout << "Destructor Base\n"; }
#endif
    virtual void hablar() const { std::cout << "Hola desde Base\n"; }  // la hace polimorfica
};

class Derivada : public Base {
private:
    int* recurso_;
public:
    Derivada() : recurso_(new int[100]) { std::cout << "Constructor Derivada (reserva memoria)\n"; }
#ifdef CON_VIRTUAL
    ~Derivada() override {
#else
    ~Derivada() {
#endif
        delete[] recurso_;
        std::cout << "Destructor Derivada (libera memoria)\n";
    }
    void hablar() const override { std::cout << "Hola desde Derivada\n"; }
};

int main() {
    Base* p = new Derivada();
    p->hablar();
    delete p;  // destruccion a traves de Base*
    return 0;
}
