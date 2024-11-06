#pragma once
#include "IMemoryPool.h"
#include <cstddef>
#include <vector>

class MemoryPool : public IMemoryPool {
public:
    MemoryPool(size_t poolSize); // �����������
    ~MemoryPool() override; // ����������

    void* allocate(size_t size) override; // ���������������� ����� ��� ��������� ������
    void deallocate(void* block) override; // ���������������� ����� ��� ������������ ������

    size_t getUsedSize() const override; // ���������������� ����� ��� ��������� ��������������� �������
    size_t getPoolSize() const override; // ���������������� ����� ��� ��������� ������ ������� ����

private:
    char* pool; // ��������� �� ��� ������
    size_t poolSize; // ����� ������ ����
    size_t usedSize; // ������������ ������
    std::vector<void*> freeBlocks; // ������ ��� �������� ��������� ������

    struct MemBlockHeader { // ��������� ����� ������
        size_t size; // ������ �����
        bool isFree; // ����, �������� �� ����
    };

    MemBlockHeader* header_from_block(void* block); // ����� ��� ��������� ��������� �� �����
};