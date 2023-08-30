#include <iostream>
#include <thread>
#include <mutex>
#include <list>
#include <algorithm>

/**
 * Command to run: make run_simple_mutex
*/

/**
 * Instead of using lock() and unlock(), use the "lock_guard" template provided by C++
 * Why? Because, while using lock and unlock, we need to call unlock in all the possible 
 * out paths for a function
 * 
 * Using lock_guard enables to use the RAII idiom, and subsequently taking care of destroying
 * the resource even in case of an exception
*/

std::list<int> foo;
std::mutex mtx;

void add_to_list(int new_value) {
    std::lock_guard<std::mutex> guard(mtx); // Lock acquired here
    foo.push_back(new_value);
} // lock released here, as scope ends here

bool check_if_present(int value) {
    std::lock_guard<std::mutex> guard(mtx);
    return std::find(foo.begin(), foo.end(), value) != foo.end();
}

int main() {

    add_to_list(1);
    add_to_list(2);
    add_to_list(3);

    std::cout << check_if_present(1) << std::endl;
    std::cout << check_if_present(3) << std::endl;
    std::cout << check_if_present(4) << std::endl;

    return 0;
}