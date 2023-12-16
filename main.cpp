#include "bigint.hpp"
#include <iostream>

int main()
{
    try
    {
        bigint b("99999");
        bigint c("99");
        b += c;
        std::cout << b << "\n";
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}
