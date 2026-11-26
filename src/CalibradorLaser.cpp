#include "CalibradorLaser.h"

namespace calidad
{

    CalibradorLaser::CalibradorLaser(const std::string &id)
        : Dispositivo(id), desfase_(-0.3) {}

    bool CalibradorLaser::inspeccionar(const Pieza &pieza) const
    {
        double medido = pieza.largo() + desfase_;
        return medido >= 49.5 && medido <= 50.5;
    }

    std::string CalibradorLaser::descripcion() const { return "Calibrador laser"; }

    bool CalibradorLaser::calibrar()
    {
        desfase_ = 0.0;
        return true;
    }

} // namespace calidad