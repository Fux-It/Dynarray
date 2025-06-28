#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <cstring>
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

// C vector implementation

void benchmark_cpp_vector(size_t count) {
    std::vector<int> vec;
    vec.reserve(count); 

    auto start = std::chrono::high_resolution_clock::now();


    int64_t sum = 0;
    for (size_t i = 0; i < count; ++i) {
        vec.push_back(static_cast<int>(i));
        sum += vec.back();
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "C++ vector resize:   " << duration.count() << " seconds" << std::endl;
    std::cout << "sum - " << sum << std::endl;
}

void benchmark_cpp_resize(size_t count) {
    std::vector<int> vec;

    auto start = std::chrono::high_resolution_clock::now();


    int64_t sum = 0;
    for (size_t i = 0; i < count; ++i) {
        vec.resize(i + 1);
        vec[i] = i;
        sum += vec[i];
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "C++ vector:   " << duration.count() << " seconds" << std::endl;
    std::cout << "sum - " << sum << std::endl;
    std::cout << "capacity - " << vec.capacity() << std::endl;
}

int main() {
    const size_t count = 1000000000;

    std::cout << "Benchmarking vector resize (" << count << " elements):" << std::endl;

    benchmark_cpp_resize(count);
}
