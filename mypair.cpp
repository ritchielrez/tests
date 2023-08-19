#include <type_traits>
template <typename A, typename B> struct MyPair {
    MyPair() { }
    MyPair(const A&, const B&) { }
};
int main() {
    MyPair mp{11, 22};
    static_assert(std::is_same_v<decltype(mp), MyPair<int, int>>);
}
