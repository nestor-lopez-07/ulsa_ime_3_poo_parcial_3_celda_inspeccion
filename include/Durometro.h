#pragma once

#include <string>

#include "Dispositivo.h"

namespace calidad {

class Durometro : public Dispositivo {
public:
    explicit Durometro(const std::string& id);

    bool inspeccionar(const Pieza& pieza) const override;
    std::string descripcion() const override;
};

}  // namespace calidad