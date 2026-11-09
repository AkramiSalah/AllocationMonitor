#include "AllocationMonitor.hpp"
#include <new>
#include <iostream>
#include <cstring>

void* AllocationMonitor::allocate(std::size_t size, AllocationMonitor& monitor) {
    void* memPointer = std::malloc(sizeof(AllocationHeader) + size);
    if(memPointer == NULL) throw std::bad_alloc{};
    
    AllocationHeader header{size};
    std::memcpy(memPointer, &header, sizeof(header));

    monitor.m_currentlyAllocatedByteCount += size;

    return static_cast<char*>(memPointer) + sizeof(AllocationHeader);
}

void AllocationMonitor::deallocate(void* ptr, AllocationMonitor& monitor) noexcept {
    AllocationHeader* header = static_cast<AllocationHeader*>(ptr) - 1; // the magic of ptr artihmetic :)
    monitor.m_currentlyAllocatedByteCount -= header->m_allocatedSize;

    // just for testing right now, DELETE THIS LATER!
    std::cout << header->m_timer.elapsedMs() << " have elapsed since allocating this\n";

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

void operator delete(void* ptr, std::size_t) noexcept {
    AllocationMonitor::getInstance().deallocate(ptr);
}