Ejemplo de uso de std::condition_variable en C++. Este ejemplo muestra cómo utilizar condiciones de espera para sincronizar dos hilos: uno que produce datos y otro que consume esos datos.


Descripción del código
Clase ProductorConsumidor: Contiene un std::queue para almacenar datos, un std::mutex para proteger el acceso a la cola, y un std::condition_variable para la sincronización.

producir(int valor): Agrega un valor a la cola y notifica al consumidor.
consumir(): Espera hasta que hay un elemento en la cola, luego lo consume.
Funciones productor y consumidor: Las funciones que simulan la producción y el consumo de datos. El productor agrega datos a la cola, mientras que el consumidor los extrae.

Función main: Crea una instancia de ProductorConsumidor, lanza dos hilos (uno para el productor y otro para el consumidor), y espera a que ambos terminen.

Compilación
Compila el programa con:

bash
Copiar código
g++ -std=c++11 -o productor_consumidor productor_consumidor.cpp -lpthread
Ejecución
Luego ejecuta el programa:

bash
Copiar código
./productor_consumidor
Este código mostrará los números producidos y consumidos, mostrando cómo los hilos se sincronizan adecuadamente utilizando std::condition_variable.
