#include <iostream>
#include <thread>
#include <mutex>
#include <string>
#include <algorithm>

class data {
    int a; 
    std::string b;
public:
    void do_something();
};

class data_wrapper {
private:
    data d;
    std::mutex mtx;
public:

    // a method that passes a function, which operates on the data 
    template<typename T> 
    void process_data(T func) {
        std::lock_guard<std::mutex> lock(mtx);
        func(d);    
    }
};

data *unprotected;

void malicious_function(data *garbage) {
    unprotected = garbage;
}

data_wrapper wrapper;

void foo() {
    wrapper.process_data(malicious_function);
    unprotected -> do_something(); // call's garbage's do something, which might be dangerous
}

int main() {

    foo();

    return 0;
}