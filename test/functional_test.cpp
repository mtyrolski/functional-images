#include "../src/functional.hpp"

int main()
{
    assert(compose()(42) == 42);
    assert(compose([](auto x) { return x + 1; },
                   [](auto x) { return x * x; })(1) == 4);

    const auto h1 = [](auto a, auto b) {
        auto g = a * b;
        return g;
    };
    const auto h2 = [](auto a, auto b) {
        auto g = a + b;
        return g;
    };
    const auto f1 = [](auto p) {
        auto a = p;
        return a;
    };
    const auto f2 = [](auto p) {
        auto b = p;
        return b;
    };
    assert(lift(h1, f1, f2)(42) == 42 * 42);
    assert(lift(h2, f1, f2)(42) == 42 + 42);

    return 0;
}