#include <inttypes.h>
#include <vector>
#include <string>
#include <cmath>
#include <stdexcept>

class bigint
{
public:
    bigint() {}

    bigint(const int64_t) {}

    bigint(std::string &string_of_digits)
    {
        if (string_of_digits.size() == 0)
            throw empty_string;

        const char first_bit = string_of_digits.at(0);
        if (first_bit == '1')
            is_negative = true;
        else if (first_bit == '0')
            is_negative = false;
        else
            throw invalid_string;

        const uint64_t number_of_blocks = (uint64_t)ceil((double)string_of_digits.length() / (double)size_of_blocks);
        data.reserve(number_of_blocks);

        uint64_t result = 0, exponent = 0;
        for (size_t idx = string_of_digits.size() - 1; idx > 0; idx--)
        {
            const char current_char = string_of_digits.at(idx);
            if (current_char != '1' && current_char != '0')
                throw invalid_string;

            if (current_char == '1')
                result += pow(2, (double)exponent);
            if (exponent == (size_of_blocks - 1) || idx == 1)
            {
                data.insert(data.begin(), result);
                result = 0;
                exponent = 0;
                continue;
            }

            exponent++;
        }
    }

    std::vector<uint64_t> getter()
    {
        return data;
    }

private:
    const static inline uint64_t size_of_blocks = 64;
    const static inline std::invalid_argument invalid_string = std::invalid_argument("Input string does not contain a binary representation!");
    const static inline std::invalid_argument empty_string = std::invalid_argument("Input string is empty!");
    std::vector<uint64_t> data;
    bool is_negative;
};
