#include "AllocationMonitor.hpp"
#include <new>
#include <iostream>
#include <cstring>
#include <cstddef>

void* AllocationMonitor::allocate(std::size_t size, std::size_t al) {
    if(al < alignof(std::max_align_t)) al = alignof(std::max_align_t); // otherwise alligned alloc fails
    
    std::size_t alignedHeaderSize = alignedSize(sizeof(AllocationHeader), al);
    std::size_t alignedUserDataSize = alignedSize(size, al);
    
    void* memPointer = std::aligned_alloc( al, alignedHeaderSize + alignedUserDataSize );
    if(memPointer == NULL) throw std::bad_alloc{};
    
    char* headerAddress = static_cast<char*>(memPointer) + alignedHeaderSize - sizeof(AllocationHeader);

    AllocationHeader header{size, memPointer};
    std::memcpy(headerAddress, &header, sizeof(header));

    this->m_currentlyAllocatedByteCount += size;

    char* userDataAdress = headerAddress + sizeof(AllocationHeader);
    return userDataAdress;
}

void AllocationMonitor::deallocate(void* ptr) noexcept {
    if(!ptr) return;
    AllocationHeader* headerPtr = reinterpret_cast<AllocationHeader*>(static_cast<char*>(ptr) - sizeof(AllocationHeader)); 
    this->m_currentlyAllocatedByteCount -= headerPtr->m_allocatedSize;

    // just for testing right now, DELETE THIS LATER!
    std::cout << headerPtr->m_timer.elapsedMs() << " have elapsed since allocating this\n";

    free(headerPtr->m_allocatedBufferAddress);
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