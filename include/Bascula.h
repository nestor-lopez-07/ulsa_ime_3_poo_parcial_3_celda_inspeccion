#pragma once

#include <string>

#include "Calibrable.h"
#include "Dispositivo.h"

namespace calidad
{

    class Bascula : public Dispositivo, public Calibrable
    {

    private:
        double desfase_;

    public:
        explicit Bascula(const std::string &id);

        bool inspeccionar(const Pieza &pieza) const override;
        const std::string descripcion() const override;
        bool calibrar() override;
    };

} // namespace calidad
