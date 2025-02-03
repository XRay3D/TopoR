#pragma once

#include "pfr.hpp"
// #include "boost/type_index.hpp"

#include <QVariant>
#include <utility>
// #include <vcruntime.h>

using index_t = size_t;

template <typename T>
inline constexpr index_t pod_size_v = pfr::tuple_size<std::decay_t<T>>::value;

// #define __TEMPLATES_RECURSION__
// #define __VARIADIC_TEMPLATES_UNPACKING_IF__
// #define __VARIADIC_TEMPLATES_UNPACKING_ARRAY_FUNC__
#define __VARIADIC_TEMPLATES_UNPACKING_ARRAY_VIRT__

#ifdef __TEMPLATES_RECURSION__ // 175.828 ms 99
////////////////////////////////////////////////////////////////////
///
///
template <index_t I>
struct get_visit_impl {
    template <typename T, typename F>
    constexpr static void visit(T& pod, const index_t idx, F fun) {
        (idx == I - 1) ? fun(boost::pfr::get<I - 1>(pod))
                       : get_visit_impl<I - 1>::visit(pod, idx, fun);
    }
    template <typename T>
    constexpr static auto get(T& pod, const index_t idx) {
        return (idx == I - 1) ? boost::pfr::get<I - 1>(pod)
                              : get_visit_impl<I - 1>::get(pod, idx);
    }
};

template <>
struct get_visit_impl<0> {
    // clang-format off
    template <typename T, typename F>
    static void visit(T&, index_t, F) { assert(false); }
    template <typename T>
    static QVariant get(T&, index_t) { assert(false); return {}; }
    // clang-format on
};

template <typename F, typename T>
constexpr void visit_at(T& pod, const index_t idx, F fun) { get_visit_impl<pod_size_v<T>>::visit(pod, idx, fun); }
template <typename F, typename T>
constexpr void visit_at(const T& pod, const index_t idx, F fun) { get_visit_impl<pod_size_v<T>>::visit(pod, idx, fun); }

template <typename T>
constexpr auto get_at(T& pod, const index_t idx) { return get_visit_impl<pod_size_v<T>>::get(pod, idx); }
template <typename T>
constexpr auto get_at(const T& pod, const index_t idx) { return get_visit_impl<pod_size_v<T>>::get(pod, idx); }

#elif defined(__VARIADIC_TEMPLATES_UNPACKING_IF__) // 138.9 ms 99
////////////////////////////////////////////////////////////////////
///
///
template <typename T, typename F, index_t... I>
void visit_impl(T& pod, const index_t idx, F fun, std::index_sequence<I...>) {
    ((I == idx ? fun(boost::pfr::get<I>(pod)) : void()), ...);
}

template <typename T, index_t... I>
QVariant get_impl(T&& pod, const index_t idx, std::index_sequence<I...>) {
    QVariant ret;
    return ((I == idx ? ret = boost::pfr::get<I>(pod) : ret), ..., ret);
}

template <typename F, typename T, typename Indices = std::make_index_sequence<pod_size_v<T>>>
constexpr void visit_at(T& pod, const index_t idx, F fun) { visit_impl(pod, idx, fun, Indices{}); }
template <typename F, typename T, typename Indices = std::make_index_sequence<pod_size_v<T>>>
constexpr void visit_at(const T& pod, const index_t idx, F fun) { visit_impl(pod, idx, fun, Indices{}); }

// template <typename T, typename Indices = std::make_index_sequence<pod_size_v<T>>>
// constexpr auto get_at(T& pod, const index_t idx) { return get_impl(pod, idx, Indices {}); }
template <typename T, typename Indices = std::make_index_sequence<pod_size_v<T>>>
constexpr auto get_at(const T& pod, const index_t idx) { return get_impl(pod, idx, Indices{}); }

#elif defined(__VARIADIC_TEMPLATES_UNPACKING_ARRAY_FUNC__) // 122.626 ms 99
////////////////////////////////////////////////////////////////////
///
///
namespace detail {

template <index_t I>
struct getter final {
    template <typename T>
    auto operator()(T&& pod) { return (boost::pfr::get<I>(pod)); }
};

template <typename T, index_t... Is>
struct array {
    static inline std::function<QVariant(T)> data[] = {getter<Is>()...};
};

template <typename T, index_t... I>
auto get_impl(T&& pod, const index_t idx, std::index_sequence<I...>) {
    return array<T, I...>::data[idx](pod);
}

template <typename T, typename F, index_t... I>
void visit_impl(T&& pod, const index_t idx, F fun, std::index_sequence<I...>) {
    ((I == idx ? fun(boost::pfr::get<I>(pod)) : void()), ...);
}

} // namespace detail

template <typename F, typename T, typename Indices = std::make_index_sequence<pod_size_v<T>>>
constexpr void visit_at(T&& pod, const index_t idx, F fun) {
    detail::visit_impl(pod, idx, fun, Indices{});
}
template <typename F, typename T, typename Indices = std::make_index_sequence<pod_size_v<T>>>
constexpr void visit_at(const T& pod, const index_t idx, F fun) {
    detail::visit_impl(pod, idx, fun, Indices{});
}

template <typename T, typename Indices = std::make_index_sequence<pod_size_v<T>>>
constexpr auto get_at(T&& pod, const index_t idx) { return detail::get_impl(pod, idx, Indices{}); }
template <typename T, typename Indices = std::make_index_sequence<pod_size_v<T>>>
constexpr auto get_at(const T& pod, const index_t idx) { return detail::get_impl(pod, idx, Indices{}); }

#elif defined(__VARIADIC_TEMPLATES_UNPACKING_ARRAY_VIRT__) // 116.363 ms 99
////////////////////////////////////////////////////////////////////

template <typename T>
QVariant toVariant(const T& val) {
    return {}; // QVariant::fromValue(val);
}

namespace detail {

template <typename T>
struct getter1 {
    virtual QVariant get(T&& pod) = 0;
};

template <index_t I, typename T>
struct getter final : getter1<T> {
    QVariant get(T&& pod) override { return toVariant(pfr::get<I>(std::forward<T>(pod))); }
};

template <typename T, index_t... Is>
struct array {
    static constexpr size_t size = sizeof(getter<0, T>);
    static inline char ptr[size * sizeof...(Is)] = {};
    static inline getter1<T>* data2[] = {new(ptr + Is * size) getter<Is, T>()...};
};

template <typename T, index_t... I>
auto get_impl(T&& pod, const index_t idx, std::index_sequence<I...>) {
    return array<T, I...>::data2[idx]->get(std::forward<T>(pod));
}

template <typename T, typename F, index_t... I>
void visit_impl(T&& pod, const index_t idx, F fun, std::index_sequence<I...>) {
    ((I == idx ? fun(pfr::get<I>(std::forward<T>(pod))) : void()), ...);
}

} // namespace detail

template <typename F, typename T>
constexpr void visit_at(T&& pod, const index_t idx, F fun) {
    detail::visit_impl(std::forward<T>(pod), idx, fun, std::make_index_sequence<pod_size_v<T>>{});
}

template <typename T>
constexpr auto get_at(T&& pod, const index_t idx) {
    return detail::get_impl(std::forward<T>(pod), idx, std::make_index_sequence<pod_size_v<T>>{});
}

#endif
