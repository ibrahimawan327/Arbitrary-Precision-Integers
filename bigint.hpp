/**
 * @file bigint.hpp
 * @author Ibrahim Awan (ibrahimawan327@gmail.com)
 * @brief Header file with implementation details of bigint class
 * @version 0.1
 * @date 2023-12-21
 *
 * @copyright Copyright (c) 2023 Ibrahim Awan
 */

#include <inttypes.h>
#include <iostream>
#include <cctype>

/**
 * @brief The bigint class is used to represent signed arbitrary precision integers.
 * Currently, the class supports addition (+), subtraction (-), multiplication (*), negation (-), comparison (==, !=, <, <=, >, >=),
 * assignment (=), and stream insertion (<<) operators.
 */
class bigint
{
public:
    /**
     * @brief Construct a new bigint object with value 0 using default constructor
     *
     */
    bigint() : digits("0") {}

    /**
     * @brief Construct a new bigint object by converting the signed 64-bit integer into a bigint representation
     *
     * @param signed_integer The signed 64-bit integer whose value is to be interpreted and converted to a bigint representation
     */
    bigint(const int64_t signed_integer)
    {
        digits = std::to_string(signed_integer);
        if (digits.at(0) == '-')
        {
            is_negative = true;
            digits.erase(0, 1);
        }
    }

    /**
     * @brief Construct a new bigint object by parsing the input string of digits and converting to a bigint representation
     *
     * @param string_of_digits The input string of digits that are to be converted to a bigint representation
     */
    bigint(const std::string &string_of_digits)
    {
        digits = string_of_digits;
        for (int64_t i = 0; i < (int64_t)digits.size(); i++)
        {
            if (digits.at((size_t)i) == ' ')
            {
                digits.erase(digits.begin() + i);
                --i;
            }
        }

        if (digits.empty())
            throw empty_string;

        const char first_character = digits.at(0);
        if (first_character == '-' && digits.size() > 1)
        {
            is_negative = true;
            digits.erase(0, 1);
        }
        else if (!isdigit(first_character))
            throw invalid_string;

        while (*digits.begin() == '0')
            digits.erase(0, 1);

        if (digits.empty())
            throw empty_string;

        for (uint64_t i = 0; i < digits.size(); i++)
        {
            if (!isdigit(digits.at(i)))
                throw invalid_string;
        }
    }

    bigint(const bigint &other) : is_negative(other.is_negative), digits(other.digits) {}

    /**
     * @brief Addition (+=) operator that accepts a bigint object and adds its value to the current bigint object
     *
     * @param other The bigint object whose value is to be added to the current bigint object
     * @return bigint&. Reference to the current bigint object, after adding the value of other
     */
    bigint &operator+=(const bigint &other)
    {
        // Assume x and y are +ve integers. Then, -x and -y are -ve integers
        // Case 1: x + (-y) is equivalent to x - y. So, reverse the sign of y and call the subtraction (-=) operator.
        if (!is_negative && other.is_negative)
        {
            *this -= (-other);
            return *this;
        }

        // Case 2: (-x) + y is equivalent to y - x.
        if (is_negative && !other.is_negative)
        {
            *this = other - (-(*this));
            return *this;
        }

        // Case 3 (Base case): If x and y are either both positive or negative integers, perform addition character by character
        // Indices below (first_index and second_index) are signed integers because we need to know when they become negative for the while-loop to work appropriately
        int64_t first_index = (int64_t)digits.size() - 1;
        int64_t second_index = (int64_t)other.digits.size() - 1;
        int64_t carryover = 0;

        // The following is the typical algorithm for addition
        while (first_index >= 0 || second_index >= 0)
        {
            // Taking the example (9456 + 743) shown below: In the first iteration, first_number = 6, second_number = 3, carryover = 0, summation = 9
            // In the second iteration, first_number = 5, second_number = 4, carryover = 0, summation = 9
            // In the third iteration, first_number = 4, second_number = 7, carryover = 0, summation = 11
            // In the fourth iteration, first_number = 9, second_number = 0, carryover = 1, summation = 10
            const int64_t first_number = (first_index >= 0) ? char2int(digits.at((size_t)first_index)) : 0;
            // If the first_index still maps to a valid number in the current bigint object, first_number gets replaced by the result of the digit-digit addition.
            // Otherwise, an insertion is required
            const bool insertion_required = (first_index >= 0) ? false : true;
            const int64_t second_number = (second_index >= 0) ? char2int(other.digits.at((size_t)second_index)) : 0;
            const int64_t summation = first_number + second_number + carryover;

            // Addition requires a carryover of 1 when the summation exceeds 9
            if (summation > 9)
            {
                carryover = 1;
                if (insertion_required)
                    digits.insert(digits.begin(), int2char(summation - 10));
                else
                    digits.replace((size_t)first_index, 1, 1, int2char(summation - 10));
            }
            else
            {
                carryover = 0;
                if (insertion_required)
                    digits.insert(digits.begin(), int2char(summation));
                else
                    digits.replace((size_t)first_index, 1, 1, int2char(summation));
            }

            first_index--;
            second_index--;
        }

        // If carryover is still 1 after the above algorithm, a final '1' needs to be added
        // For example, 999 + 999 would compute to 998 with a carryover of 1. Due to this, add a '1' as the final step
        if (carryover == 1)
            digits.insert(digits.begin(), '1');

        return *this;
    }

    /**
     * @brief Subtraction (-=) operator that accepts a bigint object and subtracts its value from the current bigint object
     *
     * @param other The bigint object whose value is to be subtracted from the current bigint object
     * @return bigint&. Reference to the current bigint object, after subtraction
     */
    bigint &operator-=(const bigint &other)
    {
        // Assume x and y are +ve integers. Then, -x and -y are -ve integers
        // Case 1: (-x) - y is equivalent to -(x + y).
        if (is_negative && !other.is_negative)
        {
            *this = -(-(*this) + other);
            return *this;
        }

        // Case 2: x - (-y) is equivalent to x + y.
        if (!is_negative && other.is_negative)
        {
            *this += (-other);
            return *this;
        }

        // Case 3:: -x - (-y) is equivalent to y - x.
        if (is_negative && other.is_negative)
        {
            *this = ((-other) - (-(*this)));
            return *this;
        }

        // Cases 4 and 5 occur when x and y are both positive integers.
        // Case 4: x - y is equivalent to -(y - x) and is easier to compute programmatically when x < y.
        if (*this < other)
        {
            *this = -(other - *this);
            return *this;
        }

        // Case 5 (Base case): Computes x - y when x and y are both positive and x >= y.
        // Again, second_index is int64_t rather than uint64_t due to the (second_index >= 0) check below
        int64_t second_index = (int64_t)other.digits.size() - 1;
        int64_t carryover = 0;

        // The following is the typical algorithm for subtraction
        for (std::string::reverse_iterator rit = digits.rbegin(); rit != digits.rend(); rit++)
        {
            const int64_t first_number = char2int(*rit) - carryover;
            const int64_t second_number = (second_index >= 0) ? char2int(other.digits.at((size_t)second_index)) : 0;

            if (first_number < second_number)
            {
                carryover = 1;
                *rit = int2char(first_number + 10 - second_number);
            }
            else
            {
                carryover = 0;
                *rit = int2char(first_number - second_number);
            }

            second_index--;
        }

        // Remove 0's from the beginning that arise from subtracting integers that are close together in magnitude
        // For example, 9999 - 9998 = 0001 = +1
        while (digits.size() > 1 && digits.front() == '0')
            digits.erase(0, 1);

        return *this;
    }

    /**
     * @brief Multiplication (*=) operator that accepts a bigint object and multiplies its value with the current bigint object
     *
     * @param other The bigint object whose value is to be multiplied with the current bigint object
     * @return bigint&. Reference to the current bigint object, after multiplication
     */
    bigint &operator*=(const bigint &other)
    {
        bigint b;
        uint64_t padded_zeros = 0;
        for (std::string::const_reverse_iterator outside_rit = other.digits.rbegin(); outside_rit != other.digits.rend(); outside_rit++)
        {
            const int64_t first_number = char2int(*outside_rit);
            if (first_number == 0)
            {
                padded_zeros++;
                continue;
            }
            std::string s;
            int64_t carryover = 0;
            for (int64_t second_index = (int64_t)digits.size() - 1; second_index >= 0; second_index--)
            {
                const int64_t second_number = char2int(digits.at((size_t)second_index));
                const int64_t result = first_number * second_number + carryover;

                if (second_index == 0)
                {
                    s.insert(0, std::to_string(result));
                }
                else if (result > 9)
                {
                    s.insert(s.begin(), int2char(result % 10));
                    carryover = (result / 10);
                }
                else
                {
                    s.insert(s.begin(), int2char(result));
                    carryover = 0;
                }
            }

            for (uint64_t i = 0; i < padded_zeros; i++)
                s.push_back('0');

            padded_zeros++;
            b += bigint(s);
        }

        if ((is_negative && !other.is_negative) || (!is_negative && other.is_negative))
            b.is_negative = true;

        *this = b;
        return *this;
    }

    /**
     * @brief Comparison (==) operator used to determine if the current object and other are equal to each other
     *
     * @param other The bigint object to be compared to the current object
     * @return Boolean. true if the two bigint objects are equal and false otherwise
     */
    bool operator==(const bigint &other) const
    {
        return (digits == other.digits && is_negative == other.is_negative);
    }

    /**
     * @brief Comparison (!=) operator used to determine if the current object and other are NOT equal to each other
     *
     * @param other The bigint object to be compared to the current object
     * @return Boolean. true if the two bigint objects are unequal and false otherwise
     */
    bool operator!=(const bigint &other) const
    {
        return !(*this == other);
    }

    /**
     * @brief Comparison (<) operator used to determine if the current object is strictly less than other
     *
     * @param other The bigint object to be compared to the current object
     * @return Boolean. true if the current object (lhs of operator) is strictly less than other (rhs of operator)
     */
    bool operator<(const bigint &other) const
    {
        // Assume x and y are +ve integers. Then, -x and -y are -ve integers
        // Case 1: -x < y. Returns true since -x is a negative number and y is not
        if (is_negative && !other.is_negative)
            return true;
        // Case 2: x < -y. Returns false since -y is a negative number and x is not
        if (!is_negative && other.is_negative)
            return false;
        // Case 3: -x < -y. Both numbers are negative - need to investigate further
        if (is_negative && other.is_negative)
        {
            // If sizes are different, the larger size bigint is the smaller number (e.g. -40000 < -40)
            if (digits.size() != other.digits.size())
                return digits.size() > other.digits.size();

            // Otherwise, loop through the string of digits from most significant digit to least significant digit
            // Whichever bigint object has a larger digit is the smaller number (e.g. -5345 < -5335. In the 3rd iteration of the loop, 4 > 3)
            for (uint64_t i = 0; i < digits.size(); i++)
            {
                if (digits.at(i) != other.digits.at(i))
                    return char2int(digits.at(i)) > char2int(other.digits.at(i));
            }

            // If both objects have the same size and identical digits, they are equal and neither object is smaller than the other
            return false;
        }

        // Case 4: x < y. Both numbers are positive - need to investigate further
        // If sizes are different, the larger size bigint is the larger number (e.g. 40 < 40000)
        if (digits.size() != other.digits.size())
            return digits.size() < other.digits.size();
        // Otherwise, loop through the string of digits from most significant digit to least significant digit
        // Whichever bigint object has a larger digit is the larger number (e.g. 4319 > 4309. In the 3rd iteration of the loop, 1 > 0)
        for (uint64_t i = 0; i < digits.size(); i++)
        {
            if (digits.at(i) != other.digits.at(i))
                return char2int(digits.at(i)) < char2int(other.digits.at(i));
        }

        // If both objects have the same size and identical digits, they are equal and neither object is smaller than the other
        return false;
    }

    /**
     * @brief Comparison (<=) operator used to determine if the current object is less than or equal to other
     *
     * @param other The bigint object to be compared to the current object
     * @return Boolean. true if the current object (lhs of operator) is less than or equal to other (rhs of operator)
     */
    bool operator<=(const bigint &other) const
    {
        return ((*this == other) || (*this < other));
    }

    /**
     * @brief Comparison (>) operator used to determine if the current object is strictly greater than other
     *
     * @param other The bigint object to be compared to the current object
     * @return Boolean. true if the current object (lhs of operator) is strictly greater than other (rhs of operator)
     */
    bool operator>(const bigint &other) const
    {
        return !(*this <= other);
    }

    /**
     * @brief Comparison (>=) operator used to determine if the current object is greater than or equal to other
     *
     * @param other The bigint object to be compared to the current object
     * @return Boolean. true if the current object (lhs of operator) is greater than or equal to other (rhs of operator)
     */
    bool operator>=(const bigint &other) const
    {
        return ((*this == other) || (*this > other));
    }

    /**
     * @brief Assignment (=) operator used to reassign the current object's data to the values of another bigint object
     *
     * @param other The bigint object whose data is to be assigned to the current object
     * @return bigint&. Reference to the current bigint object, after reassignment
     */
    bigint &operator=(const bigint &other)
    {
        digits = other.digits;
        is_negative = other.is_negative;
        return *this;
    }

    friend bigint operator+(bigint lhs, const bigint &rhs);
    friend bigint operator-(bigint lhs, const bigint &rhs);
    friend bigint operator*(bigint lhs, const bigint &rhs);
    friend bigint operator-(bigint b);
    friend std::ostream &operator<<(std::ostream &out, const bigint &b);

private:
    int64_t char2int(const char c) const { return (int64_t)(c - '0'); }
    char int2char(const int64_t integer) const { return (char)(integer + '0'); }

    const static inline std::invalid_argument invalid_string = std::invalid_argument("Input string does not represent a signed string of digits!");
    const static inline std::invalid_argument empty_string = std::invalid_argument("Input string is empty! To instantiate a bigint with value 0, use default constructor or write bigint(0).");
    bool is_negative = false;
    std::string digits;
};

bigint operator+(bigint lhs, const bigint &rhs)
{
    lhs += rhs;
    return lhs;
}

bigint operator-(bigint lhs, const bigint &rhs)
{
    lhs -= rhs;
    return lhs;
}

bigint operator*(bigint lhs, const bigint &rhs)
{
    lhs *= rhs;
    return lhs;
}

bigint operator-(bigint b)
{
    b.is_negative = !b.is_negative;
    return b;
}

std::ostream &operator<<(std::ostream &out, const bigint &b)
{
    if (b.digits == "0")
        return (out << b.digits);
    const char sign = b.is_negative ? '-' : '+';
    out << sign << b.digits;
    return out;
}