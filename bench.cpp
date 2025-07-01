#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <cstring>
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

// C vector implementation

void benchmark_cpp_vector(size_t count) 
{
    std::vector<int> vec;
    vec.reserve(count); 

    auto start = std::chrono::high_resolution_clock::now();


    int64_t sum = 0;
    for (size_t i = 0; i < count; ++i) 
    {
        vec.push_back(static_cast<int>(i));
        sum += vec.back();
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "C++ vector resize:   " << duration.count() << " seconds" << std::endl;
    std::cout << "sum - " << sum << std::endl;
}

void benchmark_cpp_resize(size_t count) 
{
    std::vector<int> vec;
    
    vec.resize(100000);
    vec.resize(8);
    vec.shrink_to_fit();

    auto start = std::chrono::high_resolution_clock::now();


    int64_t sum = 0;
    for (size_t i = 0; i < count; ++i) 
    {
        vec.resize(i + 1, i);
        sum += vec[i];
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "C++ vector:   " << duration.count() << " seconds" << std::endl;
    std::cout << "sum - " << sum << std::endl;
    std::cout << "capacity - " << vec.capacity() << std::endl;
}

void benchmark_cpp_insert(size_t count) 
{
    std::vector<int> vec;
    

    auto start = std::chrono::high_resolution_clock::now();


    int64_t sum = 0;
    for (size_t i = 0; i < count; ++i) 
    {
        vec.insert(vec.begin(), i);
        sum += vec[0];
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "C++ vector:   " << duration.count() << " seconds" << std::endl;
    std::cout << "sum - " << sum << std::endl;
    std::cout << "capacity - " << vec.capacity() << std::endl;
    std::cout << "size - " << vec.size() << std::endl;
}

void benchmark_cpp_erase(size_t count) 
{
    std::vector<int> vec;
    
    for(size_t i = 0; i < count; i++)
        vec.push_back(i);

    auto start = std::chrono::high_resolution_clock::now();


    int64_t sum = 0;
    for (size_t i = 0; i < count; ++i) 
    {
        sum += vec[0];
        vec.erase(vec.begin());
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "C++ vector:   " << duration.count() << " seconds" << std::endl;
    std::cout << "sum - " << sum << std::endl;
    std::cout << "capacity - " << vec.capacity() << std::endl;
    std::cout << "size - " << vec.size() << std::endl;
}

int main() 
{
    size_t count = 1000000000;
    
    std::cout << "Benchmarking vector PUSH_BACK (" << count << " elements):" << std::endl;
    benchmark_cpp_vector(count);
    
    std::cout << "Benchmarking vector RESIZES (" << count << " elements):" << std::endl;
    benchmark_cpp_resize(count);

    count /= 1000;

    std::cout << "Benchmarking vector INSERTS (" << count << " elements):" << std::endl;
    benchmark_cpp_insert(count);
    
    std::cout << "Benchmarking vector ERASE (" << count << " elements):" << std::endl;
    benchmark_cpp_erase(count);
}
