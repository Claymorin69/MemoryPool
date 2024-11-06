#pragma once

#include <cstddef>

class IMemoryPool {
public:
    virtual ~IMemoryPool() = default;
    virtual void* allocate(size_t size) = 0; // ����� ��� ��������� ������
    virtual void deallocate(void* block) = 0; // ����� ��� ������������ ������
    virtual size_t getUsedSize() const = 0; // ����� ��� ��������� ��������������� �������
    virtual size_t getPoolSize() const = 0; // ����� ��� ��������� ������ ������� ����
};