#pragma once

#include <cstddef>

class IMemoryPool {
public:
    virtual ~IMemoryPool() = default;
    virtual void* allocate(size_t size) = 0; // Метод для выделения памяти
    virtual void deallocate(void* block) = 0; // Метод для освобождения памяти
    virtual size_t getUsedSize() const = 0; // Метод для получения использованного размера
    virtual size_t getPoolSize() const = 0; // Метод для получения общего размера пула
};