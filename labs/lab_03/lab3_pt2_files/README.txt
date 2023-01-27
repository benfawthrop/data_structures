Ben Fawthrop
Lab 03
Data Structures

In order to fix our compilation errors, #ifndef, #define, and #endif statements were placed on all of our
header files

on our first run after fixing compilation errors, the program exits with
libc++abi: terminating with uncaught exception of type std::length_error: vector
zsh: abort      ./lab3_pt2.out input2.txt

the compilations we get prior to this run are:

When compiling our roads.cpp file:
    warning: reference to stack memory associated with local variable 'roads' returned [-Wreturn-stack-address]
        return roads;
               ^~~~~
    warning: comparison of integers of different signs: 'int' and 'std::vector<Line>::size_type' (aka 'unsigned long') [-Wsign-compare]
        for (int i = 0; i < roads.size(); i++) {
                        ~ ^ ~~~~~~~~~~~~
    warning: variable 'count' is uninitialized when used here [-Wuninitialized]
            count++;
            ^~~~~
When compiling line.cpp:
    warning: expression result unused [-Wunused-value]
            gradient * -1;
            ~~~~~~~~ ^ ~~
    warning: non-void function does not return a value in all control paths [-Wreturn-type]
    }
    ^
When compiling point.cpp:
    warning: unused variable 'answer' [-Wunused-variable]
        double answer = rise / run;
               ^


