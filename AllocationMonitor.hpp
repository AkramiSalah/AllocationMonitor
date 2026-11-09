#pragma once
#include <cstdlib>
#include "Timer.hpp"

// Note that this is a singelton!
class AllocationMonitor {
public:
    void printStatus();

    void* allocate(std::size_t size, AllocationMonitor& monitor = AllocationMonitor::getInstance());
    void deallocate(void* ptr, AllocationMonitor& monitor = AllocationMonitor::getInstance()) noexcept;

    static AllocationMonitor& getInstance() {
        static AllocationMonitor instance;
        return instance;
    }

    AllocationMonitor(const AllocationMonitor& other) = delete;
    AllocationMonitor operator=(const AllocationMonitor& other) = delete;

private:
    AllocationMonitor() = default;
    std::size_t m_currentlyAllocatedByteCount;
};

struct AllocationHeader {
    std::size_t m_allocatedSize;
    Timer m_timer;

    explicit AllocationHeader(const std::size_t allocatedSize) :
        m_allocatedSize(allocatedSize), m_timer(Timer()) {};
};

////////// TODO : literally make all of these :(((((

// cppref's new, delete pages have a list that says what the default behaviour is so lets see if it works for me.. 

// news

void* operator new  ( std::size_t size ); // done :)

// void* operator new[]( std::size_t size );

// void* operator new  ( std::size_t size, std::align_val_t al );

// void* operator new[]( std::size_t size, std::align_val_t al );

//Replaceable non-throwing allocation functions
// void* operator new  ( std::size_t size, const std::nothrow_t& tag );

// void* operator new[]( std::size_t size, const std::nothrow_t& tag );

// void* operator new  ( std::size_t size, std::align_val_t al, const std::nothrow_t& tag ) noexcept;

// void* operator new[]( std::size_t size, std::align_val_t al, const std::nothrow_t& tag ) noexcept;

// deletes


void operator delete  ( void* ptr ) noexcept; // done :)

// void operator delete[]( void* ptr ) noexcept;

// void operator delete  ( void* ptr, std::align_val_t al ) noexcept;

// void operator delete[]( void* ptr, std::align_val_t al ) noexcept;

void operator delete  ( void* ptr, std::size_t sz ) noexcept; // done :)

// void operator delete[]( void* ptr, std::size_t sz ) noexcept;

// void operator delete  ( void* ptr, std::size_t sz, std::align_val_t al ) noexcept;

// void operator delete[]( void* ptr, std::size_t sz, std::align_val_t al ) noexcept;

// Replaceable placement deallocation functions

// void operator delete  ( void* ptr, const std::nothrow_t& tag ) noexcept;

// void operator delete[]( void* ptr, const std::nothrow_t& tag ) noexcept;

//void operator delete  ( void* ptr, std::align_val_t al, const std::nothrow_t& tag ) noexcept;

//void operator delete[]( void* ptr, std::align_val_t al, const std::nothrow_t& tag ) noexcept;