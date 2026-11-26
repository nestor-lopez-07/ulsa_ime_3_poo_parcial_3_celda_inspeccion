// Experimento 1: memoria y object slicing bajo herencia.
// Programa independiente: no usa las clases del proyecto.

#include <iostream>

// Parte 1: sin metodos virtuales
class Base1
{
public:
    int a;
    double b;
    void saludar() const { std::cout << " Base1::saludar\n"; }
};
class Derivada1 : public Base1
{
public:
    double c;
    int d;
};

// Parte 2: con metodo virtual en la base
class Base2
{
public:
    int a;
    double b;
    virtual ~Base2() = default;
    virtual void quienSoy() const { std::cout << " Soy Base2\n"; }
};
class Derivada2 : public Base2
{
public:
    double c;
    int d;
    void quienSoy() const override { std::cout << " Soy Derivada2\n"; }
};

// Parte 3: slicing (recibe Base2 POR VALOR)
void porValor(Base2 b)
{
    std::cout << "Dentro de porValor, llamo quienSoy():\n";
    b.quienSoy();
}
void porReferencia(const Base2 &b)
{
    std::cout << "Dentro de porReferencia, llamo quienSoy():\n";
    b.quienSoy();
}

int main()
{
    std::cout << "--- Sin virtual ---\n";
    std::cout << "sizeof(Base1) = " << sizeof(Base1) << '\n';
    std::cout << "sizeof(Derivada1) = " << sizeof(Derivada1) << '\n';

    std::cout << "--- Con virtual ---\n";
    std::cout << "sizeof(Base2) = " << sizeof(Base2) << '\n';
    std::cout << "sizeof(Derivada2) = " << sizeof(Derivada2) << '\n';

    std::cout << "--- Slicing ---\n";
    Derivada2 d;
    d.a = 1;
    d.b = 2.0;
    d.c = 3.0;
    d.d = 4;
    porValor(d);
    porReferencia(d);
    return 0;
}
