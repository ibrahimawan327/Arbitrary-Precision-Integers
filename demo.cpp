/**
 * @file demo.cpp
 * @author Ibrahim Awan (ibrahimawan327@gmail.com)
 * @brief Demonstration program to showcase bigint class functionality
 * @version 0.1
 * @date 2023-12-24
 *
 * @copyright Copyright (c) 2023 Ibrahim Awan
 */

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
    std::cout << "\n\nMultiplication operator demonstration: \n";
    try
    {
        std::cout << "155 * 200 = " << bigint("155") * bigint("200") << '\n';
        std::cout << "43857902378459234 * 38942579023745 = " << bigint("43857902378459234") * bigint("38942579023745") << '\n';
        std::cout << "3495873 * 0 = " << bigint("3495873") * bigint() << '\n';
        std::cout << "-4353 * 345534 = " << bigint(-4353) * bigint(345534) << '\n';
        std::cout << "-178 * (-200) = " << bigint("-178") * bigint("-200") << '\n';
        std::cout << "0 * 87 = " << bigint() * bigint(87) << '\n';
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    // Negation (-) operator demonstration:
    std::cout << "\n\nNegation operator demonstration: \n";
    try
    {
        std::cout << "Reversing the sign of +3453245 = " << -bigint("3453245") << '\n';
        std::cout << "Reversing the sign of -943583 = " << -bigint("-943583") << '\n';
        std::cout << "Reversing the sign of -347859790823745 = " << -bigint(-347859790823745) << '\n';
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    // Comparison (==, !=, <, >, <=, and >=) operators
    std::cout << "\n\nComparision operator demonstrations: \n";
    try
    {
        /* code */
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}
