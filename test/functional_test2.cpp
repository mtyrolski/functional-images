#include "../src/functional.hpp"
#include "test.hpp"
#include <cstddef>
#include <type_traits>
#include <utility>

namespace {

struct A
{};
struct B
{};
struct G
{};
struct D
{};

template<std::size_t n>
struct Z
{};

struct P
{};

// W C++20 można użyć funkcji lambda zamiast tego szablonu.
template<typename T, typename... Ts>
T
f(Ts...)
{
  return {};
}

}

int
main()
{
  // "lift0"
  static_assert(std::is_same_v<A, decltype(lift(&f<A>)(std::declval<P>()))>);

  // "lift1"
  static_assert(
    std::is_same_v<B, decltype(lift(&f<B, A>, &f<A, P>)(std::declval<P>()))>);

  // "lift2"
  static_assert(std::is_same_v<G,
                               decltype(lift(&f<G, A, B>, &f<A, P>, &f<B, P>)(
                                 std::declval<P>()))>);

  // "lift42"
  static_assert(
    std::is_same_v<D,
                   decltype(lift(&f<struct D,
                                    Z<0>,
                                    Z<1>,
                                    Z<2>,
                                    Z<3>,
                                    Z<4>,
                                    Z<5>,
                                    Z<6>,
                                    Z<7>,
                                    Z<8>,
                                    Z<9>,
                                    Z<10>,
                                    Z<11>,
                                    Z<12>,
                                    Z<13>,
                                    Z<14>,
                                    Z<15>,
                                    Z<16>,
                                    Z<17>,
                                    Z<18>,
                                    Z<19>,
                                    Z<20>,
                                    Z<21>,
                                    Z<22>,
                                    Z<23>,
                                    Z<24>,
                                    Z<25>,
                                    Z<26>,
                                    Z<27>,
                                    Z<28>,
                                    Z<29>,
                                    Z<30>,
                                    Z<31>,
                                    Z<32>,
                                    Z<33>,
                                    Z<34>,
                                    Z<35>,
                                    Z<36>,
                                    Z<37>,
                                    Z<38>,
                                    Z<39>,
                                    Z<40>,
                                    Z<41>>,
                                 &f<Z<0>, P>,
                                 &f<Z<1>, P>,
                                 &f<Z<2>, P>,
                                 &f<Z<3>, P>,
                                 &f<Z<4>, P>,
                                 &f<Z<5>, P>,
                                 &f<Z<6>, P>,
                                 &f<Z<7>, P>,
                                 &f<Z<8>, P>,
                                 &f<Z<9>, P>,
                                 &f<Z<10>, P>,
                                 &f<Z<11>, P>,
                                 &f<Z<12>, P>,
                                 &f<Z<13>, P>,
                                 &f<Z<14>, P>,
                                 &f<Z<15>, P>,
                                 &f<Z<16>, P>,
                                 &f<Z<17>, P>,
                                 &f<Z<18>, P>,
                                 &f<Z<19>, P>,
                                 &f<Z<20>, P>,
                                 &f<Z<21>, P>,
                                 &f<Z<22>, P>,
                                 &f<Z<23>, P>,
                                 &f<Z<24>, P>,
                                 &f<Z<25>, P>,
                                 &f<Z<26>, P>,
                                 &f<Z<27>, P>,
                                 &f<Z<28>, P>,
                                 &f<Z<29>, P>,
                                 &f<Z<30>, P>,
                                 &f<Z<31>, P>,
                                 &f<Z<32>, P>,
                                 &f<Z<33>, P>,
                                 &f<Z<34>, P>,
                                 &f<Z<35>, P>,
                                 &f<Z<36>, P>,
                                 &f<Z<37>, P>,
                                 &f<Z<38>, P>,
                                 &f<Z<39>, P>,
                                 &f<Z<40>, P>,
                                 &f<Z<41>, P>)(std::declval<P>()))>);
}
