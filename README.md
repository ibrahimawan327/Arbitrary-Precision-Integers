# Arbitrary-Precision Integers in C++

Unlike the Python programming language, C++ does not provide built-in support for arbitrary-precision signed integers. Signed 64-bit integers in C++ can only go up to 9,223,372,036,854,775,807 and the class Bigint provided in the header file bigint.hpp extends this range. The class Bigint allows for addition, subtraction, multiplication, comparison, and other operations on signed integers of unlimited range (limited only by computer memory).

## Constructors
1. `Bigint()`. The default constructor initializes a Bigint object with a value of 0. 
2. `Bigint(const int64_t signed_integer)`. This constructor accepts a signed 64-bit integer as input and converts it into a Bigint object.
3. `Bigint(const std::string &string_of_digits)`. This constructor accepts a string of digits, e.g. "34895720329845", and converts this string of digits into a Bigint object.

The third constructor performs simple error-checking to verify that the input string is indeed a valid string of digits. For instance, if `Bigint b("3245dbg");` is executed inside a try-catch block, the invalid argument exception `Input string does not represent a signed string of digits!` will be thrown by the constructor. The constructor will also strip away any accidental spaces and will interpret the sign of the input string of digits based on whether the first valid character is a `-`. For example, `Bigint c("-34534590238");` is perfectly valid code whereas `Bigint c("-");` will throw an exception since there are no digits after the negative sign.

## Addition 
`Bigint &operator+=(const Bigint &other)`

The core addition algorithm for 2 Bigint's is applicable when both integers are either positive or negative. This is explained below, where x and y represent positive integers and -x and -y represent negative integers.

* **Case 1**: x + (-y) is equivalent to x - y. In this case, it is easiest to reverse the sign of y and call the overloaded subtraction operator.
* **Case 2**: (-x) + y is equivalent to y - x. Again, the overloaded subtraction operator is applicable here, after reversing the sign of x.
* **Case 3**: x + y or (-x) + (-y) is explained below and constitutes the bulk of the addition overload.

The algorithm for addition is straightforward. It is a character by character addition and if the result of addition exceeds 9, there is a carryover of 1 to the next iteration. A simple mathematical example is shown below:

      1438
      + 99

So, the algorithm, formatted as first_number + second_number + carryover, is as follows (carryover initialized to 0):
* First iteration: 8 + 9 + 0 = 17. Carryover is then 1 and resultant digits = "7"
* Second iteration: 3 + 9 + 1 = 13. Carryover is then 1 and resultant digits = "37"
* Third iteration: 4 + 0 + 1 = 5. Carryover is 0 and resultant digits = "537"
* Fourth iteration: 1 + 0 + 0 = 1. Carryover is 0 and resultant digits = 1537"



## Subtraction
`Bigint &operator-=(const Bigint &other)`



## Multiplication

## Comparison