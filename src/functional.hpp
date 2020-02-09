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

template <> inline auto compose<>() {
  return [](const auto &T) { return T; };
}

#endif // FUNCTIONAL_FUNCTIONAL_H