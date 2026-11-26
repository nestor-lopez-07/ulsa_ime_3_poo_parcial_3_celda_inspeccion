# Documentación de la clase: [Inserta aquí el nombre de tu clase]

> Copia este archivo como `docs/<matrícula>/<Clase>.md` (por ejemplo, `docs/0123456/Bascula.md`) y llena tu copia. No modifiques la plantilla.

**Documentación elaborada por:** [Daniel Alejandro Hernández Sánchez]
**Matrícula:** [25029]
**Integrante:** [3]

# Documentación de la clase: CamaraVision

## 1. Propósito

**¿Qué representa tu clase y qué revisa o registra de cada pieza?**

Representa una cámara de visión dentro de la celda de inspección que revisa cada Pieza de forma visual a partir de sus datos (como su cantidad de defectos reportados por defectos()) para saber si cumple con el criterio de inspección y pasa la revisión o si falla.

**¿Quién usa tu clase y para qué?**

La usa CeldaInspeccion cuando va procesando las piezas del turno. Como la celda guarda los dispositivos como punteros a Dispositivo, llama de forma polimórfica a inspeccionar(pieza) y a descripcion() sin tener que saber el tipo exacto, y con eso se arma el ReporteTurno.

## 2. Decisiones de diseño

**¿De qué clase o clases hereda tu clase y por qué?**

Hereda de Dispositivo porque es un dispositivo más dentro de la celda de inspección; así comparte la interfaz base (id(), inspeccionar(...), descripcion()) y puede ir en el mismo vector<Dispositivo*> que los demás sensores/dispositivos. No hereda de Calibrable porque en el diseño UML la cámara no lleva calibración como Bascula o CalibradorLaser.

**Atributos propios de tu clase y para qué sirve cada uno:**

Según el diagrama UML, CamaraVision no agrega atributos propios extra y usa el id que hereda de Dispositivo para identificar qué cámara es. (Si en mi .h puse algún atributo adicional, por ejemplo algún umbral o dato extra, aquí lo anoto).

**Métodos que sobreescribes con override y cómo implementaste la regla de inspección:**

Sobreescribo inspeccionar(const Pieza& pieza) y descripcion() con override. En inspeccionar reviso la regla de inspección visual sobre pieza (por ejemplo, que no tenga defectos o cumpla lo esperado) y regreso true si pasa o false si se rechaza; en descripcion() regreso un texto con el tipo de cámara y su id.

**¿Qué métodos de tu clase son const y por qué?**

Los métodos que solo consultan o inspeccionan sin cambiar nada (como inspeccionar y descripcion, además de los heredados como id()) van marcados como const porque no modifican el estado de CamaraVision ni el de la Pieza, y así se pueden llamar desde referencias o punteros const.

**Lo particular de tu clase.**

CamaraVision: ¿qué tuviste que hacer para que la celda pudiera usar tu clase sin modificarla?
  Para que CeldaInspeccion pudiera usar CamaraVision sin tocar su código, heredé públicamente de Dispositivo, implementé los métodos virtuales puros (inspeccionar y descripcion) con override respetando sus firmas exactas, y registré la instancia de CamaraVision en la celda como Dispositivo*. De ese modo la celda solo trabaja contra la interfaz de Dispositivo mediante polimorfismo.

## 3. Pruebas

**¿Cómo comprobaste que tu clase funciona? ¿Qué piezas del turno te sirvieron para verificarla?**

Lo probé corriendo el programa / pruebas con piezas distintas del turno: unas sin defectos (para verificar que inspeccionar regrese true y se cuenten como aceptadas) y otras con defectos o fuera de criterio (para verificar que regrese false y se reflejen en el rechazo del turno), además de revisar que descripcion() e id() salieran bien.

## 4. Bitácora

**Dudas que tuviste y cómo las resolviste:**

Al principio me quedó duda de cómo encajaba CamaraVision con CeldaInspeccion y Dispositivo sin modificar la celda, y qué debía llevar const o override. Lo resolví revisando el diagrama UML, las declaraciones en Dispositivo.h / Pieza.h / CeldaInspeccion.h y probando la compilación.

**Errores que encontraste y cómo los corregiste:**

Me topé con detalles típicos de firmas (const, referencias const Pieza&, override y #include de cabeceras) al compilar y enlazar con el resto del proyecto; los fui corrigiendo comparando la declaración en CamaraVision.h con Dispositivo.h y volviendo a compilar hasta que no marcó errores ni warnings.
