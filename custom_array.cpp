#include <cassert>
#include <cstdint>
#include <iostream>
#include <type_traits>

namespace rit
{
template <typename First, typename... Rest>
struct array_enforce_type
{
    static_assert(std::conjunction_v<std::is_same<First, Rest>...>, "Make sure all array elements have the same type");
    using type = First;
};

template <typename T, std::size_t capacity>
struct array
{
    T m_arr[capacity];

    // Returning a reference so if user wants to change value of index they can because a reference is returned
    T& operator[](const int64_t index)
    {
        if(index < 0)
        {
            std::cerr << "Invalid negative array index\n";
            exit(EXIT_FAILURE);
        };

        if(index >= capacity)
        {
            std::cerr << "Array index access out of bound\n";
            exit(EXIT_FAILURE);
        }

        return m_arr[index];
    }
};

template <typename First, typename... Rest>
array(First, Rest...)
    -> array<typename array_enforce_type<First, Rest...>::type, sizeof...(Rest) + 1>;
};

int main()
{
    rit::array arr {1,2,3,4,5};

    for(const int &e : arr.m_arr)
    {
        std::cout << e << " ";
    }
    std::cout << "\n";

    arr[0] = 2;
    std::cout << arr[0] << "\n";
}

