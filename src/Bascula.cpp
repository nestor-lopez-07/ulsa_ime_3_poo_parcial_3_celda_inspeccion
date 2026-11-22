#include "Bascula.h"
namespace calidad {

    Bascula::Bascula(const std::string& id) : Dispositivo(id), desfase_(0.4) {}

bool Bascula::inspeccionar(const Pieza& pieza) const {
    double medido = pieza.peso() + desfase_;
    return medido >= 10.0 && medido <= 15.0;
}
std::string Bascula::descripcion() const { return "Bascula"; }

bool Bascula::calibrar() {
    desfase_ = 0.0;
    return true;
}

} 