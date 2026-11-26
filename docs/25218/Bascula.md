# Documentación de la clase: Bascula

**Documentación elaborada por:** Néstor Hiram López Valdovinos
**Matrícula:** 25218
**Integrante:** 1

## 1. Propósito

**¿Qué representa tu clase y qué revisa o registra de cada pieza?**

La clase `Bascula` representa el dispositivo encargado de medir el peso de una pieza. Revisa si el peso medido se encuentra dentro del intervalo aceptable de 10.0 a 15.0 kg, ambos límites incluidos.

**¿Quién usa tu clase y para qué?**

La usa `CeldaInspeccion` a través del contrato `Dispositivo`. Al procesar una pieza, la celda llama a `inspeccionar()` sin conocer que el objeto concreto es una báscula.

## 2. Decisiones de diseño

**¿De qué clase o clases hereda tu clase y por qué?**

`Bascula` hereda de `Dispositivo`, porque es un tipo de dispositivo que puede inspeccionar piezas, y de `Calibrable`, porque puede corregir su desfase de fábrica.

**Atributos propios de tu clase y para qué sirve cada uno:**

La báscula tiene el atributo privado `desfase_`, de tipo `double`. Contiene el error sumado a la medición del peso. Inicialmente vale `0.4` kg y pasa a `0.0` después de la calibración.

**Métodos que sobrescribes con `override` y cómo implementaste la regla de inspección:**

Sobrescribo `inspeccionar(const Pieza&) const`, que calcula `pieza.peso() + desfase_` y devuelve verdadero si el peso medido está entre 10.0 y 15.0 kg. También sobrescribo `descripcion() const`, que devuelve `"Bascula"`.

La clase implementa `calibrar()` de `Calibrable`. Este método asigna `0.0` a `desfase_` y devuelve `true` para indicar que la calibración fue exitosa.

**¿Qué métodos de tu clase son `const` y por qué?**

`inspeccionar()` y `descripcion()` son `const` porque solo consultan datos y no modifican la báscula ni la pieza recibida. `Pieza` se recibe como referencia constante para evitar una copia y proteger sus atributos.

**Lo particular de tu clase:**

El desfase se modeló como un valor propio de la báscula. Antes de calibrar se suma `0.4` kg al peso real; después de ejecutar `calibrar()` se suma `0.0`, por lo que la medición coincide con el peso real. Esto permite que `CeldaInspeccion::iniciarTurno()` detecte que la báscula es calibrable mediante `dynamic_cast<Calibrable*>`.

## 3. Pruebas

**¿Cómo comprobaste que tu clase funciona? ¿Qué piezas del turno te sirvieron para verificarla?**

Después de ejecutar `iniciarTurno()`, `P-02` verifica el límite superior aceptable porque mide 15.0 kg y debe ser aceptada. `P-03` mide 16.2 kg y debe provocar un rechazo, mientras que `P-08` verifica el límite inferior porque mide 9.5 kg y también debe ser rechazada. El reporte final esperado asigna dos rechazos a `B-01`.

## 4. Bitácora

**Dudas que tuviste y cómo las resolviste:**

Tuve dudas sobre cuándo debía conservarse el desfase. Se resolvió usando `desfase_` como atributo privado y modificándolo únicamente mediante `calibrar()`. También confirmé que la regla debe aplicarse al peso medido, no al peso real.

**Errores que encontraste y cómo los corregiste:**

La firma de `inspeccionar()` fue corregida para incluir `const`, igualando el contrato abstracto de `Dispositivo` y la declaración de la clase derivada. Así puede sobrescribirse correctamente y llamarse de forma segura desde un puntero o referencia a `Dispositivo`.
