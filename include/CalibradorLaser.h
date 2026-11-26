#pragma once

#include <string>

#include "Calibrable.h"
#include "Dispositivo.h"

namespace calidad
{

    class CalibradorLaser : public Dispositivo, public Calibrable
    {
    private:
        double desfase_;

    public:
        explicit CalibradorLaser(const std::string &id);

        bool inspeccionar(const Pieza &pieza) override;
        const std::string descripcion() const override;
        bool calibrar() override;
    };

} // namespace calidad
