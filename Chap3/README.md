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

## How to avoid these? 
- A straightforward way is to see that since the entire issue is because of the fact that one thread is not able to complete all the operations at one go, we "lock" the data so that only one thread can access it at a time. So, we thread 1 is accessing the linked list, thread 2 is **not allowed** to modify the list, until thread1 is done. 
- Another way is to design the set of operations in such a way that they are **indivisible**, that there won't be any issue of cutting off in between. This is referred to as **Lock Free Programming**.
- Yet another way is to use the idea of **transactions** from the world of databases. We make all the changes and store it as a log, and commit it all at once. If for some reason, the commit was unsuccessful, restart the transaction again.
  

## Using mutexes
Refer to [mutexes.c](mutexes.c) for some code

* Note that merely surrounding every function that accesses data with lock_guards is not sufficient.
* If a function returns a pointer or a reference to the data, then the caller can access the data without acquiring the lock, which is a fatal flaw.

