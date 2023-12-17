#include "bigint.hpp"
#include <iostream>

int main()
{

    try
    {
        bigint b("-00000000000");
        std::cout << b << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}
