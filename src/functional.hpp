#ifndef FUNCTIONAL_FUNCTIONAL_H
#define FUNCTIONAL_FUNCTIONAL_H

#include <functional>

namespace Detail {
template <typename Head, typename... Tail> class Composer {
  Head f;
  Composer<Tail...> tail;

public:
  explicit Composer(Head f, Tail... t) : f(f), tail(t...) {}

  template <typename T> auto operator()(const T &x) const { return tail(f(x)); }
};

template <typename Head> class Composer<Head> {
  Head f;

public:
  explicit Composer(Head f) : f(f) {}

  template <typename T> auto operator()(const T &x) const { return f(x); }
};
} // namespace Detail

template <typename... FList> auto compose(FList... fl) {
  return Detail::Composer<FList...>(fl...);
}

/**
 * @brief composing functions
 * compose()(x) == identity(x)
 * compose(f)(x) == f(x)
 * compose(f, g)(x) == g(f(x))
 * @return  compose of given functions
 */
template <> inline auto compose<>() {
  return [](const auto &T) { return T; };
}

/**
 * @brief functional point wise lifting
 * lift(h)
 * a -> (p -> a)
 * h
 *
 * lift(h, f1)
 * (a -> b) -> (p -> a) -> (p -> b)
 *    h           f1
 * lift(h, f1, f2)
 * (a -> b -> g) -> (p -> a) -> (p -> b) -> (p -> g)
 *       h             f1          f2
 *  ...
 * lift(h, f1, ..., fn)
 * (a1 -> ... -> an -> d) -> (p -> a1) -> ... -> (p -> an) -> (p -> d)
 *           h                  f1                  fn
 * @tparam H - header function type for lifting
 * @tparam Fs - helper functions type which will take argument p
 * @param h - header function
 * @param fs - helper functions
 * @return point wise lifted function
 */
template <typename H, typename... Fs> auto lift(H h, Fs... fs) {
  return [h, fs...](auto p) { return h(fs(p)...); };
}

#endif // FUNCTIONAL_FUNCTIONAL_H