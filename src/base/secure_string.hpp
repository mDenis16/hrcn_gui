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
            str[i] = a[i];
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
