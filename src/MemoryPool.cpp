#include "MemoryPool.h"
#include <iostream>
#include <cassert>
#include <stdexcept>

MemoryPool::MemoryPool(size_t poolSize) : poolSize(poolSize), usedSize(0) {
    pool = new char[poolSize]; // Выделяем память под пул
    std::cout << "Пул памяти размером " << poolSize << " байт создан.\n";
}

MemoryPool::~MemoryPool() {
    delete[] pool; // Освобождаем память пула
    std::cout << "Пул памяти уничтожен.\n";
}

MemoryPool::MemBlockHeader* MemoryPool::header_from_block(void* block) {
    return reinterpret_cast<MemBlockHeader*>(static_cast<char*>(block) - sizeof(MemBlockHeader)); // Получаем заголовок блока
}

void* MemoryPool::allocate(size_t size) {
    if (size == 0) {
        throw std::invalid_argument("Запрашиваемый размер выделения равен 0"); // Проверка на нулевой размер
    }

    // Поиск свободного блока
    for (auto it = freeBlocks.begin(); it != freeBlocks.end(); ++it) {
        MemBlockHeader* header = header_from_block(*it);
        if (header->size >= size) {
            freeBlocks.erase(it);
            usedSize += size + sizeof(MemBlockHeader);
            header->isFree = false;
            return static_cast<void*>(reinterpret_cast<char*>(header) + sizeof(MemBlockHeader)); // Возвращаем указатель на блок
        }
    }

    // Проверка на переполнение пула
    if (usedSize + size + sizeof(MemBlockHeader) > poolSize) {
        throw std::bad_alloc();
    }

    // Выделение нового блока
    void* block = pool + usedSize;
    usedSize += size + sizeof(MemBlockHeader);
    MemBlockHeader* header = new (block) MemBlockHeader{ size, false }; // Создаем заголовок блока

    std::cout << "Выделено " << size << " байт. Всего использовано: " << usedSize << " байт.\n";
    return static_cast<void*>(static_cast<char*>(block) + sizeof(MemBlockHeader)); // Возвращаем указатель на блок
}

void MemoryPool::deallocate(void* block) {
    if (block == nullptr) {
        throw std::invalid_argument("Попытка освободить нулевой указатель"); // Проверка на нулевой указатель
    }

    MemBlockHeader* header = header_from_block(block);
    if (header->isFree) {
        throw std::runtime_error("Обнаружено двойное освобождение"); // Проверка на двойное освобождение
    }

    header->isFree = true; // Помечаем блок как свободный
    freeBlocks.push_back(header); // Добавляем блок в список свободных
    usedSize -= (header->size + sizeof(MemBlockHeader)); // Обновляем использованный размер
    std::cout << "Освобождено " << header->size << " байт. Всего использовано: " << usedSize << " байт.\n";
}

size_t MemoryPool::getUsedSize() const {
    return usedSize; // Возвращаем использованный размер
}

size_t MemoryPool::getPoolSize() const {
    return poolSize; // Возвращаем общий размер пула
}