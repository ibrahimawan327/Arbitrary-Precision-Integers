#include "bigint.hpp"
#include <iostream>
#include <chrono>

int main()
{

    // Addition (+/+=) operator demonstration:
    std::cout << "\n\nAddition operator demonstration: \n";
    try
    {
        bigint a("289347509237452983");
        std::cout << "289347509237452983 + (-8927590837459082) = " << (a += bigint("-8927590837459082")) << '\n';
        std::cout << "3453543 + (-99999953) = " << bigint("3453543") + bigint("-99999953") << '\n';
        bigint a1(-3425);
        std::cout << "-3425 + 94038503 = " << (a1 += bigint("94038503")) << '\n';
        std::cout << "38457609823754980 + 84357982347509237459802375908 = " << bigint(38457609823754980) + bigint("84357982347509237459802375908") << '\n';
        std::cout << "-999 + (-981) = " << bigint(-999) + bigint(-981) << '\n';
        std::cout << "5 + (-7) = " << bigint(5) + bigint(-7) << '\n';
        std::cout << "-17 + 44 = " << bigint(-17) + bigint(44) << '\n';
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    // Subtraction (-/-=) operator demonstration:
    std::cout << "\n\nSubtraction operator demonstration: \n";
    try
    {
        std::cout << "-3847 - 43432 = " << bigint(-3847) - bigint("43432") << '\n';
        std::cout << "3459834 - (-49038) = " << bigint("3459834") - bigint(-49038) << '\n';
        std::cout << "-348956709348756 - (-95842376093) = " << bigint("-348956709348756") - bigint(-95842376093) << '\n';
        std::cout << "23489 - 23489 = " << bigint("23489") - bigint(23489) << '\n';
        bigint s;
        std::cout << "0 - 2435324 = " << (s -= bigint("2435324")) << '\n';
        std::cout << "234892349857230 - 238945789203 = " << bigint("234892349857230") - bigint("238945789203") << '\n';
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    // Multiplication (*/*=) operator demonstration:
}
