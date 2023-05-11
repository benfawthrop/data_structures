HOMEWORK 6: INVERSE WORD SEARCH


NAME:  Ben Fawthrop


COLLABORATORS AND OTHER RESOURCES: 
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

Nia H

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.

ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  24


ALGORITHM ANALYSIS:
What's the order notation of your algorithm?
O((wl)^2 * r * (wh-l) * (2^(wh-l)) * f + s * (w*h + w*h))

The time complexity of this program can be broken down into a few key segments.
The first segment is taking inputs which has a complexity of O(r+f).  The next simple
portion is printing the solutions which has a complexity of O(s*w*h).  Next is adding random
letters to the finished boards.  This also has a complexity of O(s*w*h).  Finally, finding valid boards
has a complexity of O((wl)^2 * r * (wh-l) * (2^(wh-l))).  This is because there are (wl)^2 ways to place
each required word on the board, and there are r required words. Additionally, there are (wh-l) spaces
remaining on the board to fill with other letters, and there are 2^(wh-l) ways to fill these spaces with
letters or leave them blank. Finally, we need to check if each board contains the forbidden words, which
requires O(f) time



TEST CASE SUMMARY:
How did your program perform on the different test cases?  Summarize
the running times.  (It's ok if it didn't finish the harder examples.)
What new test cases did you create and how did it perform on those
tests?

PUZZLE      RUN TIME    SOLUTIONS
1           0.008s      8
2           0.009s      4
3           2.520s      8
5           0.059s      100
6           1.380s      216
7           1.550s      80
mine1       0.083s      2912

the case mine1 looks like this:
4 4
+ frog
+ bear
- lion
- deer
    I built this case to test the random letter filler function
    As you can see, it builds a lot of solutions because there
    are quite a few open coords.

MISC. COMMENTS TO GRADER:  
Optional, please be concise!


