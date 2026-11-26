#pragma once

#include <string>

#include "Dispositivo.h"

namespace calidad
{

    class SensorTemperatura final : public Dispositivo
    {
    public:
        explicit SensorTemperatura(const std::string &id);

        bool inspeccionar(const Pieza &pieza) const override;
        const std::string descripcion() const override;
    };

}