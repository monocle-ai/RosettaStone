// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_UTILS_HPP
#define ROSETTASTONE_UTILS_HPP

#include <effolkronium/random.hpp>

#include <cstddef>
#include <functional>
#include <string>
#include <vector>

using Random = effolkronium::random_static;

//! Checks all conditions are true.
//! \param t A value to check that it is true.
//! \return true if all conditions are true, false otherwise.
template <typename T>
constexpr bool AllCondIsTrue(const T& t)
{
    return static_cast<bool>(t);
}

//! Checks all conditions are true.
//! \param t A value to check that it is true.
//! \param args Rest values to check that they are true.
//! \return true if all conditions are true, false otherwise.
template <typename T, typename... Others>
constexpr bool AllCondIsTrue(const T& t, const Others&... args)
{
    return (static_cast<bool>(t)) && AllCondIsTrue(args...);
}

//! Combines hash function with given \p v.
//! \param seed The seed value to combine hash function.
//! \param v The value to pass std::hash.
//!
//! It is based on peter1591's hearthstone-ai repository.
//! References: https://github.com/peter1591/hearthstone-ai
template <typename T>
void CombineHash(std::size_t& seed, const T& v)
{
    seed ^= std::hash<T>()(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

//! Erases item if it is matched predicate.
//! \param items A container consists of item.
//! \param predicate The condition to erase item.
template <typename ContainerT, typename PredicateT>
void EraseIf(ContainerT& items, const PredicateT& predicate)
{
    for (auto it = items.begin(); it != items.end();)
    {
        if (predicate(*it))
        {
            it = items.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

//! Gets N elements from a list of distinct elements by using the default
//! equality comparer. The source list must not have any repeated elements.
//! \param list A list of distinct elements to choose.
//! \param amount The number of elements to choose.
//! \return A list of N distinct elements.
template <typename T>
std::vector<T*> ChooseNElements(std::vector<T*> list, int amount)
{
    const std::size_t size = list.size();
    if (amount > size)
    {
        amount = size;
    }

    std::vector<T*> results;
    results.reserve(amount);

    std::vector<std::size_t> indices;
    indices.reserve(amount);

    for (int i = 0; i < amount; ++i)
    {
        std::size_t idx;
        bool flag;

        do
        {
            idx = Random::get<std::size_t>(0, list.size() - 1);
            flag = false;

            for (int j = 0; j < i; ++j)
            {
                if (indices[j] == idx)
                {
                    flag = true;
                    break;
                }
            }
        } while (flag);

        results.emplace_back(list[idx]);
        indices.emplace_back(idx);
    }

    return results;
}

//! Decodes Base64 based string.
//! \param src Base64 based string.
//! \return A unsigned char type container consists of decoded string.
std::vector<unsigned char> DecodeBase64(const std::string& src);

#endif  // ROSETTASTONE_UTILS_HPP
