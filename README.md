# AllocationMonitor
This project is a WOP. 
This README is also a WOP.
---

right now the main feature(s) I strive to support are:
- *detection of new*
- *detection of delete calls*
- *infodumping into a file (std out, or maybe just any file...)*

possible future features which right now im unsure how to acomplish are:
- *having this all abstracted away in such a way where the user doesnt have to do anything for it to all work*

possible scope extending features are:
- *adding timing and benchmarking support*


---

This is an exploration of replacing global functions, compiled in C++20.
Providing a single instance (via Singleton) of a class whose whole job is to maintain a record of how many bytes have been requested by a user at any point in time,
with a timer just for fun.
This is by no means an attempt to replace any alternatives, and is more of a proof-of-concept/WOP.

### AllocationMointor provides means to allocate and deallocate memory.
by appending a block of memory for internal bookeeping is placed right before the allocated space, an [hand crafted BTW..](ASCII diagram) to show this is provided:
   /=====================================================================================================================================\
<- | - - - Padding (Optional) - - -| Bookeepeing (Not Optional, check AllocationMointor::AllocationHeader for more detail) | Your Storage |->
   \=====================================================================================================================================/

## Possible Future Goals:
    -[ ] Add a .log file that shows current status
    -[ ] Add a tool to visualize the .log file
    -[ ] Benchmark against regular new delete for, generate a plot to show results using matplotlib/R.
    -[ ] Add Customization of AllocationMointor::AllocationHeader by providing a way to make it user defined, let it run callbacks, and so on.

## Example Usage:
clone this repo into <foldername>
compile using Cmake
#include "AllocationMonitor.hpp"
and thats it youre ready to roll.
you can just forget about it from there.
a log file will be generated for you.
you may inspect it. or use the tool ill hopefully provide...


## Closing Statements:
    This is by no means an attempt to replace any alternatives, and is more of a proof-of-concept/WOP. ??
