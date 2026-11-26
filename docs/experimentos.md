# Experimentos

Los dos experimentos son programas independientes (no usan las clases del proyecto) y se compilan por separado de src/*.cpp.

## Experimento 1: Memoria y object slicing

*Compilar y ejecutar:*

g++ -Wall -Wextra -std=c++17 experimentos/memoria.cpp -o memoria
./memoria


*Salida:*

--- Sin virtual ---
sizeof(Base1)     = 16
sizeof(Derivada1) = 32
--- Con virtual ---
sizeof(Base2)     = 24
sizeof(Derivada2) = 40
--- Slicing ---
Dentro de porValor, llamo quienSoy():
  Soy Base2
Dentro de porReferencia, llamo quienSoy():
  Soy Derivada2


*1. ¿Por qué sizeof(Derivada) es mayor o igual que sizeof(Base)?*

Porque un objeto derivado contiene dentro una parte Base completa y además sus propios atributos. En el experimento, Base1 tiene un int y un double (16 bytes con alineación) y Derivada1 agrega un double y un int, por lo que pasa a 32 bytes. Nunca puede ser menor, y sería igual solo si la derivada no agregara atributos.

*2. ¿Cuánto cambió el tamaño al agregar un método virtual y a qué se debe?*

Cada clase creció 8 bytes: Base pasó de 16 a 24 y Derivada de 32 a 40. Esos 8 bytes son el puntero oculto a la tabla virtual (vptr) que el compilador agrega a cada objeto de una clase con métodos virtuales. Ese puntero apunta a la vtable, que guarda las direcciones de los métodos virtuales y permite decidir en tiempo de ejecución cuál versión llamar (binding dinámico). El tamaño exacto puede variar según compilador y arquitectura (aquí, 64 bits).

*3. ¿Qué se perdió al pasar el objeto por valor?*

Se perdió la parte derivada. Al pasar Derivada2 por valor a una función que recibe Base2, se copia solo la parte Base2 (object slicing): se pierden c y d, y el objeto copiado es realmente de tipo Base2, con el vptr de Base2. Por eso se ejecutó Soy Base2 aunque el método esté sobrescrito. Al pasarlo por referencia no se copia nada y se ejecuta Soy Derivada2.

*4. ¿Por qué esto no puede pasar con Dispositivo en su proyecto? ¿Cómo se evita en general?*

Dispositivo es abstracta (tiene inspeccionar y descripcion virtuales puros), así que no se pueden crear objetos Dispositivo ni pasarlos por valor: el compilador lo rechaza. Además, CeldaInspeccion guarda std::vector<Dispositivo*>, es decir punteros, y recibe Pieza por const&. Por eso Bascula, CalibradorLaser, CamaraVision, SensorTemperatura y Durometro siempre se usan por su tipo real y se ejecuta la versión correcta de cada método. En general se evita pasando objetos polimórficos por referencia (const&) o por puntero (o puntero inteligente), y haciendo abstracta la clase base.

## Experimento 2: Destructor virtual

*Compilar y ejecutar:*

# Sin virtual
g++ -Wall -Wextra -std=c++17 experimentos/destructores.cpp -o destructores
./destructores

# Con virtual
g++ -Wall -Wextra -std=c++17 -DCON_VIRTUAL experimentos/destructores.cpp -o destructores_virtual
./destructores_virtual


*Salida SIN virtual en el destructor de Base:*

warning: deleting object of polymorphic class type 'Base' which has non-virtual destructor might cause undefined behavior [-Wdelete-non-virtual-dtor]
Constructor Base
Constructor Derivada (reserva memoria)
Hola desde Derivada
Destructor Base


*Salida CON virtual en el destructor de Base:*

Constructor Base
Constructor Derivada (reserva memoria)
Hola desde Derivada
Destructor Derivada (libera memoria)
Destructor Base


*Explicación del warning:*

El compilador avisa que se está haciendo delete sobre un objeto de una clase polimórfica (tiene un método virtual) a través de un puntero Base* cuyo destructor no es virtual. Eso es comportamiento indefinido: como el destructor no es virtual, delete p solo sabe llamar al destructor de Base (tipo del puntero) y no al de Derivada (tipo real del objeto). El warning describe exactamente el error que provoca el experimento.

*1. ¿Qué diferencia hay entre las dos salidas?*

Sin virtual solo se ejecuta ~Base(): nunca se llama a ~Derivada(). Con virtual se ejecutan los dos, primero ~Derivada() y luego ~Base() (de lo más derivado a lo más base).

*2. ¿Qué consecuencia tiene?*

Si Derivada tiene recursos propios (aquí un arreglo new int[100]; en general memoria, archivos o conexiones), al no ejecutarse su destructor nunca se liberan y hay fuga de memoria o recursos abiertos.

*3. ¿Por qué no se notó en el proyecto?*

En main los dispositivos son objetos locales (Bascula bascula("B-01"); etc., incluido Durometro) y no se destruyen por un Dispositivo* con delete. Pero si la celda los creara con new y los borrara a través de Dispositivo*, el error aparecería. Por eso Dispositivo y Calibrable declaran destructor virtual, y las 5 clases de dispositivos (Bascula, CalibradorLaser, CamaraVision, SensorTemperatura y Durometro) quedan protegidas al heredar de Dispositivo.