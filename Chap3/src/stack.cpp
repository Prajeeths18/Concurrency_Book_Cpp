#include <thread>
#include <iostream>
#include <deque>

// Spotting race conditions that inherent in interfaces

/**
 * - A stack has the following operations: 
 *  - push()
 *  - pop()
 *  - top() 
 *  - empty()
 *  - size()
*/

// Here is a simple interface for a stack:
template<typename T, typename Container = std::deque<T>>
class stack {
public:
    /* some constructors */

    bool empty() const;
    size_t size() const;
    T& top();
    T const& top() const;   
    void push(T const&);
    void push(T&&);
    void pop();
    void swap(stack&&);
};

/**
 * Assume that each of the functions above has a lock around it. Still, this structure is not free 
 * of race conditions.
 * 
 * Why? Because the results of empty() and size() can't be relied on.
 * Suppose one thread calls empty() function, and retuns false (assume that there is only one element left). 
 * A second thread comes in and calls pop(). This makes the size 0. Now, if the first thread is resumed,
 * there is a problem. Before suspension, thread 1 operated on the condition that the stack isn't empty.
 * But now, it is. 
*/
