#include "Durometro.h"

namespace calidad {

Durometro::Durometro(const std::string& id) : Dispositivo(id) {}

bool Durometro::inspeccionar(const Pieza& pieza) const {
    return pieza.dureza() >= 45.0 && pieza.dureza() <= 60.0;
}

std::string Durometro::descripcion() const { return "Durometro"; }

}  // namespace calidad