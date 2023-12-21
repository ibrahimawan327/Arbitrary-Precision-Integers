#include "bigint.hpp"
#include <iostream>
#include <chrono>

int main()
{

    try
    {
        std::cout << bigint("1111111") - bigint("00000") << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}
