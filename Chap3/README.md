# Sharing data between **threads**

## Race conditions
A condition where the outcome depends on the order of the execution between two threads

- Most race conditions are benign, but some are "problematic" - and race conditions, henceforth will refer to such problematic ones.
- These happen when there are two or more distinct pieces of data needs to be modified in order to complete the operation, and will require more than 1 instruction to do so.
- This can be seen as "**broken invariant**"
  - Eg: consider deleting a node from a doubly linked list. For simplicity, assume that this node is internal(there is a non-NULL left and right node for this node). 
  - The deletion of this node requires the following operations:
    - set left.next = right
    - set right.prev = left
    - delete current node
  - We see that we need to modify left's next value and right's prev value, which are two distinct pieces of data. After all the operations, the state of the list is correct. But what if a thread has executed only the first operation? And suddenly the second thread gets scheduled? This leads to the broken invariants problem, and hence a "Race condition".