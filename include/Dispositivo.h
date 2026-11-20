#pragma once

#include <string>

#include "Pieza.h"

namespace calidad
{

    class Dispositivo
    {
    private:
        std::string id_;

    public:
        explicit Dispositivo(const std::string &id) : id_(id) {}

        const std::string &id() const { return id_; }

        // TODO (equipo): definan el contrato que todo dispositivo debe cumplir.
        //  - La celda necesita pedirle a CUALQUIER dispositivo que inspeccione una pieza
        //    y que diga qué tipo de dispositivo es.
        //  - No debe poder crearse un "Dispositivo" genérico.
        //  - Debe ser seguro destruir un dispositivo concreto a través de un Dispositivo*.
        //
        // Preguntas para el diseño:
        //  ¿Qué métodos declaran aquí y cuáles deben ser virtuales puros?
        //  ¿Cuáles deben ser const y por qué?
        //  ¿Qué pasa con el destructor?
        virtual ~Dispositivo() = default;
        virtual bool inspeccionar(const Pieza &) = 0;
        virtual const std::string &descripcion() const = 0;
    };

} // namespace calidad
