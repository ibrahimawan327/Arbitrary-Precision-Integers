#include "bigint.hpp"
#include <iostream>
#include <chrono>

int main()
{

    // Addition (+/+=) operator demo:
    try
    {
        std::cout << bigint("548673409567390485673908457690347569803754609734095867") * bigint("89547689037456903756908387456093487569034758609345786093487563") << "\n ";
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}
