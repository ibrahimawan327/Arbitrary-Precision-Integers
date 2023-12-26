/**
 * @file demo.cpp
 * @author Ibrahim Awan (ibrahimawan327@gmail.com)
 * @brief Demonstration program to showcase Bigint class functionality
 * @version 0.1
 * @date 2023-12-24
 *
 * @copyright Copyright (c) 2023 Ibrahim Awan
 */

#include "bigint.hpp"
#include <iostream>
#include <chrono>
#include <fstream>

int main()
{
    // Constructor demonstration:
    std::cout << "\n\nConstructor demonstration: \n";
    try
    {
        std::cout << "Input string     -00002345902384     --> " << Bigint("    -00002345902384    ") << '\n';
        std::cout << "Input string 58923745908723094572309458723450923875980 --> " << Bigint("58923745908723094572309458723450923875980") << '\n';
        std::cout << "Input 64-bit integer -234232 --> " << Bigint(-234232) << '\n';
        std::cout << "Input 64-bit integer 94097502234 --> " << Bigint(94097502234) << '\n';
        std::cout << "Default constructor --> " << Bigint() << '\n';
        std::cout << "Input string: 348597vetrg --> " << Bigint("348597vetrg") << '\n';
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    // Addition (+/+=) operator demonstration:
    std::cout << "\n\nAddition operator demonstration: \n";
    try
    {
        Bigint a("289347509237452983");
        std::cout << "289347509237452983 + (-8927590837459082) = " << (a += Bigint("-8927590837459082")) << '\n';
        std::cout << "3453543 + (-99999953) = " << Bigint("3453543") + Bigint("-99999953") << '\n';
        Bigint a1(-3425);
        std::cout << "-3425 + 94038503 = " << (a1 += Bigint("94038503")) << '\n';
        std::cout << "38457609823754980 + 84357982347509237459802375908 = " << Bigint(38457609823754980) + Bigint("84357982347509237459802375908") << '\n';
        std::cout << "-999 + (-981) = " << Bigint(-999) + Bigint(-981) << '\n';
        std::cout << "5 + (-7) = " << Bigint(5) + Bigint(-7) << '\n';
        std::cout << "-17 + 44 = " << Bigint(-17) + Bigint(44) << '\n';
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    // Subtraction (-/-=) operator demonstration:
    std::cout << "\n\nSubtraction operator demonstration: \n";
    try
    {
        std::cout << "-3847 - 43432 = " << Bigint(-3847) - Bigint("43432") << '\n';
        std::cout << "3459834 - (-49038) = " << Bigint("3459834") - Bigint(-49038) << '\n';
        std::cout << "-348956709348756 - (-95842376093) = " << Bigint("-348956709348756") - Bigint(-95842376093) << '\n';
        std::cout << "23489 - 23489 = " << Bigint("23489") - Bigint(23489) << '\n';
        Bigint s;
        std::cout << "0 - 2435324 = " << (s -= Bigint("2435324")) << '\n';
        std::cout << "234892349857230 - 238945789203 = " << Bigint("234892349857230") - Bigint("238945789203") << '\n';
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    // Multiplication (*/*=) operator demonstration:
    std::cout << "\n\nMultiplication operator demonstration: \n";
    try
    {
        std::cout << "155 * 200 = " << Bigint("155") * Bigint("200") << '\n';
        std::cout << "43857902378459234 * 38942579023745 = " << Bigint("43857902378459234") * Bigint("38942579023745") << '\n';
        std::cout << "3495873 * 0 = " << Bigint("3495873") * Bigint() << '\n';
        std::cout << "-4353 * 345534 = " << Bigint(-4353) * Bigint(345534) << '\n';
        std::cout << "-178 * (-200) = " << Bigint("-178") * Bigint("-200") << '\n';
        std::cout << "0 * 87 = " << Bigint() * Bigint(87) << '\n';
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    // Negation (-) operator demonstration:
    std::cout << "\n\nNegation operator demonstration: \n";
    try
    {
        std::cout << "Reversing the sign of +3453245 = " << -Bigint("3453245") << '\n';
        std::cout << "Reversing the sign of -943583 = " << -Bigint("-943583") << '\n';
        std::cout << "Reversing the sign of -347859790823745 = " << -Bigint(-347859790823745) << '\n';
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    // Comparison (==, !=, <, >, <=, and >=) operators demonstration:
    std::cout << "\n\nComparision operator demonstrations: \n";
    try
    {
        std::cout << "348597 > 438975 --> " << (Bigint(348597) > Bigint(438975)) << '\n';
        std::cout << "2001 <= 2001 --> " << (Bigint(2001) <= Bigint(2001)) << '\n';
        std::cout << "2001 <= -17 --> " << (Bigint(2001) <= Bigint(-17)) << '\n';
        std::cout << "2349 == 2349 --> " << (Bigint(2349) == Bigint("2349")) << '\n';
        std::cout << "-1998 != 1998 --> " << (Bigint(-1998) != Bigint(1998)) << '\n';
        std::cout << "-1998 != -1998 --> " << (Bigint(-1998) != Bigint(-1998)) << '\n';
        std::cout << "438597 >= -3459083345 --> " << (Bigint("438597") >= Bigint("-3459083345")) << '\n';
        std::cout << "-43 >= 0 --> " << (Bigint("-43") >= Bigint()) << '\n';
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    // Assignment (=) operator demonstration:
    std::cout << "\n\nAssignment operator demonstrations: \n";
    try
    {
        Bigint a("348795698432567");
        Bigint b;
        std::cout << "a is: " << a << "\n";
        std::cout << "b is: " << b << "\n\n";

        b = a;
        std::cout << "a is: " << a << '\n';
        std::cout << "b is: " << b << "\n\n";

        Bigint c(-564365);
        b = c;
        std::cout << "a is: " << a << '\n';
        std::cout << "b is: " << b << '\n';
        std::cout << "c is: " << c << "\n\n";
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}
