# Celda Robótica de Inspección de Calidad

Proyecto del Parcial 3 de Programación Orientada a Objetos.

## 1. Equipo

| Integrante | Matrícula | Nombre | Usuario de GitHub | Clase |
| --- | --- | --- | --- | --- |
| 1 | 25218 | Néstor Hiram López Valdovinos | nestor-lopez-07 | Bascula |
| 2 | Pendiente | Brayan Alberto | Pendiente | CalibradorLaser |
| 3 | Pendiente | Daniel | Pendiente | CamaraVision |
| 4 | 25128 | Diego | Pendiente | SensorTemperatura |
| 5 | Pendiente | Arturo | Pendiente | ReporteTurno |
| 6 | Pendiente | Jorge | Jorge-Sadurni | Durometro |

## 2. Cómo compilar y ejecutar

Desde la raíz del repositorio:

```powershell
g++ -Wall -Wextra -std=c++17 -Iinclude src/*.cpp -o celda.exe
.\celda.exe
```

Los dos experimentos se compilan y ejecutan por separado:

```powershell
g++ -Wall -Wextra -std=c++17 experimentos/memoria.cpp -o memoria.exe
.\memoria.exe

g++ -Wall -Wextra -std=c++17 experimentos/destructores.cpp -o destructores.exe
.\destructores.exe
```

## 3. Contrato de `Dispositivo` y `Calibrable`

**Errores esperados al compilar el repositorio base:**

El repositorio incompleto no puede proporcionar una implementación válida de `Dispositivo` o `Calibrable`. Los errores principales esperan que el equipo declare el contrato común y que las clases derivadas hereden e implementen esos métodos. También puede haber errores por métodos abstractos que no se implementaron o por falta de definiciones para `dynamic_cast`, según el estado de las clases.

**Contrato acordado para `Dispositivo`:**

```cpp
class Dispositivo {
public:
    explicit Dispositivo(const std::string& id);

    const std::string& id() const;
    virtual bool inspeccionar(const Pieza& pieza) = 0;
    virtual const std::string& descripcion() const = 0;
    virtual ~Dispositivo() = default;
};
```

- `inspeccionar(const Pieza&)` es `virtual` puro porque cada dispositivo aplica una regla distinta sobre la misma pieza. Devuelve `bool`: `true` significa que acepta y `false` que rechaza.
- `descripcion() const` es `virtual` puro porque la descripción textual pertenece a cada tipo concreto. Es `const` porque solo consulta el nombre y no modifica el objeto.
- `id() const` se conserva como consulta constante. Se recibe por referencia constante para evitar copiar cadenas innecesariamente.
- La parámetro de `inspeccionar()` se recibe como `const Pieza&` porque el dispositivo solo lee los datos de la pieza y no debe modificarlos.
- El destructor es `virtual` para que `delete` o la destrucción de un dispositivo concreto usando un `Dispositivo*` invoque primero al destructor derivado y después al destructor base.
- No se puede crear directamente un `Dispositivo` genérico porque contiene métodos virtuales puros; cada clase concreta debe implementarlos.

**Contrato acordado para `Calibrable`:**

```cpp
class Calibrable {
public:
    virtual bool calibrar() = 0;
    virtual ~Calibrable() = default;
};
```

`calibrar()` es virtual porque la acción concreta puede ser distinta según el dispositivo. Devuelve `bool` para permitir que `iniciarTurno()` imprima `OK` o `FALLA`. `Calibrable` es una interfaz de capacidad y no tiene atributos: solo declara una operación que comparten ciertos dispositivos. Incluye destructor virtual para que pueda usarse de forma polimórfica por puntero. `Bascula` y `CalibradorLaser` heredarán de `Dispositivo` y de `Calibrable`.

## 4. Cálculo a mano del reporte

Turno de 12 piezas, con los desfases ya corregidos por la calibración. `Bascula` mide `peso + desfase` y el desfase queda en `0.0`; `CalibradorLaser` mide `largo + desfase` y el desfase queda en `0.0`.

| Pieza | B-01 | L-01 | V-01 | T-01 | D-01 | Resultado |
| --- | --- | --- | --- | --- | --- | --- |
| P-01 | ACEPTA | ACEPTA | ACEPTA | ACEPTA | ACEPTA | ACEPTADA |
| P-02 | ACEPTA | ACEPTA | ACEPTA | ACEPTA | ACEPTA | ACEPTADA |
| P-03 | RECHAZA | ACEPTA | ACEPTA | ACEPTA | ACEPTA | RECHAZADA |
| P-04 | ACEPTA | ACEPTA | ACEPTA | ACEPTA | ACEPTA | ACEPTADA |
| P-05 | ACEPTA | RECHAZA | ACEPTA | ACEPTA | ACEPTA | RECHAZADA |
| P-06 | ACEPTA | ACEPTA | RECHAZA | ACEPTA | ACEPTA | RECHAZADA |
| P-07 | ACEPTA | ACEPTA | ACEPTA | RECHAZA | ACEPTA | RECHAZADA |
| P-08 | RECHAZA | RECHAZA | RECHAZA | ACEPTA | ACEPTA | RECHAZADA |
| P-09 | ACEPTA | ACEPTA | ACEPTA | ACEPTA | RECHAZA | RECHAZADA |
| P-10 | ACEPTA | ACEPTA | ACEPTA | ACEPTA | RECHAZA | RECHAZADA |
| P-11 | ACEPTA | ACEPTA | ACEPTA | RECHAZA | ACEPTA | RECHAZADA |
| P-12 | ACEPTA | ACEPTA | ACEPTA | ACEPTA | ACEPTA | ACEPTADA |

**Reporte esperado del equipo de 6:**

| Concepto | Cantidad |
| --- | ---: |
| Inspeccionadas | 12 |
| Aceptadas | 4 |
| Rechazadas | 8 |
| Rechazos B-01 | 2 |
| Rechazos D-01 | 2 |
| Rechazos L-01 | 2 |
| Rechazos T-01 | 2 |
| Rechazos V-01 | 2 |

El resultado coincide con las reglas del proyecto: P-01, P-02, P-04 y P-12 son aceptadas; las otras ocho piezas tienen al menos un rechazo. P-08 suma rechazos a B-01, L-01 y V-01.

**Contraste con el programa:**

La ejecución aún no pudo verificarse porque el repositorio conserva las clases y la celda incompletas. Cuando el programa esté implementado, se debe registrar aquí si coincidió al primer intento. Si aparece una diferencia, se documentará la pieza afectada, la causa y la corrección aplicada.

## 5. Diagrama de clases

El diagrama completo debe guardarse en la raíz como `diseno_solucion.png`. Debe incluir `Dispositivo` como clase abstracta, `Calibrable` como interfaz, herencia múltiple en `Bascula` y `CalibradorLaser`, composición entre `CeldaInspeccion` y `ReporteTurno`, agregación hacia `Dispositivo`, dependencia hacia `Pieza`, virtuales puros, destructor virtual, `override` y `SensorTemperatura` como `final`.

![Diagrama de clases](diseño_solucion.png)

## 6. Documentación individual

| Integrante | Documentación de su clase | Rama del reto opcional |
| --- | --- | --- |
| Néstor Hiram López Valdovinos | `docs/25218/Bascula.md` | No |
| Brayan Alberto | `docs/<matrícula>/CalibradorLaser.md` | Pendiente |
| Daniel | `docs/<matrícula>/CamaraVision.md` | Pendiente |
| Diego | `docs/<matrícula>/SensorTemperatura.md` | Pendiente |
| Arturo | `docs/<matrícula>/ReporteTurno.md` | Pendiente |
| Jorge | `docs/<matrícula>/Durometro.md` | Pendiente |

Los resultados de los experimentos deben estar documentados en [docs/experimentos.md](docs/experimentos.md).

## 7. Prueba de extensibilidad

La prueba consistirá en crear una clase nueva que herede de `Dispositivo`, implementar `inspeccionar()` y `descripcion()`, crearla en `main` y agregarla con `celda.agregarDispositivo()`. No debe ser necesario modificar `CeldaInspeccion` ni `procesar()`: la celda solo trabaja con el contrato `Dispositivo` y ejecuta cada método por binding dinámico.

**Resultado esperado:**

- Archivos nuevos: un encabezado `include/*.h` y una implementación `src/*.cpp`.
- Archivo modificado: `main.cpp`, únicamente para crear y agregar el dispositivo.
- `CeldaInspeccion`: no debe modificarse.
- El reporte esperado puede cambiar durante la prueba, pero debe restaurarse antes de la entrega.

## 8. Reflexión del equipo

**¿Qué aprendimos en este proyecto?**

Aprenderemos a separar un contrato común de sus implementaciones concretas. El uso de herencia, métodos virtuales puros, `override`, herencia múltiple e interfaces permite que la celda inspeccione piezas sin conocer las clases concretas. También reforzaremos las relaciones de agregación y composición, el uso de referencias constantes y la importancia de verificar límites y desfases de calibración.

**¿Qué cambiaríamos de nuestro proceso de trabajo como equipo?**

Haríamos primero los contratos de `Dispositivo` y `Calibrable`, revisaríamos el diagrama antes de implementar y confirmaríamos el cálculo a mano antes de probar. Después, cada integrante trabajaría en su clase desde una rama o en archivos propios, haciendo `git pull` antes de comenzar y commits pequeños. Las modificaciones compartidas a `CeldaInspeccion` y `main` se harían avisando al equipo y verificando la compilación después de cada integración.
