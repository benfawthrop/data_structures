HOMEWORK 3: MATRIX CLASS


NAME:  Ben Fawthrop


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

cplusplus.com
Yashas Balaji
I went to ALAC for a short question but forget the name of the mentor

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  14



ORDER NOTATION:
For each of the functions below, write the order notation O().
Write each answer in terms of m = the number of rows and n = the
number of columns.  You should assume that calling new [] or delete []
on an array will take time proportional to the number of elements in
the array.

get
O(1)
This is because all we are doing in this function is indexing the array

set
O(1)
Also simply just indexing the 2d array

num_rows
O(1)
returns an integer

get_column
O(m)
it is only iterating down the 2d array, not across, so we only do m computations

operator<<
O(n*m)
traversing the whole 2d array, so we need width*height operations

quarter
O(n*m)
we are looping through the entire 2d array 4 different times so the true complexity is 4(n*m), however
we drop the constant

operator==
O(n*m)
traversing the whole 2d array, so we need width*height operations

operator!=
O(n*m)
Just running the opposite of == so same time complexity

swap_rows
O(1)
indexing is a constant time operation and there are no loops

rref (provided in matrix_main.cpp)
O(m*n^3)


TESTING & DEBUGGING STRATEGY: 
Discuss your strategy for testing & debugging your program.  
What tools did you use (gdb/lldb/Visual Studio debugger,
Valgrind/Dr. Memory, std::cout & print, etc.)?  How did you test the
"corner cases" of your Matrix class design & implementation?

Primarily, I used lldb and std::cout for debugging this program.
Using a secondary cpp file, I was able to write much more simple
test cases, which allowed me to test single functions and variables at a
time which made fixing bugs much easier than debugging the entire matrix_main
file all at once.  I used Valgrind a little in order to check for mem leaks
but not a lot.


EXTRA CREDIT: 
Indicate here if you implemented resize() for extra credit.  
Also document the order notation for your resize() function.



MISC. COMMENTS TO GRADER:  
(optional, please be concise!)


