#include "MemoryPool.h"
#include <iostream>

int main() {
    setlocale (LC_ALL, "RUS");
    const size_t poolSize = 1024; // ������ ���� ������ � ������
    IMemoryPool* memoryPool = new MemoryPool(poolSize); // ������� ��� ������ ����� ���������

    try {
        // ������ ��������� ������
        void* block1 = memoryPool->allocate(32);
        std::cout << "������� �������� 32 ����� ��� block1.\n";

        void* block2 = memoryPool->allocate(64);
        std::cout << "������� �������� 64 ����� ��� block2.\n";

        // ������ ������������ ������
        memoryPool->deallocate(block1);
        std::cout << "������� ���������� block1.\n";

        memoryPool->deallocate(block2);
        std::cout << "������� ���������� block2.\n";

        // �������� ������������� ������
        std::cout << "������������ ������: " << memoryPool->getUsedSize() << " ����\n";
        std::cout << "����� ������ ����: " << memoryPool->getPoolSize() << " ����\n";
    }
    catch (const std::exception& e) {
        std::cerr << "����������: " << e.what() << '\n';
    }

    delete memoryPool; // ����������� ������, ���������� ��� ���
    return 0;
}