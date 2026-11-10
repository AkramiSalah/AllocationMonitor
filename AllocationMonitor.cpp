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

void* operator new[](std::size_t size) {
    return operator new(size);
}

void* operator new( std::size_t size, std::align_val_t al ){
    return AllocationMonitor::getInstance().allocate(size, static_cast<std::size_t>(al));
}

void* operator new[]( std::size_t size, std::align_val_t al ){
    return operator new (size, al);
}

//Replaceable non-throwing allocation functions
void* operator new( std::size_t size, const std::nothrow_t& tag ) noexcept{
    try {
        return operator new(size);
    }
    catch(...) {
        return nullptr;
    }
}

void* operator new[]( std::size_t size, const std::nothrow_t& tag ) noexcept{
    return operator new(size, tag);
}

void* operator new( std::size_t size, std::align_val_t al, const std::nothrow_t& tag ) noexcept{
    try {
        return operator new(size, al);
    }
    catch(...) {
        return nullptr;
    }
}

void* operator new[]( std::size_t size, std::align_val_t al, const std::nothrow_t& tag ) noexcept{
    return operator new(size, al, tag);
}


void operator delete(void* ptr) noexcept{
    AllocationMonitor::getInstance().deallocate(ptr);
}

void operator delete[]( void* ptr ) noexcept{
    operator delete(ptr);
}

void operator delete  ( void* ptr, std::align_val_t al ) noexcept{
    operator delete(ptr);
}

void operator delete[]( void* ptr, std::align_val_t al ) noexcept{
    operator delete(ptr, al);
}

void operator delete(void* ptr, std::size_t) noexcept {
    operator delete(ptr);
} 

void operator delete[]( void* ptr, std::size_t size ) noexcept{
    operator delete[](ptr);
}

void operator delete  ( void* ptr, std::size_t size, std::align_val_t al ) noexcept{
    operator delete(ptr, al);
}

void operator delete[]( void* ptr, std::size_t size, std::align_val_t al ) noexcept{
    operator delete[](ptr, al);
}

// Replaceable placement deallocation functions

void operator delete  ( void* ptr, const std::nothrow_t& tag ) noexcept{
    operator delete(ptr);
}

void operator delete[]( void* ptr, const std::nothrow_t& tag ) noexcept{
    operator delete[](ptr);
}

void operator delete  ( void* ptr, std::align_val_t al, const std::nothrow_t& tag ) noexcept{
    operator delete(ptr, al);
}

void operator delete[]( void* ptr, std::align_val_t al, const std::nothrow_t& tag ) noexcept{
    operator delete[](ptr, al);
}