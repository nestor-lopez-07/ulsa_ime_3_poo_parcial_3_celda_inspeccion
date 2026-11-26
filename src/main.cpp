// main.cpp: punto de entrada del programa. Lo completa el equipo.
// Revisen la sección "main.cpp" de la Fase 3 en PROYECTO.md.
#include <iostream>

#include "Bascula.h"
#include "CalibradorLaser.h"
#include "CamaraVision.h"
#include "CeldaInspeccion.h"
#include "DatosTurno.h"
#include "ReporteTurno.h"
#include "SensorTemperatura.h"
#include "Durometro.h"


int main() {
    calidad::Bascula bascula("B-01");
    calidad::CalibradorLaser laser("L-01");
    calidad::CamaraVision camara("V-01");
    calidad::SensorTemperatura sensor("T-01");
    calidad::Durometro durometro("D-01");

    calidad::CeldaInspeccion celda;
    celda.agregarDispositivo(&bascula);
    celda.agregarDispositivo(&laser);
    celda.agregarDispositivo(&camara);
    celda.agregarDispositivo(&sensor);
    celda.agregarDispositivo(&durometro);

    celda.iniciarTurno();

    for (const calidad::Pieza& pieza : calidad::piezasDelTurno()) {
        celda.procesar(pieza);
    }

    std::cout << '\n' << celda.reporte();

    calidad::ReporteTurno esperado(12, 4,
        {{"B-01", 2}, {"D-01", 2}, {"L-01", 2}, {"T-01", 2}, {"V-01", 2}});
    std::cout << (celda.reporte() == esperado ? "Reporte correcto"
                                              : "Reporte con diferencias") << '\n';
    return 0;
}
