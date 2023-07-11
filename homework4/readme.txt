This assignment will be due at 11:59pm, July 12th.

Attention:

The main function in your program should accept various input from keyboard, don't just consider and test the example case. Your program should allow us to type arbitrarily into the terminal multiple times and get the according result. If you fail to do so, you will lose at least 10% of the assignment grade.

 

Part 1:  Binary Search Trees

Write a C program for the following question. 

Given the root of a binary search tree and a target value, return the value in the BST that is closest to the target.

Hint: Use a modified version of binary search. If the target is less than the current node value, go left, otherwise go right. At each point calculate the closest value to the target. 

Example:

Consider the following BST:

Input: root = [4,2,5,1,3], target = 3.714286

Output: Closest number = 4

NOTE: 

1. The target value here should be of type double. 

2. For the above question, you need to create the Binary Search Tree first based on the user input. 

 

Part 2 : Linked List Priority Queue

Write a C program to implement a "Linked List Priority Queue". The program should contain the following functions:

1. Enqueue - to insert values in the queue. Make sure the new node is inserted in the correct place according to it's priority value.

2. Dequeue - to delete values from the priority queue. Delete the head node (node with the highest priority). 

3. isEmpty - To check if the queue is empty

4. isFull - To check if the queue is full

Priority queue should be implemented using Linked Lists. The structure should contain data (int), priority (int) and next Node.

NOTE: Priority with LOWER value will come FIRST. E.g. Node with priority 2 will come before node with priority 4. 

All of the above functions should be in a do while loop and the input should be taken from the user. 

The example below is NOT an example of how the output should look. It merely shows sample answers. 

Example:

pq.png

After inserting the data with the given priority, the order of the priority queue should look like this:

7 -> 4 -> 5 -> 6

 

Submission Details:

Upload 2 C files for part 1 and 2 respectively on your previous GitHub repo. Submit the GitHub URL on Canvas.

Attention:

The main function in your program can accept any input from keyboard, don't just consider and test the example case. Your program should allow us to type arbitrarily into the terminal multiple times and get the according result. If you fail to do so, you will lose at least 10% of the assignment grade.

Rubric:

5M - Part 1 - BST

5M - Part 2 - Liked List Priority Queues

Code should compile without any errors and should deliver the correct output for both the questions.
