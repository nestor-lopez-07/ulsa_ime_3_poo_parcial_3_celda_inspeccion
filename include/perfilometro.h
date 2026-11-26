#pragma once

#include <string>

#include "Calibrable.h"
#include "Dispositivo.h"

namespace calidad
{

    class perfilometro : public Dispositivo, public Calibrable
    {
    private:
        double desfase_;

    public:
        explicit perfilometro(const std::string &id);

        bool inspeccionar(const Pieza &pieza) const override;
        std::string descripcion() const override;
        bool calibrar() override;
    };

} // namespace calidad
