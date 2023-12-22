#include "bigint.hpp"
#include <iostream>
#include <chrono>

int main()
{

    // Addition (+/+=) operator demonstration:
    try
    {
        std::cout << bigint("12342233720368547758071234223372036854775807123422337203685477580712342233720368547758071234223372036854775807") * bigint("12342233720368547758071234223372036854775807123422337203685477580712342233720368547758071234223372036854775807") << "\n ";
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}
