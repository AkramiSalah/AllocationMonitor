#pragma once
#include <cstdlib>
#include "Timer.hpp"
#include "Utilities.hpp"

// Note that this is a singelton!
class AllocationMonitor {
public:
    void printStatus();

    void* allocate(std::size_t size, std::size_t al = __STDCPP_DEFAULT_NEW_ALIGNMENT__);

    void deallocate(void* ptr) noexcept;

    static AllocationMonitor& getInstance() {
        static AllocationMonitor instance;
        return instance;
    }

    AllocationMonitor(const AllocationMonitor& other) = delete;
    AllocationMonitor operator=(const AllocationMonitor& other) = delete;

private:
    AllocationMonitor() = default;
    std::size_t m_currentlyAllocatedByteCount; // currently allocated BY USER! the bookkeeping overhead does not count!
};

struct AllocationHeader {
    std::size_t m_allocatedSize;
    Timer m_timer;
    void* m_allocatedBufferAddress;

    AllocationHeader(const std::size_t userDataSize, void* allocatedBufferAddress) :
        m_allocatedSize(userDataSize),
        m_timer(Timer()),
        m_allocatedBufferAddress(allocatedBufferAddress){};
};


// new operators

// 1)
void* operator new( std::size_t size );

// 2)
void* operator new[]( std::size_t size );

// 3)
void* operator new  ( std::size_t size, std::align_val_t al );

// 4)
void* operator new[]( std::size_t size, std::align_val_t al );

//Replaceable non-throwing allocation functions

// 5)
void* operator new  ( std::size_t size, const std::nothrow_t& tag ) noexcept;

// 6)
void* operator new[]( std::size_t size, const std::nothrow_t& tag ) noexcept;

// 7)
void* operator new  ( std::size_t size, std::align_val_t al, const std::nothrow_t& tag ) noexcept;

// 8)
void* operator new[]( std::size_t size, std::align_val_t al, const std::nothrow_t& tag ) noexcept;

// delete operators

// 1)
void operator delete  ( void* ptr ) noexcept;

// 2)
void operator delete[]( void* ptr ) noexcept;

// 3)
void operator delete  ( void* ptr, std::align_val_t al ) noexcept;

// 4)
void operator delete[]( void* ptr, std::align_val_t al ) noexcept;

// 5)
void operator delete  ( void* ptr, std::size_t size ) noexcept;

// 6)
void operator delete[]( void* ptr, std::size_t size ) noexcept;

// 7)
void operator delete  ( void* ptr, std::size_t size, std::align_val_t al ) noexcept;

// 8)
void operator delete[]( void* ptr, std::size_t size, std::align_val_t al ) noexcept;

// Replaceable placement deallocation functions

// 9)
void operator delete  ( void* ptr, const std::nothrow_t& tag ) noexcept;

// 10)
void operator delete[]( void* ptr, const std::nothrow_t& tag ) noexcept;

// 11)
void operator delete  ( void* ptr, std::align_val_t al, const std::nothrow_t& tag ) noexcept;

// 12)
void operator delete[]( void* ptr, std::align_val_t al, const std::nothrow_t& tag ) noexcept;