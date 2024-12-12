
//g++ -std=c++11 -o productor_consumidor productor_consumidor.cpp -lpthread

#include <iostream>
#include <thread>
#include <condition_variable>
#include <queue>
#include <chrono>

class ProductorConsumidor {
public:
    void producir(int valor) {
        std::unique_lock<std::mutex> lock(mtx);
        cola.push(valor);
        std::cout << "Producido: " << valor << std::endl;
        cv.notify_one(); // Notifica al consumidor que hay un nuevo elemento
    }

    int consumir() {
        std::unique_lock<std::mutex> lock(mtx);
        // Espera hasta que la cola no esté vacía
        cv.wait(lock, [this]() { return !cola.empty(); });
        int valor = cola.front();
        cola.pop();
        std::cout << "Consumido: " << valor << std::endl;
        return valor;
    }

private:
    std::queue<int> cola; // Cola para almacenar los datos producidos
    std::mutex mtx;       // Mutex para proteger el acceso a la cola
    std::condition_variable cv; // Condición para la sincronización
};

void productor(ProductorConsumidor& pc) {
    for (int i = 0; i < 10; ++i) {
        pc.producir(i);
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simula tiempo de producción
    }
}

void consumidor(ProductorConsumidor& pc) {
    for (int i = 0; i < 10; ++i) {
        pc.consumir();
        std::this_thread::sleep_for(std::chrono::milliseconds(150)); // Simula tiempo de consumo
    }
}

int main() {
    ProductorConsumidor pc;

    std::thread t1(productor, std::ref(pc));
    std::thread t2(consumidor, std::ref(pc));

    t1.join();
    t2.join();

    return 0;
}
