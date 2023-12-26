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
* **Case 3 (Base Case)**: x + y or (-x) + (-y) is explained below and constitutes the bulk of the addition overload.

The algorithm for addition is straightforward. It is a character by character addition and if the result of addition exceeds 9, there is a carryover of 1 to the next iteration. A simple mathematical example is shown below:

      1438
      + 99

So, the algorithm, formatted as first_number + second_number + carryover, is as follows (carryover initialized to 0):

* First iteration: 8 + 9 + 0 = 17. Carryover is then 1 and resultant digits = "7"
* Second iteration: 3 + 9 + 1 = 13. Carryover is then 1 and resultant digits = "37"
* Third iteration: 4 + 0 + 1 = 5. Carryover is 0 and resultant digits = "537"
* Fourth iteration: 1 + 0 + 0 = 1. Carryover is 0 and resultant digits = 1537"

Examples:

* `Bigint("3453543") + Bigint("-99999953")` yields `-96546410`
* `Bigint(38457609823754980) + Bigint("84357982347509237459802375908")` yields `+84357982347547695069626130888`
* `Bigint(-999) + Bigint(-981)` yields `-1980`

## Subtraction

`Bigint &operator-=(const Bigint &other)`

The core subtraction algorithm for 2 Bigint's is applicable when both integers are positive and the numerical value of the Bigint on the left-hand side of the subtraction sign is greater than the numerical value of the Bigint on the right-hand side. In other words, when performing the subtraction x - y, the core subtraction algorithm is applicable when x and y are both positive and x > y. This is explained below, where x and y represent positive integers and -x and -y represent negative integers.

* **Case 1**: (-x) - y is equivalent to -(x + y). So, reverse the sign of x and call the addition overload, and then negate the result.
* **Case 2**: x - (-y) is equivalent to x + y. Again, call addition operator instead since it is more applicable.
* **Case 3**: (-x) - (-y) is equivalent to y - x. This is a recursive call that falls to either case 4 or case 5.
* **Case 4**: x - y is equivalent to -(y - x). This is the typical switch and negate method used when x < y. Again, this is a recursive call that falls to case 5.
* **Case 5**: x - y is explained below and constitutes the bulk of the subtraction overload

Again, this algorithm is straightforward and is a character by character subtraction with a carryover. This is illustrated in the following mathematical example:

      1000
     - 999
Again, the algorithm can be thought of as repeated comparison between (first_number - carryover) and second_number. If the former < latter, a carryover of 1 is used for the next iteration and the subtraction result is calculated as (first_number - carryover) + 10 - second_number. Otherwise, a carryover of 0 is used for the next iteration and the subtraction result is calculated as (first_number - carryover) - second_number. The first few iterations are shown below:

* First iteration: first_number = 0, second_number = 9, carryover = 0. Since 0 < 9, carryover is then 1 (for the next iteration) and resultant digits = "1".
* Second iteration: first_number = 0, second_number = 9, carryover = 1. Since -1 < 9, carryover is then 1 and resultant digits = "01".
* Third iteration: first_number = 0, second_number = 9, carryover = 1. Same case as above, resultant digits = "001".
* Fourth iteration: first_number = 1, second_number = 0, carryover = 1. Resultant digits are then "0001".

Stripping away the leading 0's yields the result of +1.

Examples:

* `Bigint(-3847) - Bigint("43432")` yields `-47279`
* `Bigint("3459834") - Bigint(-49038)` yields `+3508872`
* `Bigint("234892349857230") - Bigint("238945789203")` yields `+234653404068027`

## Multiplication

`Bigint &operator*=(const Bigint &other))`

The multiplication algorithm involves a nested for-loop structure that iterates backwards through the digits of the two Bigint objects to be multiplied. A simple example is shown below:

      567
    x 378

Given the multiplication above, the result is computed as (8 * 567) + 0 padded 0's + (7 * 567) + 1 padded 0 + (3 * 567) + 2 padded 0's. Here, the expression "+ x padded 0's" means that x 0's are appended to the end of the multiplication result. In practice, this is identical to normal multiplication and the code's inline comments assist in this explanation.  

Examples:

* `Bigint("43857902378459234") * Bigint("38942579023745")` yields `+1707939829188842510301000511330`
* `Bigint(-4353) * Bigint(345534)` yields `-1504109502`
* `Bigint("3495873") * Bigint()` yields `0`

## Negation
`Bigint operator-(Bigint b)`

The unary negation overloaded operator for the Bigint class simply takes a Bigint object by value, reverses the sign, and returns the object. It is important to note that since the original Bigint object is passed into this function by value, the original object remains unmodified.

Examples:

* `-Bigint("3453245")` yields `-3453245`
* `-Bigint("-943583")` yields `+943583`

## Comparison

`bool operator==(const Bigint &other) const`

`bool operator!=(const Bigint &other) const`

`bool operator<(const Bigint &other) const`

`bool operator<=(const Bigint &other) const`

`bool operator>(const Bigint &other) const`

`bool operator>=(const Bigint &other) const`

## Assignment

`Bigint &operator=(const Bigint &other))`

The assignment operator is used to copy the data of another Bigint object to the current Bigint object. Since the Bigint class has only 2 non-static data members: a std::string that stores the digits and a boolean variable is_negative that indicates the sign of the Bigint, the implementation is simple and involves the following 2 sub-assignments:

* this->digits = other.digits
* this->is_negative = other.is_negative


## Insertion

`std::ostream &operator<<(std::ostream &out, const Bigint &b)`

