#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <cstring>

// C vector implementation

void benchmark_cpp_vector(size_t count) {
    std::vector<int> vec;


    auto start = std::chrono::high_resolution_clock::now();

    for (size_t i = 0; i < count; ++i) {
        vec.push_back(static_cast<int>(i));
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "C++ vector:   " << duration.count() << " seconds" << std::endl;
}

int main() {
    const size_t count = 1000000000;

    std::cout << "Benchmarking vector insertions (" << count << " elements):" << std::endl;

    benchmark_cpp_vector(count);

    return 0;
}
