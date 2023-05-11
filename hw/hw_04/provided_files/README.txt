HOMEWORK 4: TOOL RENTAL LISTS


NAME:  Ben Fawthrop


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

Yashas Balaji
Jeremy P. (office hours)


Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  24



ORDER NOTATION:
Use these variables to analyze each phase of computation.  Briefly
justify your answer for each part.


i = # of different inventory items
c = # of different customers
p = # of pending customers
q = max quantity of a particular tool owned by the store
r = max # of tools rented or requested by a customer at one time
p = total # of pending tool rentals
e = # of rental or return events


Load inventory file:
O(i^2)
This is because we need to iterate through each item to
add it to the list, but we also need to iterate through the list in order to
add the tool in the correct spot

Rental event:
O(r * q)
This is because the rent operation happens r times, where r is the
number of tools a customer requests.  Since our find tool operation is a
linear search, its linear time, so time complexity is r * q

Return event - no pending customer(s):
O(r * i * c)
This is because the return operation happens r times, where r is the
number of tools the customer wants to return at a time. Since we are doing a
linear search for both Inventory and Customer objects, i * c * r is our time
complexity

Return event - with pending customer(s):
O(r * 2i * 2c)
This is because the item that needs to be moved from the queue is already at
the front so its a constant time operation. The issue is that the rent operation
needs to be called again on the freshly un-queued customer, so that operation is done twice

Entire program:
O(i^2 + c^2(r * 2i * c) + c(r + p) + i(r + p) 2i + 2c)
The first part of this comes from the get_input functions, the middle portion is
outputting our data, and the final part is deallocating our memory



MISC. COMMENTS TO GRADER:
(optional, please be concise!)

