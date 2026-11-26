# Documentación de la clase: ReporteTurno

> Copia este archivo como `docs/<matrícula>/<Clase>.md` (por ejemplo, `docs/0123456/Bascula.md`) y llena tu copia. No modifiques la plantilla.

**Documentación elaborada por:** Jorge Antonio Sadurni Cerdio
**Matrícula:** 25085
**Integrante:** 6

## 1. Propósito

**¿Qué representa tu clase y qué revisa o registra de cada pieza?**

Mi clase representa un reporte final al concluir cada determinado turno, la obligacion de este elemento es recibir lo que sucedio durante la tanda y registrar cada pieza inspeccionada y aceptada en toda la celda, asimismo el recuento de piezas rechazadas y finalmente entregar un resumen exacto de la actividad.

**¿Quién usa tu clase y para qué?**

En primer lugar, CeldaInspeccion usa esta clase a travez de metodos como registrarPieza() y registrarRechazo() cada vez que un dispositivo o calibrable evaluen las piezas, para notificarle a reporteTurno el conteo preciso.
De igual manera el main utiliza ReporteTurno para imprimir en consola el informe final, y las pruebas unitarias para confirmar que los resultados coincidan con lo esperado. 

## 2. Decisiones de diseño

**¿De qué clase o clases hereda tu clase y por qué?** (Si es `ReporteTurno`, explica por qué no hereda de `Dispositivo`.)

ReporteTurno tiene una relacion por composicion de celdaInspeccion, siguiendo el principio de "HAS A", ya que celdaInspeccion tiene un reporte, alimentando a ReporteTurno solo con la informacion de piezas inspeccionadas, aceptadas y el recuento de rechazos. 
ReporteTurno no hereda de dispositivo porque no es un aparato que mide o calibre, por lo que no tiene la relacion de "IS A" con dispositivo.

**Atributos propios de tu clase y para qué sirve cada uno:**

Los atributos propios son:
  int inspeccionadas_ = 0;
  int aceptadas_ = 0;
  std::map<std::string, int> rechazos_;
Inspeccionadas sirve para el conteo de piezas evaluadas durante el turno y aceptadas para la cantidad de piezas que fueron aprobadas, ambas son de forma entero e inicializan en 0 para empezar en un estado valido de manera controlada . Mientras que rechazos sirve para identificar globalmente que dispositivos rechazaron ciertas cantidades de piezas. 

**Métodos que sobrescribes con `override` y cómo implementaste la regla de inspección:**

ReporteTurno no tiene ningun metodo con override o lo haya sobrescrito ya que no tiene ninguna relacion polimorfica con dispositivo debido a que sus obligaciones no le exigen tener comunicacion con esa clase. Ademas de que no implementa reglas personalizadas con inspeccion.

**¿Qué métodos de tu clase son `const` y por qué?**

Los métodos de la clase que son const son:
inspeccionadas() const
aceptadas() const
rechazadas() const
operator==(const ReporteTurno &otro) const

Llevan const al final porque son operaciones de solo lectura: únicamente consultan los contadores o comparan el estado de dos reportes sin alterar los atributos internos (inspeccionadas_, aceptadas_ y rechazos_). Además, esto permite invocarlos de forma segura cuando se recibe un objeto como referencia constante (const ReporteTurno&).

**Lo particular de tu clase.** Responde solo lo que corresponda a tu clase:
- `Bascula` o `CalibradorLaser`: ¿cómo modelaste el desfase y qué hace `calibrar()`?
- `SensorTemperatura`: ¿qué significa `final` y por qué tiene sentido en esta clase?
- `ReporteTurno`: ¿qué sobrecargas implementaste (constructores y operadores) y cómo decide `operator==` que dos reportes son iguales?
- `CamaraVision` o `Durometro`: ¿qué tuviste que hacer para que la celda pudiera usar tu clase sin modificarla?

ReporteTurno: Sobrecarge los constructores de 
ReporteTurno() = default;
ReporteTurno(int inspeccionadas, int aceptadas, const std::map<std::string, int> &rechazos);
Ya que el constructor en default se crea vacio, ideal para cuando una tanda esta por empezar, mientras que el otro constructor, que esta lleno, se utiliza para comparar y las pruebas unitarias.
Operadores sobrecargados: Se sobrecargaron operator== para poder comparar directamente dos instancias de ReporteTurno, y operator<< (declarado como friend) para formatear e imprimir el contenido del reporte en un flujo de salida como std::cout o std::ostringstream.

Criterio de igualdad en operator==: Dos reportes se consideran iguales únicamente cuando sus tres atributos internos coinciden exactamente: inspeccionadas_ == otro.inspeccionadas_, aceptadas_ == otro.aceptadas_ y que el mapa rechazos_ contenga exactamente los mismos identificadores de dispositivo con la misma cantidad de rechazos (rechazos_ == otro.rechazos_).

## 3. Pruebas

**¿Cómo comprobaste que tu clase funciona? ¿Qué piezas del turno te sirvieron para verificarla?**

Comprobé el funcionamiento de la clase escribiendo un main de prueba con aserciones (assert) compilado con g++ -std=c++17 y verificando la salida formateada en consola mediante el operador sobrecargado <<.

Para validar la clase utilicé los siguientes casos de prueba del turno:

Estado inicial del reporte: Creé una instancia vacía con el constructor por defecto (ReporteTurno()) y verifiqué con assert que los contadores inspeccionadas(), aceptadas() y rechazadas() iniciaran en 0.

Registro de pieza aceptada: Simulé el paso de una pieza aprobada llamando a registrarPieza(true), confirmando que aumentaran en 1 tanto el total de piezas inspeccionadas como el de aceptadas.

Registro de pieza rechazada por dispositivo: Simulé una pieza defectuosa llamando a registrarPieza(false) y registrarRechazo("BAS-01"), comprobando que rechazadas() subiera a 1 y que el identificador "BAS-01" apareciera correctamente en el desglose impreso en consola (=== Reporte de turno ===).

## 4. Bitácora

**Dudas que tuviste y cómo las resolviste:**

Sobrecarga y métodos const: Tenía duda sobre qué métodos debían ser const y cómo aplicar la sobrecarga en la clase. Revisando ReporteTurno.h comprendí que los métodos de consulta y comparación llevan const para garantizar solo lectura, y que la sobrecarga permite tener dos constructores (vacío y parametrizado) además de definir operator== y operator<<.

Pruebas con assert: Aprendí a usar assert de cassert para validar automáticamente que los contadores coincidieran con los valores esperados sin revisar todo manualmente.

**Errores que encontraste y cómo los corregiste:**

Constructor por defecto duplicado: El compilador marcó error porque definí ReporteTurno() en ReporteTurno.cpp cuando ya estaba declarado como = default; en el .h. Lo corregí borrando la definición duplicada en el .cpp.

Typo en atributo y parámetro sin usar: Corregí un error de escritura en inspeccionadas_ dentro del constructor parametrizado y ajusté registrarPieza(bool aceptada) para utilizar el parámetro booleano y eliminar la advertencia de compilación.
