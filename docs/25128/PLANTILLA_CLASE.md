# Documentación de la clase: [SensorTemperatura]

> Copia este archivo como `docs/<matrícula>/<Clase>.md` (por ejemplo, `docs/0123456/Bascula.md`) y llena tu copia. No modifiques la plantilla.

**Documentación elaborada por:** [Diego Jiménez Mena ]
**Matrícula:** [25128]
**Integrante:** [4]

## 1. Propósito

**¿Qué representa tu clase y qué revisa o registra de cada pieza?**

`SensorTemperatura` representa un sensor que mide la temperatura de una pieza. De cada pieza revisa su temperatura y la acepta solo si está dentro del rango permitido (entre 20.0 y 35.0, ambos incluidos). No modifica la pieza ni guarda historial.

**¿Quién usa tu clase y para qué?**

La usa `CeldaInspeccion`, que la guarda junto con los demás dispositivos como un `Dispositivo*`. La celda llama a `inspeccionar()` con cada pieza y registra un rechazo en `ReporteTurno` si devuelve `false`.

## 2. Decisiones de diseño

**¿De qué clase o clases hereda tu clase y por qué?**

Hereda de `Dispositivo` porque un sensor de temperatura *es un* dispositivo de la celda. Así cumple el contrato común (`inspeccionar()` y `descripcion()`) y la celda puede tratarlo igual que a cualquier otro dispositivo. No hereda de `Calibrable` porque no tiene desfase ni se calibra.

**Atributos propios de tu clase y para qué sirve cada uno:**

No tiene atributos propios. El identificador (`id_`) vive en `Dispositivo` y se pasa en el constructor, que lo envía a la clase base con `Dispositivo(id)`. La regla de temperatura es fija, por lo que no hace falta guardar estado.

**Métodos que sobrescribes con `override` y cómo implementaste la regla de inspección:**

Sobrescribo `inspeccionar(const Pieza&) const` y `descripcion() const`. En `inspeccionar` devuelvo `pieza.temperatura() >= 20.0 && pieza.temperatura() <= 35.0`, es decir, acepta si la temperatura está dentro del rango. `descripcion()` devuelve `"Sensor temperatura"`.

**¿Qué métodos de tu clase son `const` y por qué?**

`inspeccionar` y `descripcion` son `const` porque solo consultan: no cambian la pieza ni el estado del sensor. Además, `inspeccionar` recibe `const Pieza&` para no copiar la pieza y garantizar que no se modifique. El constructor es `explicit` para evitar conversiones implícitas desde `std::string`.

**Lo particular de tu clase:**

`final` significa que ninguna otra clase puede heredar de `SensorTemperatura`. Tiene sentido aquí porque la clase ya es una implementación completa y concreta: su regla de inspección es fija (20.0 a 35.0), no tiene atributos que extender ni puntos de personalización. Marcarla `final` documenta esa intención, evita que alguien derive de ella y cambie la regla por accidente, y además permite al compilador optimizar las llamadas a sus métodos. Si en el futuro se necesitara otro tipo de sensor, lo correcto sería crear una clase nueva que herede de `Dispositivo`, no de esta.

## 3. Pruebas

**¿Cómo comprobaste que tu clase funciona? ¿Qué piezas del turno te sirvieron para verificarla?**

Agregué el sensor (T-01) a la celda, ejecuté el turno completo y revisé en la salida que cada pieza mostrara `T-01 (Sensor temperatura): ACEPTA` o `RECHAZA` según su temperatura. Comparé esos resultados con mi cálculo a mano: T-01 debe rechazar P-07 y P-11 (2 rechazos) y aceptar las otras 10 piezas. Verifiqué también que los límites 20.0 y 35.0 se acepten. Al final comprobé que el reporte mostrara "Rechazos T-01: 2".

## 4. Bitácora

**Dudas que tuviste y cómo las resolviste:**

[Escribe aquí tus dudas reales. Ejemplo: tenía dudas sobre si los límites del rango se incluían, y sobre para qué sirve `final`. Revisé el README y los apuntes de la clase para confirmarlo.]

**Errores que encontraste y cómo los corregiste:**

[Escribe aquí tus errores reales. Ejemplo: VS Code marcó el error `C/C++(1455)` de `override` porque `Dispositivo.h` aún no declaraba los métodos virtuales puros; se corrigió al completar el contrato de `Dispositivo`.]