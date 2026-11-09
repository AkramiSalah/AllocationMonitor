#pragma once
#include <cstdlib>

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
};

void* operator new(std::size_t size);
void operator delete(void* ptr) noexcept;