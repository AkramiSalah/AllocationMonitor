#include "AllocationMonitor.hpp"
#include <vector>


int main() {
    {
        int* numPtr = new int;
        *numPtr = 0xDEADBEEF;
        delete numPtr;
    }

    int* numPtr = new int;
    *numPtr = 0xDEADBEEF;
    
    AllocationMonitor::getInstance().printStatus();
}