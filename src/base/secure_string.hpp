#pragma once

#include <iostream>
#include <array>

template <size_t N>
  struct secure_string
{
    constexpr static uint32_t default_offset_basis = 0x811C9DC5;
    constexpr static uint32_t prime = 0x01000193;

    std::array<char, N> str{};

    constexpr secure_string(const char *a) noexcept
    {
        for (size_t i = 0u; i < N; ++i)
        {
            str[i] = a[i] ^ 0x21;
        }
    }

    constexpr size_t get_skip_count() const
    {
        size_t skips = 0;
        bool skip_next_char = false;

        for (size_t i = 0u; i < N; ++i)
        {
            // not delimiter
            if (str[i] != ' ')
            {
                // no need to do next checks if it's a skip wildcard
                if (str[i] == '?')
                    continue;

                if (!skip_next_char)
                {
                    // hit char pair
                    if (i + 1 < N && str[i + 1] != ' ')
                        skip_next_char = true;
                }
                // do only 1 skip for char pair
                else
                {
                    ++skips;
                    skip_next_char = false;
                }

                continue;
            }

            ++skips;
        }

        return skips;
    }

    constexpr char at(int idx) const
    {
        return str[idx];
    }

    constexpr auto size() const
    {
        return N;
    }
    constexpr size_t hash()
    {
        return 0;
    }
};

template <size_t N>
secure_string(const char (&)[N]) -> secure_string<N - 1>;


constexpr uint64_t hash_fnv1a(std::string_view str, uint64_t hash = 14695981039346656037ULL) {
    for (char c : str) {
        hash ^= static_cast<uint64_t>(c);
        hash *= 1099511628211ULL;
    }
    return hash;
}
constexpr std::size_t constexpr_strlen(const char* s)
{
    return std::char_traits<char>::length(s);
    // or
    return std::string::traits_type::length(s);
}


struct secure_data {
    char buff[128];
    size_t key;
    size_t len;
};
inline constexpr std::size_t strlen_c(const char* str) {
    std::size_t length = 0;
    while (str[length] != '\0') {
        ++length;
    }
    return length;
}

constexpr std::array<uint64_t, 16> stringToUint64Array(const char* str) {
    std::size_t length = strlen_c(str);
    std::array<uint64_t, 16> result = {0}; // 16 * 8 = 128 characters maximum
    for (std::size_t i = 0; i < length; ++i) {
        result[i / 8] |= (static_cast<uint64_t>(str[i]) << (8 * (i % 8)));
    }
    return result;
}

 inline void uint64ArrayToString(const std::array<uint64_t, 16>& arr, char* output) {
    for (std::size_t i = 0; i < 16; ++i) {
        for (std::size_t j = 0; j < 8; ++j) {
            char c = (arr[i] >> (8 * j)) & 0xFF;
            if (c != '\0') {
                *output++ = c;
            } else {
                *output = '\0';
                return;
            }
        }
    }
    *output = '\0';
}
class runtime_secure_string {
public:

    std::array<uint64_t, 16> _data;
    runtime_secure_string(std::function<std::array<uint64_t, 16>()> _callback) {

      //  memcpy(&str_data[0], &data.buff[0], 128);
        _data = _callback();
    }
    runtime_secure_string( std::array<uint64_t, 16> data) {
        _data = data;
    }

    inline void access_string(char* output) {
        uint64ArrayToString(_data, output);
    }

};

#define create_secure_string(str)  runtime_secure_string([]() { constexpr auto s = stringToUint64Array(str); return s;  })

inline runtime_secure_string create_secure_string_runtime(const char* str) {
    return runtime_secure_string(stringToUint64Array(str));
}

