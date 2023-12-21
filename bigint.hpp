/**
 * @file bigint.hpp
 * @author Ibrahim Awan (ibrahimawan327@gmail.com)
 * @brief Header file with implementation of signed integers longer than 64 bits
 * @version 0.1
 * @date 2023-12-21
 *
 * @copyright Copyright (c) 2023 Ibrahim Awan
 */

#include <inttypes.h>
#include <iostream>
#include <cctype>

class bigint
{
public:
    bigint() : digits("0") {}

    bigint(const int64_t signed_integer)
    {
        digits = std::to_string(signed_integer);
        if (digits.at(0) == '-')
        {
            digits.erase(0, 1);
            is_negative = true;
        }
    }

    bigint(const std::string &string_of_digits)
    {
        if (string_of_digits.empty())
            throw empty_string;

        const char first_character = string_of_digits.at(0);
        if (first_character == '-' && string_of_digits.size() > 1)
            is_negative = true;
        else if (!isdigit(first_character))
            throw invalid_string;

        digits = string_of_digits;
        if (is_negative)
            digits.erase(0, 1);

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

    bigint &operator+=(const bigint &other)
    {
        if (!is_negative && other.is_negative)
        {
            *this -= bigint(other.digits);
            return *this;
        }

        if (is_negative && !other.is_negative)
        {
            *this = other - bigint(digits);
            return *this;
        }

        int64_t first_index = (int64_t)digits.size() - 1;
        int64_t second_index = (int64_t)other.digits.size() - 1;
        uint8_t carryover = 0;

        while (first_index >= 0 || second_index >= 0)
        {
            const uint8_t first_number = (first_index >= 0) ? char2int(digits.at((size_t)first_index)) : 0;
            const bool insertion_required = (first_index >= 0) ? false : true;
            const uint8_t second_number = (second_index >= 0) ? char2int(other.digits.at((size_t)second_index)) : 0;

            const uint8_t summation = first_number + second_number + carryover;
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

        if (carryover == 1)
            digits.insert(digits.begin(), '1');

        return *this;
    }

    bigint &operator-=(const bigint &other)
    {
        if (is_negative && !other.is_negative)
        {
            is_negative = false;
            *this += other;
            is_negative = true;
            return *this;
        }

        if (!is_negative && other.is_negative)
        {
            *this += bigint(other.digits);
            return *this;
        }

        if (is_negative && other.is_negative)
        {
            *this = bigint(other.digits) - bigint(digits);
            return *this;
        }

        if (*this < other)
        {
            *this = -(other - *this);
            return *this;
        }

        int64_t second_index = (int64_t)other.digits.size() - 1;
        uint8_t carryover = 0;

        for (int64_t first_index = (int64_t)digits.size() - 1; first_index >= 0; first_index--)
        {
            const int8_t first_number = char2int(digits.at((size_t)first_index)) - carryover;
            const uint8_t second_number = (second_index >= 0) ? char2int(other.digits.at((size_t)second_index)) : 0;

            if (first_number < second_number)
            {
                digits.replace((size_t)first_index, 1, 1, int2char((uint8_t)(first_number + 10 - second_number)));
                carryover = 1;
            }
            else
            {
                digits.replace((size_t)first_index, 1, 1, int2char((uint8_t)(first_number - second_number)));
                carryover = 0;
            }

            second_index--;
        }

        while (*digits.begin() == '0')
            digits.erase(0, 1);

        return *this;
    }

    bigint &operator*=(const bigint &other)
    {
        bigint tmp = 1;
        bigint original_value = *this;
        while (tmp < other)
        {
            *this += original_value;
            tmp += bigint(1);
        }

        return *this;
    }

    bigint &operator-()
    {
        is_negative = !is_negative;
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
     * @return bigint& Reference to the current bigint object, after reassignment
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
    friend std::ostream &operator<<(std::ostream &out, const bigint &b);

private:
    uint8_t char2int(const char c) const { return (uint8_t)(c - '0'); }
    char int2char(const uint8_t integer) const { return (char)(integer + '0'); }

    const static inline std::invalid_argument invalid_string = std::invalid_argument("Input string does not represent a signed string of digits!");
    const static inline std::invalid_argument empty_string = std::invalid_argument("Input string is empty!");
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

std::ostream &operator<<(std::ostream &out, const bigint &b)
{
    if (b.digits.empty())
        return (out << 0);
    const char sign = b.is_negative ? '-' : '+';
    out << sign << b.digits;
    return out;
}