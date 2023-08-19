#include <stddef.h>
#include <type_traits>

template <typename T, size_t N> struct MyArray {
    T m_array[N];
};
template <typename First, typename... Rest> struct EnforceSame {
    static_assert(std::conjunction_v<std::is_same<First, Rest>...>);
    using type = First;
};
template <typename First, typename... Rest> MyArray(First, Rest...)
    -> MyArray<typename EnforceSame<First, Rest...>::type, 1 + sizeof...(Rest)>;
int main() {
    MyArray a = { 11, 22, 33, 44 };
}
