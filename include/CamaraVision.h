#pragma once

#include <string>

#include "Dispositivo.h"

namespace calidad
{

    class CamaraVision : public Dispositivo
    {
    public:
        explicit CamaraVision(const std::string &id);

        bool inspeccionar(const Pieza &pieza) override;
        const std::string descripcion() const override;
    };

} // namespace calidad