#pragma once

#include <string>

#include "Calibrable.h"
#include "Dsipositivo.h"

namespace calidad {

class CalibradorLaser : public Dispositivo, public Calibrable{
    private:
    double desfase_;

    public:
    explicit CalibradorLaser(const std::string& id);

    bool inspeccionar(const Pieza& pieza) const override;
    std::string description() const override;
    bool calibrar() override;
};


}  // namespace calidad
