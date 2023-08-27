#include <iostream>
#include <thread>
#include <vector>
#include <numeric>
#include <chrono>

template<typename T>
void naive_sum(std::vector<T>& vec) {
    T sum = 0;
    for (int i = 0; i < static_cast<int>(vec.size()); ++i) {
        sum += vec[i];
    }
    std::cout << "Naive sum = " << sum << std::endl;
}

template<typename T>
void accumulate_sum(std::vector<T>& vec) {
    std::cout << "Accumulate sum = " << std::accumulate(vec.begin(), vec.end(), 0LL) << std::endl;
}

template<typename T>
void thread_sum(std::vector<T>& vec, int num_threads) {
    int size = vec.size();
    std::thread threads[num_threads];
    T res = 0;
    T partial_res[num_threads];

    int chunk_size = (size + num_threads - 1) / num_threads;

    auto compute_sum = [&](int start, int end, int i) {
        for (int idx = start; idx <= end; ++idx) {
            partial_res[i] += vec[idx];    
        }
    };

    for (int i = 0; i < num_threads; ++i) {
        partial_res[i] = 0;
        int start = i*chunk_size;
        int end = std::min((i + 1) * chunk_size, size) - 1;
        threads[i] = std::thread(compute_sum, start, end, i);
    }

    for (int i = 0; i < num_threads; ++i) {
        threads[i].join();
        res += partial_res[i];
    }

    std::cout << "threaded sum = " << res << std::endl;
}

int main() {
       
    const int SIZE = 1'000'000'000;
    std::vector<long long> vec(SIZE);
    std::iota(vec.begin(), vec.end(), 0LL);
    
    auto start = std::chrono::high_resolution_clock::now();
    naive_sum<long long>(vec);
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Time taken = " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << std::endl;
 
    start = std::chrono::high_resolution_clock::now();
    accumulate_sum<long long>(vec);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Time taken = " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << std::endl;


    std::cout << "Number of thread supported = " << std::thread::hardware_concurrency() << std::endl;
    start = std::chrono::high_resolution_clock::now();
    thread_sum<long long>(vec, std::thread::hardware_concurrency());
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Time taken = " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << std::endl;
}
