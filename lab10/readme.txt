The lab contains two parts, create one C program for each part.

Part A:
Implement a hash table with chaining, you should implement the insert and print functionalities for the table. The values of the table are taken as input from the user, after that, print out the content of the table.

Hash function to be used - k mod size.

Sample Example is shown below for your reference:
Chain Size:

3

Number of values:

5

Input Values:

3

6

1

5

4

The table:

Chain[0] -> 3 -> 6 -> NULL

Chain[1] -> 1 -> 4 -> NULL

Chain[2] -> 5 -> NULL

Part B:
Create a hash table without chaining, you should implement three different probing functions to handle collisions (linear probing, quadratic probing, double hashing).

In the same c file, create 3 different functions for linear probing, quadratic probing and double hashing. Let the user choose which probing to use. The values to be inserted should be taken from the user. 

Hash function for linear and quadratic probing - k mod size

Hash function for double hashing: 

h1 = k mod size

h2 = 7 - (k mod 7)

h = (h1 + i*h2) mod size

 

Submission:
Upload 2 C files for parts A and B on GitHub. Submit the GitHub link on canvas.

Rubric:
10M - Code compiles without any errors and delivers the correct output.

Marks will be deducted for a late submission.
