HOMEWORK 10: DISTANCE FIELDS & FAST MARCHING METHOD


NAME:  Ben Fawthrop


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

Yashas Balaji
Nyx G.

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  15



NAIVE ALGORITHM:

Order Notation:
O(w^2 * h^2)

Timing Experiment Data:
Input                 User     Sys    Total
tiny_5x5              0.00    0.00    0.008
small_10x10           0.00    0.00    0.007
squiggle_30x30        0.01    0.00    0.020
lines_100x100         0.66    0.00    0.663
d_s_300x300          52.13    0.07   52.204
dots_1000x1000  Used ^C after 6:56 seconds (never finished)

Discussion:
The reason the time complexity doesn't involve p, is because we are checking
every pixel every time regardless of its color, so we only are operating on
w and h time.  This approach is terribly inefficient because your time grows
exponentially as input size grows.



IMPROVED ALGORITHM:

Order Notation:
O(w * h * p)

Timing Experiment Data:
Input                 User     Sys     Total
tiny_5x5              0.00    0.00     0.006
small_10x10           0.00    0.00     0.006
squiggle_30x30        0.00    0.00     0.008
lines_100x100         0.03    0.00     0.033
d_s_300x300           2.72    0.02     2.740
dots_1000x1000      450.25    0.70   7:31.51


Discussion:
Since we are not doing (w * h) comparisons for every pixel, we are able to significantly
cut down on time complexity to O(w * h * p), because for every pixel in the board
we are checking it against every black pixel.  This allows us to actually get a result for
the 1000 by 1000 test case, albeit slowly.


FAST MARCHING METHOD (with a map):

Order Notation:
O(w * h * log p)

Timing Experiment Data:
Input                 User     Sys     Total
tiny_5x5              0.00    0.01     0.109
small_10x10           0.00    0.00     0.008
squiggle_30x30        0.01    0.00     0.016
lines_100x100         0.07    0.00     0.081
d_s_300x300           0.63    0.00     0.639
dots_1000x1000        7.74    0.05     7.790

Discussion:
This is because our priority queue operations, such as our two percolate
functions take O(log n) time.  Since we do one of these operations once essentially
every pixel, we take w * h * log p time.  This is SIGNIFICANTLY faster
than either of our other two approaches



DISTANCE FIELD VISUALIZATIONS FOR EXTRA CREDIT:




FAST MARCHING METHOD (with a hash table) FOR EXTRA CREDIT:

Order Notation:

Timing Experiment Data:

Discussion:



MISC. COMMENTS TO GRADER:  
Optional, please be concise!






