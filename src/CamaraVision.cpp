#include "CamaraVision.h"

namespace calidad
{

    CamaraVision::CamaraVision(const std::string &id) : Dispositivo(id) {}

    bool CamaraVision::inspeccionar(const Pieza &pieza) const
    {
        return pieza.defectos() == 0;
    }

    std::string CamaraVision::descripcion() const { return "Camara de vision"; }

} // namespace calidad