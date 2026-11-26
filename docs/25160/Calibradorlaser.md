 Copia este archivo como `docs/<matrícula>/<Clase>.md` (por ejemplo, `docs/0123456/Bascula.md`) y llena tu copia. No modifiques la plantilla.

**Documentación elaborada por:** Brayan Alberto Lopez Contreras
**Matrícula:** 25160
**Integrante:** 2

## 1. Propósito

**¿Qué representa tu clase y qué revisa o registra de cada pieza?**

Mi clase representa el calibrador láser de la celda. Lo que revisa de cada pieza es su largo: si mide entre 49.5 y 50.5 mm la acepta y si queda fuera de ese rango la rechaza, incluyendo los dos límites como válidos. También es un dispositivo que se puede calibrar, ya que sale de fábrica descalibrado y mide 0.3 mm de menos, entonces hay que calibrarlo antes de empezar el turno para que sus mediciones sean correctas.

**¿Quién usa tu clase y para qué?**

CeldaInspeccion usa esta clase a través de un Dispositivo*, sin saber que es un CalibradorLaser. En iniciarTurno() revisa con dynamic_cast cuáles dispositivos también son Calibrable y les llama calibrar(). Después, en procesar(), le pide inspeccionar() y descripcion() igual que a los demás dispositivos, y si rechaza la pieza se registra el rechazo en ReporteTurno. El main solo crea el objeto (calidad::CalibradorLaser laser("L-01");) y lo agrega a la celda.

## 2. Decisiones de diseño

**¿De qué clase o clases hereda tu clase y por qué?** (Si es `ReporteTurno`, explica por qué no hereda de `Dispositivo`.)

Hereda de Dispositivo y de Calibrable (herencia múltiple).

Hereda de Dispositivo porque un calibrador láser es un dispositivo de la celda (relación "IS A"), cumple con inspeccionar una pieza y con decir qué tipo de dispositivo es, por eso la celda lo puede usar sin conocer su clase.

Hereda de Calibrable porque además tiene la capacidad de calibrarse. Calibrable es una interfaz sin atributos, así que no se genera el problema del diamante.

**Atributos propios de tu clase y para qué sirve cada uno:**

El único atributo propio es double desfase_ (en mm). Sirve para guardar el error de medición del dispositivo. Empieza en -0.3, que es el desfase de fábrica, y calibrar() lo deja en 0.0. Es privado para que solo se pueda modificar calibrando. El id no lo guardo en mi clase, lo guarda Dispositivo.

**Métodos que sobrescribes con `override` y cómo implementaste la regla de inspección:**

Sobrescribo tres métodos, los tres con override:

inspeccionar(const Pieza& pieza): calcula el largo medido sumando el largo de la pieza más desfase_, y regresa true si ese valor está entre 49.5 y 50.5. La regla se aplica al valor medido y no al largo real de la pieza.

descripcion() const: regresa "Calibrador laser", que es el texto que imprime la celda.

calibrar(): viene de Calibrable y deja el desfase en 0.0.

**¿Qué métodos de tu clase son `const` y por qué?**

El método const es descripcion() const, porque solo consulta el nombre y no modifica el objeto.

inspeccionar no es const porque la firma es la que acordó el equipo en Dispositivo (sin const) y el override tiene que ser igual que el de la base. En mi clase solo lee desfase_, entonces podría ser const, pero habría que cambiarlo en Dispositivo y en todas las demás clases. calibrar() no es const porque modifica desfase_.

**Lo particular de tu clase.** Responde solo lo que corresponda a tu clase:
- `Bascula` o `CalibradorLaser`: ¿cómo modelaste el desfase y qué hace `calibrar()`?
- `SensorTemperatura`: ¿qué significa `final` y por qué tiene sentido en esta clase?
- `ReporteTurno`: ¿qué sobrecargas implementaste (constructores y operadores) y cómo decide `operator==` que dos reportes son iguales?
- `CamaraVision` o `Durometro`: ¿qué tuviste que hacer para que la celda pudiera usar tu clase sin modificarla?

El desfase lo modelé como un atributo double privado que se suma al largo real de la pieza para obtener el valor que mide el dispositivo. Empieza en -0.3 mm, por lo que sin calibrar mide de menos. calibrar() asigna desfase_ = 0.0 y regresa true para que iniciarTurno() imprima OK. Si se llama varias veces el resultado es el mismo.

Esto cambia el resultado del turno. Con P-05 (50.7 mm reales), sin calibrar mide 50.4 y la acepta por error, y ya calibrado mide 50.7 y la rechaza. Con P-10 (49.6 mm) pasa lo contrario: sin calibrar mide 49.3 y la rechaza, y calibrado mide 49.6 y la acepta.

## 3. Pruebas

**¿Cómo comprobaste que tu clase funciona? ¿Qué piezas del turno te sirvieron para verificarla?**

Hice dos pruebas.

Primero escribí un programa aparte con assert (pruebas/prueba_calibrador_laser.cpp) que usa solo CalibradorLaser y Pieza, compilado con g++ -Wall -Wextra -std=c++17 -Iinclude pruebas/prueba_calibrador_laser.cpp src/CalibradorLaser.cpp src/Pieza.cpp -o prueba_laser. Verifiqué lo siguiente:

Datos básicos: que el id fuera "L-01" y la descripción "Calibrador laser".

Límites ya calibrado: que 49.5 y 50.5 se aceptaran y que 49.4 y 50.6 se rechazaran.

Piezas del turno: P-05 (50.7) y P-08 (51.0) se rechazan, P-10 (49.6) se acepta.

Sin calibrar: que P-05 se aceptara y P-10 se rechazara por el desfase, y que después de llamar calibrar() los resultados se corrigieran. También que calibrar dos veces no cambiara nada.

Uso por puntero: que funcionara a través de un Dispositivo* y que dynamic_cast a Calibrable* encontrara la parte calibrable del mismo objeto.

La salida fue "Todas las pruebas de CalibradorLaser pasaron".

Después compilé el programa completo con g++ -Wall -Wextra -std=c++17 -Iinclude src/*.cpp -o celda, sin errores ni warnings, y comparé la salida con el cálculo a mano del README: L-01 rechazó P-05 y P-08 (2 rechazos) y al final salió "Reporte correcto". P-04 (50.5 mm) me sirvió para confirmar que el límite superior está incluido.

## 4. Bitácora

**Dudas que tuviste y cómo las resolviste:**

Destructor: no sabía si necesitaba uno propio. Como la clase no reserva recursos no declaré ninguno, el destructor virtual ya lo heredan Dispositivo y Calibrable y con eso es seguro destruirla por un puntero a la base.

Valor medido: entendí que la regla se compara contra el largo medido (largo real + desfase) y no contra el largo real, por eso la celda debe calibrar en iniciarTurno() antes de inspeccionar.

**Errores que encontraste y cómo los corregiste:**

Resultados incorrectos sin calibrar: sin calibrar el láser, P-05 salía ACEPTADA en vez de RECHAZADA y P-10 salía RECHAZADA en vez de ACEPTADA. Con la prueba verifiqué que mi calibrar() deja el desfase en 0.0 y que inspeccionar() usa ese mismo atributo.