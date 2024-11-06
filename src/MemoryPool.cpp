#include "MemoryPool.h"
#include <iostream>
#include <cassert>
#include <stdexcept>

MemoryPool::MemoryPool(size_t poolSize) : poolSize(poolSize), usedSize(0) {
    pool = new char[poolSize]; // �������� ������ ��� ���
    std::cout << "��� ������ �������� " << poolSize << " ���� ������.\n";
}

MemoryPool::~MemoryPool() {
    delete[] pool; // ����������� ������ ����
    std::cout << "��� ������ ���������.\n";
}

MemoryPool::MemBlockHeader* MemoryPool::header_from_block(void* block) {
    return reinterpret_cast<MemBlockHeader*>(static_cast<char*>(block) - sizeof(MemBlockHeader)); // �������� ��������� �����
}

void* MemoryPool::allocate(size_t size) {
    if (size == 0) {
        throw std::invalid_argument("������������� ������ ��������� ����� 0"); // �������� �� ������� ������
    }

    // ����� ���������� �����
    for (auto it = freeBlocks.begin(); it != freeBlocks.end(); ++it) {
        MemBlockHeader* header = header_from_block(*it);
        if (header->size >= size) {
            freeBlocks.erase(it);
            usedSize += size + sizeof(MemBlockHeader);
            header->isFree = false;
            return static_cast<void*>(reinterpret_cast<char*>(header) + sizeof(MemBlockHeader)); // ���������� ��������� �� ����
        }
    }

    // �������� �� ������������ ����
    if (usedSize + size + sizeof(MemBlockHeader) > poolSize) {
        throw std::bad_alloc();
    }

    // ��������� ������ �����
    void* block = pool + usedSize;
    usedSize += size + sizeof(MemBlockHeader);
    MemBlockHeader* header = new (block) MemBlockHeader{ size, false }; // ������� ��������� �����

    std::cout << "�������� " << size << " ����. ����� ������������: " << usedSize << " ����.\n";
    return static_cast<void*>(static_cast<char*>(block) + sizeof(MemBlockHeader)); // ���������� ��������� �� ����
}

void MemoryPool::deallocate(void* block) {
    if (block == nullptr) {
        throw std::invalid_argument("������� ���������� ������� ���������"); // �������� �� ������� ���������
    }

    MemBlockHeader* header = header_from_block(block);
    if (header->isFree) {
        throw std::runtime_error("���������� ������� ������������"); // �������� �� ������� ������������
    }

    header->isFree = true; // �������� ���� ��� ���������
    freeBlocks.push_back(header); // ��������� ���� � ������ ���������
    usedSize -= (header->size + sizeof(MemBlockHeader)); // ��������� �������������� ������
    std::cout << "����������� " << header->size << " ����. ����� ������������: " << usedSize << " ����.\n";
}

size_t MemoryPool::getUsedSize() const {
    return usedSize; // ���������� �������������� ������
}

size_t MemoryPool::getPoolSize() const {
    return poolSize; // ���������� ����� ������ ����
}