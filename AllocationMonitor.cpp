#include "AllocationMonitor.hpp"
#include <new>
#include <iostream>

void* AllocationMonitor::allocate(std::size_t size, AllocationMonitor& monitor) {
    // if the user wants an adress, he will get one. but it cannot take zero memory, this is useful for empty structs for example.
    if(size == 0) ++size;

    void* memPointer = std::malloc(size);
    if(memPointer == NULL) throw std::bad_alloc{};

    monitor.m_currentlyAllocatedByteCount += size;

    return memPointer;
}

void AllocationMonitor::deallocate(void* ptr, AllocationMonitor& monitor) noexcept {
    // monitor.m_currentlyAllocatedByteCount -= sizeof(*ptr);
    // so uhh... thats not actaully possible since the ptr is a void ptr...
    free(ptr);
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