# Experimentos

Los experimentos son programas independientes: no usan las clases del proyecto y cada uno tiene su propio `main()`. Compílalos por separado; no incluyas `src/*.cpp` en estos comandos.

## 1. Memoria y *object slicing*

### Compilar y ejecutar

Desde la raíz del repositorio, en PowerShell:

```powershell
g++ -Wall -Wextra -std=c++17 experimentos/memoria.cpp -o memoria.exe
.\memoria.exe
```

### Salida observada

```text
--- Sin virtual ---
sizeof(Base1) = 16
sizeof(Derivada1) = 32
--- Con virtual ---
sizeof(Base2) = 24
sizeof(Derivada2) = 40
--- Slicing ---
Dentro de porValor, llamo quienSoy():
 Soy Base2
Dentro de porReferencia, llamo quienSoy():
 Soy Derivada2
```

Los tamaños dependen del compilador y la arquitectura. Los valores anteriores corresponden a la ejecución de este proyecto.

### Análisis

**1. ¿Por qué `sizeof(Derivada)` es mayor o igual que `sizeof(Base)`?**

Un objeto derivado contiene la parte completa de su clase base y, además, sus propios atributos. En este experimento, `Base1` tiene un `int` y un `double` (16 bytes con alineación); `Derivada1` agrega otro `double` y un `int`, por lo que ocupa 32 bytes. El tamaño podría ser igual si la clase derivada no agregara atributos.

**2. ¿Cuánto cambió el tamaño al agregar un método virtual y a qué se debe?**

En esta ejecución, cada clase creció 8 bytes: `Base` pasó de 16 a 24 y `Derivada` de 32 a 40. El compilador suele guardar en cada objeto un puntero oculto a la tabla de funciones virtuales (`vptr`), que permite seleccionar la implementación durante la ejecución. El tamaño exacto y el aumento pueden variar entre compiladores y arquitecturas.

**3. ¿Qué se perdió al pasar el objeto por valor?**

Al pasar un `Derivada2` por valor a una función que recibe `Base2`, solo se copia la parte `Base2`: se pierden los miembros propios `c` y `d`. Esto se llama *object slicing*. El objeto recibido es una `Base2`, por lo que se ejecuta `Base2::quienSoy()`. Al pasarlo por referencia no se copia y se conserva el tipo dinámico `Derivada2`.

**4. ¿Por qué esto no puede pasar con `Dispositivo` en el proyecto? ¿Cómo se evita en general?**

`Dispositivo` es abstracta porque declara `inspeccionar()` y `descripcion()` como virtuales puros; no se puede crear ni copiar un objeto `Dispositivo` por valor. Además, `CeldaInspeccion` guarda punteros `Dispositivo*`, que conservan el tipo dinámico del dispositivo concreto. En general, se evita el *slicing* usando referencias o punteros (incluidos punteros inteligentes) para los objetos polimórficos.

## 2. Destructor virtual

### Compilar y ejecutar

Compila y ejecuta las dos versiones por separado. La versión sin destructor virtual produce intencionalmente un warning del compilador.

```powershell
# Sin destructor virtual
g++ -Wall -Wextra -std=c++17 experimentos/destructores.cpp -o destructores.exe
.\destructores.exe

# Con destructor virtual
g++ -Wall -Wextra -std=c++17 -DCON_VIRTUAL experimentos/destructores.cpp -o destructores_virtual.exe
.\destructores_virtual.exe
```

### Warning esperado en la versión sin destructor virtual

El texto puede variar ligeramente según el compilador. Con GCC se observó:

```text
warning: deleting object of polymorphic class type 'Base' which has non-virtual destructor might cause undefined behavior [-Wdelete-non-virtual-dtor]
```

### Salida observada sin destructor virtual

```text
Constructor Base
Constructor Derivada (reserva memoria)
Hola desde Derivada
Destructor Base
```

### Salida observada con destructor virtual

```text
Constructor Base
Constructor Derivada (reserva memoria)
Hola desde Derivada
Destructor Derivada (libera memoria)
Destructor Base
```

La eliminación de un objeto derivado a través de un puntero a una base polimórfica cuyo destructor no es virtual tiene **comportamiento indefinido**. La salida sin destructor virtual es solo lo observado en esta ejecución; el estándar no garantiza ese resultado.

### Análisis

**1. ¿Qué diferencia hay entre las dos salidas?**

En la ejecución sin destructor virtual solo se observó el mensaje de `Base`. Con destructor virtual se ejecutaron primero `~Derivada()` y después `~Base()`, en ese orden.

**2. ¿Qué problema causaría si `Derivada` tuviera recursos que liberar?**

Si no se ejecuta `~Derivada()`, no se libera el arreglo reservado por esa clase. En un programa real, recursos como memoria, archivos o conexiones podrían quedar sin liberar. Como la operación tiene comportamiento indefinido, no se debe confiar en una salida concreta.

**3. ¿En qué cambio del diseño del proyecto sí causaría un problema?**

Actualmente, `main` crea los dispositivos como objetos locales y no los elimina mediante `delete` sobre un `Dispositivo*`. El problema aparecería, por ejemplo, si la celda pasara a ser propietaria de los dispositivos y los destruyera a través de esos punteros. Por eso `Dispositivo` declara un destructor virtual.
