#include <inttypes.h>
#include <iostream>
#include <cctype>

class bigint
{
public:
    bigint() : data("0") {}

    // Do error checking here
    bigint(const int64_t signed_integer)
    {
        data = std::to_string(signed_integer);
        if (data.at(0) == '-')
        {
            data.erase(0, 1);
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

        data = string_of_digits;
        if (is_negative)
            data.erase(0, 1);

        while (*data.begin() == '0')
            data.erase(0, 1);

        if (data.empty())
            throw empty_string;

        for (uint64_t i = 0; i < data.size(); i++)
        {
            if (!isdigit(data.at(i)))
                throw invalid_string;
        }
    }

    bigint &operator+=(const bigint &other)
    {
        int64_t first_index = (int64_t)data.length() - 1;
        int64_t second_index = (int64_t)other.data.size() - 1;
        uint8_t carryover = 0;

        while (first_index >= 0 || second_index >= 0)
        {
            const uint8_t first_number = (first_index >= 0) ? char2int(data.at((size_t)first_index)) : 0;
            const bool insertion_required = (first_index >= 0) ? false : true;
            const uint8_t second_number = (second_index >= 0) ? char2int(other.data.at((size_t)second_index)) : 0;

            const uint8_t summation = first_number + second_number + carryover;
            if (summation > 9)
            {
                carryover = 1;
                if (insertion_required)
                    data.insert(data.begin(), int2char(summation - 10));
                else
                    data.replace((size_t)first_index, 1, std::to_string(summation - 10));
            }
            else
            {
                carryover = 0;
                if (insertion_required)
                    data.insert(data.begin(), int2char(summation));
                else
                    data.replace((size_t)first_index, 1, std::to_string(summation));
            }

            first_index--;
            second_index--;
        }

        if (carryover == 1)
            data.insert(data.begin(), '1');

        return *this;
    }

    bool operator==(const bigint &other) const
    {
        return data == other.data && is_negative == other.is_negative;
    }

    bool operator!=(const bigint &other) const
    {
        return !(*this == other);
    }

    bool operator<(const bigint &other) const
    {
        if (is_negative && !other.is_negative)
            return true;
        if (!is_negative && other.is_negative)
            return false;
        // if (is_negative && other.is_negative)
    }

    bool operator>(const bigint &other) const
    {
        return false;
    }

    friend std::ostream &operator<<(std::ostream &out, const bigint &b);

private:
    uint64_t char2int(const char c) { return (uint64_t)(c - '0'); }
    char int2char(const uint8_t integer) { return (char)(integer + '0'); }

    const static inline std::invalid_argument invalid_string = std::invalid_argument("Input string does not represent a signed string of digits!");
    const static inline std::invalid_argument empty_string = std::invalid_argument("Input string is empty!");
    bool is_negative = false;
    std::string data;
};

bigint operator+(bigint lhs, const bigint &rhs)
{
    lhs += rhs;
    return lhs;
}

std::ostream &operator<<(std::ostream &out, const bigint &b)
{
    const char sign = b.is_negative ? '-' : '+';
    out << sign << b.data;
    return out;
}