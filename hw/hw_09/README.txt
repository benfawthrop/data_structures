HOMEWORK 9: MINIBLAST


NAME:  Ben Fawthrop


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

Yashas Balaji
Josh Parent
Colin P
Daniel N

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  18


HASH FUNCTION DESCRIPTION
The hash function I chose was the same one that was implemented in
the lab 11 hashset. The reason I chose this because it was
very efficient and generally avoided collisions.  It
was implemented using bitwise operators to create a hash value.

This hash value is then % by the length of the array to find it's index

HASH TABLE IMPLEMENTATION
My hash table is implemented around a vector of hash_nodes.
Each node store a kmer and all the positions in the database that
the kmer appears at.  Collisions are solved using linear probing in the positive
direction.  Nodes can be searched for using the overloaded
[] operator.  This operator cannot be used to modify the table, however
it allows for a fairly fast find operator


ANALYSIS OF PERFORMANCE OF YOUR ALGORITHM:
(order notation & concise paragraph, < 200 words)

L = length of the genome sequence
q - query length
p - number of different locations where key is found
k - key size (k-mer size)

How much memory will the hash table data structure require (order notation for memory use)?
O(L*(k + p))

Each node in the hash table takes up O(k + p) space, so assuming we have L nodes, our
space complexity will be as above

What is the order notation for performance (running time) of each of
the commands? What about for the hash table's insert, find, and resize?

getting queries - O(q * p) because you must iterate through the length of
    the whole query to check for mismatches as well as iterating through all
    the different locations where kmer is found
building the table - O(L) must iterate through the entire database
insert - O(1) in the best case O(L) in the worst case
find (operator[]) - O(1) in the best case O(L) in the worst case
resize - O(L) because you need to rehash every existing node

whole program - O((L-k+1)(k+p))
    This is because building the hashtable takes O((L-k+1)*(q*p)) time,
    and searching for each query in the hashtable takes O(1) time.



EXTRA CREDIT
Add a new command to implement the database using one of the other
 data structures that we have covered so far in the course: 
vectors, lists, arrays etc. 

Compare the performance your alternative method to the homework method
by making a table of run times for each of the genomes and query 
sets provided with the homework  and compare the times to build
the index and the times to process the queries. 
Document any new commands you have added in your README file.



MISC. COMMENTS TO GRADER:  
(optional, please be concise!)


