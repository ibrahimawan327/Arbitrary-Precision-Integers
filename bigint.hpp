#include <inttypes.h>
#include <iostream>
#include <cctype>

class bigint
{
public:
    bigint() : data("0") {}

    // Do error checking here
    bigint(const int64_t signed_integer) : data(std::to_string(signed_integer)) {}

    bigint(const std::string &string_of_digits)
    {
        if (string_of_digits.empty())
            throw empty_string;

        const char first_character = string_of_digits.at(0);
        if (first_character == '-' && string_of_digits.size() > 1)
            is_negative = true;
        else if (!isdigit(first_character))
            throw invalid_string;

        for (uint64_t i = 1; i < string_of_digits.size(); i++)
        {
            if (!isdigit(string_of_digits.at(i)))
                throw invalid_string;
        }

        data = string_of_digits;
        if (is_negative)
            data.erase(0, 1);
    }

    bigint &operator+=(const bigint &other)
    {
        bool string_bigger_than_other = false;
        if (data.size() <= other.data.size())
        {
            const uint64_t original_size = data.size();
            for (uint64_t i = 0; i < (other.data.size() - original_size); i++)
                data.insert(data.begin(), '0');
        }
        else
        {
            string_bigger_than_other = true;
        }

        uint64_t carryover = 0;
        for (uint64_t i = 0; i < data.size(); i++)
        {
            const uint64_t current_index = data.size() - i - 1;
            uint64_t second_number;
            if (string_bigger_than_other)
            {
                if ((current_index - (data.size() - other.data.size())) >= 0)
                    second_number = other.data.at(current_index - (data.size() - other.data.size()));
                else
                    second_number = 0;
            }
            else
                second_number = char2int(other.data.at(current_index));

            uint64_t summation = char2int(data.at(current_index)) + second_number + carryover;
            if (summation > 9)
            {
                carryover = 1;
                data.replace(current_index, 1, std::to_string(summation - 10));
            }
            else
            {
                carryover = 0;
                data.replace(current_index, 1, std::to_string(summation));
            }
        }

        if (carryover == 1)
            data.insert(data.begin(), '1');

        return *this;
    }

    friend std::ostream &operator<<(std::ostream &out, const bigint &b);

private:
    uint64_t char2int(const char c)
    {
        switch (c)
        {
        case '0':
            return 0;
        case '1':
            return 1;
        case '2':
            return 2;
        case '3':
            return 3;
        case '4':
            return 4;
        case '5':
            return 5;
        case '6':
            return 6;
        case '7':
            return 7;
        case '8':
            return 8;
        case '9':
            return 9;
        }
    }

    const static inline std::invalid_argument invalid_string = std::invalid_argument("Input string does not represent a signed string of digits!");
    const static inline std::invalid_argument empty_string = std::invalid_argument("Input string is empty!");
    bool is_negative = false;
    std::string data;
};

std::ostream &operator<<(std::ostream &out, const bigint &b)
{
    const char sign = b.is_negative ? '-' : '+';
    out << sign << b.data;
    return out;
}