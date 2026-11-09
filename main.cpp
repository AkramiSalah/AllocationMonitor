#include "AllocationMonitor.hpp"
#include <vector>


int main() {
    {
        int* numPtr = new int;
        *numPtr = 0xDEADBEEF;
        delete numPtr;
    }

    std::vector<int> vec(1000, 0xDEADBEEF);

    AllocationMonitor::getInstance().printStatus();
}