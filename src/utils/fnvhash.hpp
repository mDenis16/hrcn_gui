#pragma once
#include <string>



template <size_t N>
   struct str_to_hash
{
    constexpr static uint32_t default_offset_basis = 0x811C9DC5;
    constexpr static uint32_t prime = 0x01000193;

    std::array<char, N> str{};

    constexpr str_to_hash(const char *a) noexcept
    {
        for (size_t i = 0u; i < N; ++i)
        {
            str[i] = a[i];
        }
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
        std::size_t hash = 0;


        hash += (hash << 3);
        hash ^= (hash >> 11);
        hash += (hash << 15);

        return hash;
    }
};
template <size_t N>
str_to_hash(const char (&)[N]) -> str_to_hash<N - 1>;

template <str_to_hash str>
  constexpr uint32_t string_to_fnv1_hash()
{
    std::uint32_t hash = 0x811C9DC5;
    for (size_t i = 0u; i < str.size(); ++i)
    {
        hash ^= static_cast<std::uint32_t>(str.str[i]);
        hash *= 0x01000193;
    }

    return hash;
}

namespace fnv_1a
{
    template <typename S>
    struct fnv_internal;
    template <typename S>
    struct fnv1a;
    /*
    }
        template <wstr_to_ba str>
        constexpr uint32_t wstring_to_fnv1_hash()
        {
            std::uint32_t hash = 0x811C9DC5;
            for (size_t i = 0u; i < str.size(); ++i)
            {
                hash ^= static_cast<std::uint32_t>(str.m_str[i]);
                hash *= 0x01000193;
            }

            return hash;
        }
    */
    template <>
    struct fnv_internal<uint32_t>
    {
        constexpr static uint32_t default_offset_basis = 0x811C9DC5;
        constexpr static uint32_t prime = 0x01000193;
    };

    template <>
    struct fnv1a<uint32_t> : public fnv_internal<uint32_t>
    {
        constexpr static uint32_t hash(char const *string, const uint32_t val = default_offset_basis)
        {
            return (string[0] == '\0')
                       ? val
                       : hash(&string[1], (val ^ uint32_t(string[0])) * prime);
        }

        constexpr static uint32_t hash(wchar_t const *string, const uint32_t val = default_offset_basis)
        {
            return (string[0] == L'\0')
                       ? val
                       : hash(&string[1], (val ^ uint32_t(string[0])) * prime);
        }
    };
}

using fnv = fnv_1a::fnv1a<uint32_t>;