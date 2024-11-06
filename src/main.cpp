#include "MemoryPool.h"
#include <iostream>

int main() {
    setlocale (LC_ALL, "RUS");
    const size_t poolSize = 1024; // Размер пула памяти в байтах
    IMemoryPool* memoryPool = new MemoryPool(poolSize); // Создаем пул памяти через интерфейс

    try {
        // Пример выделения памяти
        void* block1 = memoryPool->allocate(32);
        std::cout << "Успешно выделено 32 байта для block1.\n";

        void* block2 = memoryPool->allocate(64);
        std::cout << "Успешно выделено 64 байта для block2.\n";

        // Пример освобождения памяти
        memoryPool->deallocate(block1);
        std::cout << "Успешно освобожден block1.\n";

        memoryPool->deallocate(block2);
        std::cout << "Успешно освобожден block2.\n";

        // Проверка использования памяти
        std::cout << "Используемая память: " << memoryPool->getUsedSize() << " байт\n";
        std::cout << "Общий размер пула: " << memoryPool->getPoolSize() << " байт\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Исключение: " << e.what() << '\n';
    }

    delete memoryPool; // Освобождаем память, выделенную под пул
    return 0;
}