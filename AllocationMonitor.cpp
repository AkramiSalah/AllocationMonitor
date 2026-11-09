#include "AllocationMonitor.hpp"
#include <new>
#include <iostream>

void* AllocationMonitor::allocate(std::size_t size, AllocationMonitor& monitor) {
    // if the user wants an adress, he will get one. but it cannot take zero memory, this is useful for empty structs for example.
    if(size == 0) ++size;

    void* memPointer = std::malloc(sizeof(AllocationHeader) + size);
    if(memPointer == NULL) throw std::bad_alloc{};

    static_cast<AllocationHeader*>(memPointer)->m_allocatedSize = size;
    monitor.m_currentlyAllocatedByteCount += size;

    return static_cast<AllocationHeader*>(memPointer) + 1;
}

void AllocationMonitor::deallocate(void* ptr, AllocationMonitor& monitor) noexcept {
    AllocationHeader* header = static_cast<AllocationHeader*>(ptr) - 1; // the magic of ptr artihmetic :)
    monitor.m_currentlyAllocatedByteCount -= header->m_allocatedSize;

    free(header);
}


void AllocationMonitor::printStatus() {
    std::cout << this->m_currentlyAllocatedByteCount << " Byte(s) Currently Allocated\n";
}


void* operator new(std::size_t size) {
    return AllocationMonitor::getInstance().allocate(size);
}


void operator delete(void* ptr) noexcept{
    AllocationMonitor::getInstance().deallocate(ptr);
}