Homework 3

The following homework assignment will have 2 parts:

Part A: Linear Search
Implement a linear search algorithm using C. Your program should follow the steps below:

The array to be searched from and the target to be found should be taken as input from the user. You can assume that all of them are non-negative.
Print out the array and the target
Convert all of them to their binary form, represented by an integer. For example, an int of 5 will become an int of 101. You can assume that the user input can always be convertible to another int.
Print out the converted array and the converted target.
Perform a linear search on the converted numbers and the converted target.
Print out the position for the target, if it doesn’t exist, print -1.
After the search, convert all of them back to their original form.
Print out the original array and the original target
Part B: Binary Search
Implement a binary search algorithm using C. Your program should follow the steps below:

The array to be searched from and the target to be found should be taken as input from the user. You can assume that all of them are non-negative.
Print out the array and the target
Sort the array (any sorting algorithm is ok) and perform a binary search on the sorted numbers and the target.
Print out the search result (position in the sorted array), if no answer can be found, print -1.
Please do not use any library functions except for I/O operations. And there is no binary conversion needed for Part B.

Submission Details:
Create 2 different files on GitHub for the 2 parts mentioned above. Submit the GitHub repository link on canvas.

 

Output example for Part A:
Input array size:

5

Input elements of the array:

9

6

7

4

8

Input target:

7

The array:

9 6 7 4 8

The target:

7

Converted array:

1001 110 111 100 1000

Converted target:

111

Search result:

2

Original array:

9 6 7 4 8

Original target:

7

Output example for Part B:
Input array size:

5

Input elements of the array:

9

6

7

4

8

Input target:

7

The array:

9 6 7 4 8

The target:

7

Search result:

2