# Documentación de la clase: [Inserta aquí el nombre de tu clase]

> Copia este archivo como `docs/<matrícula>/<Clase>.md` (por ejemplo, `docs/0123456/Bascula.md`) y llena tu copia. No modifiques la plantilla.

**Documentación elaborada por:** [Arturo Lugo Rodriguez ]
**Matrícula:** [25162]
**Integrante:** [6]

## 1. Propósito

**¿Qué representa tu clase y qué revisa o registra de cada pieza?**

[`Durometro` representa un instrumento que mide la dureza de una pieza. De cada pieza revisa su dureza y la acepta solo si está dentro del rango permitido (entre 45 y 60, ambos incluidos). No modifica la pieza ni guarda historial.]

**¿Quién usa tu clase y para qué?**

[La usa `CeldaInspeccion`, que la guarda junto con los demás dispositivos como un `Dispositivo*`. La celda llama a `inspeccionar()` con cada pieza y registra un rechazo en `ReporteTurno` si devuelve `false`.]

## 2. Decisiones de diseño

**¿De qué clase o clases hereda tu clase y por qué?** (Si es `ReporteTurno`, explica por qué no hereda de `Dispositivo`.)

[Hereda de `Dispositivo` porque un durómetro *es un* dispositivo de la celda. Así cumple el contrato común (`inspeccionar()` y `descripcion()`) y la celda puede tratarlo igual que a cualquier otro dispositivo. No hereda de `Calibrable` porque no tiene desfase ni se calibra.]

**Atributos propios de tu clase y para qué sirve cada uno:**

[No tiene atributos propios. El identificador (`id_`) vive en `Dispositivo` y se accede con `id()`. La regla de dureza es fija, por lo que no hace falta guardar estado.]

**Métodos que sobrescribes con `override` y cómo implementaste la regla de inspección:**

[Sobrescribo `inspeccionar(const Pieza&) const` y `descripcion() const`. En `inspeccionar` devuelvo `pieza.dureza() >= 45 && pieza.dureza() <= 60`, es decir, acepta si la dureza está dentro del rango. `descripcion()` devuelve `"Durometro"`.]

**¿Qué métodos de tu clase son `const` y por qué?**

[`inspeccionar` y `descripcion` son `const` porque solo consultan: no cambian la pieza ni el estado del durómetro. Además, `inspeccionar` recibe `const Pieza&` para no copiar la pieza y garantizar que no se modifique.]

**Lo particular de tu clase.** Responde solo lo que corresponda a tu clase:
- `Bascula` o `CalibradorLaser`: ¿cómo modelaste el desfase y qué hace `calibrar()`?
- `SensorTemperatura`: ¿qué significa `final` y por qué tiene sentido en esta clase?
- `ReporteTurno`: ¿qué sobrecargas implementaste (constructores y operadores) y cómo decide `operator==` que dos reportes son iguales?
- `CamaraVision` o `Durometro`: ¿qué tuviste que hacer para que la celda pudiera usar tu clase sin modificarla?

[Para que la celda pudiera usar `Durometro` sin modificarla, solo tuve que heredar de `Dispositivo` y sobrescribir sus dos métodos virtuales con la firma exacta de la clase base. En `main` basta con crear el objeto y llamar a `agregarDispositivo(&durometro)`. `CeldaInspeccion` no cambió porque trabaja con `Dispositivo*` y el polimorfismo resuelve en ejecución qué `inspeccionar()` llamar.]

## 3. Pruebas

**¿Cómo comprobaste que tu clase funciona? ¿Qué piezas del turno te sirvieron para verificarla?**

[Agregué el durómetro (D-01) a la celda, ejecuté el turno completo y revisé en la salida que cada pieza mostrara `D-01 (Durometro): ACEPTA` o `RECHAZA` según su dureza. Comparé esos resultados con mi cálculo a mano, usando las piezas cuya dureza queda fuera de 45–60 (para ver el rechazo) y las que quedan justo en los límites (para confirmar que 45 y 60 se aceptan). Al final verifiqué que el reporte mostrara los rechazos de `D-01` que esperaba.]

## 4. Bitácora

**Dudas que tuviste y cómo las resolviste:**

[Tenía dudas sobre si el rango incluía los límites y sobre por qué `Durometro` no necesita atributos. Revisé el README para confirmar que los extremos se aceptan y entendí que, al no tener desfase ni estado, no hace falta guardar nada.]

**Errores que encontraste y cómo los corregiste:**

[VS Code marcó dos errores `C/C++(1455)`: "member function declared with 'override' does not override a base class member". El motivo era que `Dispositivo.h` aún no declaraba `inspeccionar` y `descripcion` como virtuales puros con `const`. Lo corregí agregando `virtual bool inspeccionar(const Pieza& pieza) const = 0;` y `virtual std::string descripcion() const = 0;` en `Dispositivo`, con la misma firma que en `Durometro`. También había pegado por error el contenido del header dentro de `Durometro.cpp`, y lo reemplacé por la implementación real.]
