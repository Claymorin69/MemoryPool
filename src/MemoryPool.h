#pragma once
#include "IMemoryPool.h"
#include <cstddef>
#include <vector>

class MemoryPool : public IMemoryPool {
public:
    MemoryPool(size_t poolSize); // Конструктор
    ~MemoryPool() override; // Деструктор

    void* allocate(size_t size) override; // Переопределенный метод для выделения памяти
    void deallocate(void* block) override; // Переопределенный метод для освобождения памяти

    size_t getUsedSize() const override; // Переопределенный метод для получения использованного размера
    size_t getPoolSize() const override; // Переопределенный метод для получения общего размера пула

private:
    char* pool; // Указатель на пул памяти
    size_t poolSize; // Общий размер пула
    size_t usedSize; // Используемый размер
    std::vector<void*> freeBlocks; // Вектор для хранения свободных блоков

    struct MemBlockHeader { // Заголовок блока памяти
        size_t size; // Размер блока
        bool isFree; // Флаг, свободен ли блок
    };

    MemBlockHeader* header_from_block(void* block); // Метод для получения заголовка из блока
};