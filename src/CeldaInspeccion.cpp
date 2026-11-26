#include "CeldaInspeccion.h"

#include <iostream>

#include "Calibrable.h"

namespace calidad
{

    void CeldaInspeccion::iniciarTurno()
    {
        std::cout << "=== Inicio de turno ===\n";
        for (Dispositivo *d : dispositivos_)
        {
            // ¿Este dispositivo también es Calibrable? (cross-cast con herencia múltiple)
            if (Calibrable *c = dynamic_cast<Calibrable *>(d))
            {
                std::cout << "Calibrando " << d->id() << " (" << d->descripcion() << ") ... "
                          << (c->calibrar() ? "OK" : "FALLA") << '\n';
            }
        }
    }

    void CeldaInspeccion::agregarDispositivo(Dispositivo *d)
    {
        if (d != nullptr)
        {
            dispositivos_.push_back(d);
        }
    }

    bool CeldaInspeccion::procesar(const Pieza &pieza)
    {
        std::cout << '\n'
                  << pieza << '\n';

        bool aceptada = true;
        for (Dispositivo *d : dispositivos_)
        {
            bool ok = d->inspeccionar(pieza);
            std::cout << "  " << d->id() << " (" << d->descripcion() << "): "
                      << (ok ? "ACEPTA" : "RECHAZA") << '\n';

            if (!ok)
            {
                aceptada = false;
                reporte_.registrarRechazo(d->id());
            }
        }

        std::cout << "  -> " << (aceptada ? "ACEPTADA" : "RECHAZADA") << '\n';
        reporte_.registrarPieza(aceptada);

        return aceptada;
    }

    const ReporteTurno &CeldaInspeccion::reporte() const
    {
        return reporte_;
    }

    // TODO (equipo): implementen agregarDispositivo(), procesar() y reporte().

} // namespace calidad
