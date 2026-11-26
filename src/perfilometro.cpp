#include "perfilometro.h"

namespace calidad
{

    perfilometro::perfilometro(const std::string &id)
        : Dispositivo(id), desfase_(+0.25) {}

    bool perfilometro::inspeccionar(const Pieza &pieza) const
    {
        double medido = pieza.largo() + desfase_;
        return medido >= 49.7 && medido <= 50.3;
        return pieza.defectos() <= 1;
    }

    std::string perfilometro::descripcion() const { return "Perfilometro"; }

    bool perfilometro::calibrar()
    {
        desfase_ = 0.0;
        return true;
    }

} // namespace calidad
