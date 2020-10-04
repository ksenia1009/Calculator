# Calculator
This is a program which solves any arithmetic expressions.  
Reverse Polish notation or RPN is used for this purpose (see more [RPN](https://en.wikipedia.org/wiki/Reverse_Polish_notation)).  

For this program you should have:
* CMake 3.6  
* gtest  
Or you should do:  
`sudo apt-get install libgtest-dev`
`sudo apt-get install cmake`  
`cd /usr/src/gtest`  
`sudo cmake CMakeLists.txt`  
`sudo make`  
`sudo cp *.a /usr/lib`  

## To run the program you should do:  
`cd Calculator/`  
`mkdir build`  
`cd build/`  
`cmake ..`  
`make`  
`./TestSerization`  
