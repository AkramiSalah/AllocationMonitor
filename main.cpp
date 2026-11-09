#include "AllocationMonitor.hpp"
#include <vector>


int main() {
    int* numPtr = new int;
    *numPtr *= 123;
    
    AllocationMonitor::getInstance().printStatus();
}