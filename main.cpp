#include "bigint.hpp"
#include <iostream>
#include <chrono>

int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    try
    {
        bigint b("500");
        bigint c("500");
        std::cout << (b * c) << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = end - start;

    std::cout << "Duration is: " << duration.count() << std::endl;
}
