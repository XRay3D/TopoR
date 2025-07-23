#pragma once

#include <QString>
#include <array>
#include <meta>
#include <optional>
#include <variant>
#include <vector>

namespace meta = std::meta;

namespace Xml {

#ifdef _MSC_VER
#define __PRETTY_FUNCTION__ __FUNCSIG__;
#endif

namespace Impl {
template <typename T>
inline consteval auto typeName() {
    constexpr std::string_view sv = __PRETTY_FUNCTION__;
#ifdef _MSC_VER
    constexpr auto last = sv.find_last_not_of(" &>(}", sv.size() - 6);
#else
    constexpr auto last = sv.find_last_not_of(" &>]");
#endif
    constexpr auto first = sv.find_last_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_0123456789", last);
    constexpr size_t size = last - first + 1;
    std::array<char, size> res{};
    auto it = res.data();
    for(auto a{first + 1}; a <= last; ++a) *it++ = sv[a];
    return res;
}

template <typename T>
inline constexpr auto Name = typeName<T>();

} // namespace Impl

template <typename T>
inline constexpr auto TypeName = QLatin1String{Impl::Name<T>.data(), Impl::Name<T>.size() - 1};

template <typename... Ts>
struct Overload : Ts... {
    using Ts::operator()...;
};

template <typename... Ts>
Overload(Ts...) -> Overload<Ts...>;

constexpr bool NoOpt{};

struct Attribute {
    bool optional = true;
    consteval auto operator()(bool optional) const -> Attribute { return {.optional = optional}; }
    // explicit operator bool() const { return optional ? value != T{} : true; };
};

static constexpr auto Attr = Attribute{};

// template <typename T, bool Optional = true>
// struct Attr /*: std::integral_constant<bool, Optional>*/ { // xml attribute
//     using TypeName = T;
//     T value{};

//     explicit operator bool() const { return Optional ? value != T{} : true; };

//     auto operator+() const noexcept
//         requires std::is_enum_v<T>
//     { return std::to_underlying(value); };

//     // Attr() { } // disable std::is_aggregate_v<T>
//     // Attr(const T& val = {})
//     //     : value{val} { }
//     // Attr(T&& val)
//     //     : value{std::move(val)} { }
//     // Attr(const Attr&) = default;
//     // Attr(Attr&&) = default;

//     operator T&() noexcept { return value; }
//     operator const T&() const noexcept { return value; }
//     T& operator=(const T& val) noexcept { return value = val; }
//     T& operator=(T&& val) noexcept { return value = val; }

//     // auto operator<=>(const T& other) const {
//     //     return value <=> other;
//     // }
// };

template <typename T>
struct Optional;

// template <typename T, bool Opt>
// struct Optional<Attr<T, Opt>> : std::optional<Attr<T, Opt>> {
//     using opt = std::optional<Attr<T, Opt>>;
//     using std::optional<Attr<T, Opt>>::optional;
//     operator T() const { return (opt::has_value()) ? opt::value().value : T{}; }
// };

template <typename T>
struct Optional : std::optional<T> {
    using opt = std::optional<T>;
    using std::optional<T>::optional;
    operator T() const { return (opt::has_value()) ? opt::value() : T{}; }
    // using operator bool();
    // auto& operator=(T&& val) { return Optional::emplace(std::move(val)), Optional::value(); }
    // auto& operator=(const T& val) { return Optional::emplace(val), Optional::value(); }
};

template <typename T, typename CanSkip = std::true_type>
struct Array : std::vector<T> /*, std::false_type*/ { // xml inpace array of elements of type T
    using vector = std::vector<T>;
    using vector::vector;
    bool canSkip() const { return CanSkip::value ? vector::empty() : false; }
};

// using DontSkip = std::false_type;
static constexpr auto DontSkip = false;

struct ArrayElement {
    bool canSkip_ = true;
    consteval auto operator()(bool canSkip) const -> ArrayElement {
        return {.canSkip_ = canSkip};
    }
    template <typename T>
    bool canSkip(const std::vector<T>& vector) const { return canSkip_ ? vector.empty() : false; }
};

static constexpr auto ArrayElem = ArrayElement{};

// template <typename T, typename CanSkip = std::true_type>
// struct ArrayElem : std::vector<T>, CanSkip { // xml element
//     using vector = std::vector<T>;
//     using vector::vector;
//     bool canSkip() const { return CanSkip::value ? vector::empty() : false; }
// };

// struct NullVariant { };

template <typename... Ts>
struct Variant : std::variant</*NullVariant,*/ Ts...> {
    using variant = std::variant</*NullVariant,*/ Ts...>;
    using variant::variant;
    using variant::operator=;
    // using FirstType = std::tuple_element_t<0, std::tuple<Ts...>>;
    // template <typename Func>
    // auto visit(Func&& func) {
    //     return std::visit(std::forward<Func>(func), *this);
    // }
    template <typename Func>
    decltype(auto) visit(Func&& func) const {
        // using Ret = decltype(func(FirstType{}));
        // return std::visit(Overload{[](NullVariant) -> Ret { if constexpr( !std::is_same_v<void ,Ret>) return {}; }, std::forward<Func>(func)}, *this);
        return std::visit(std::forward<Func>(func), *this);
    }
    // template <typename... Funcs>
    // auto visit(Funcs&&... funcs) {
    //     return std::visit(Overload{std::forward<Funcs>(funcs)...}, *this);
    // }
    template <typename... Funcs>
    decltype(auto) visit(Funcs&&... funcs) const {
        // using Ret = std::tuple_element_t<0, std::tuple<decltype(funcs({}))...>>;
        // return std::visit(Overload{[](NullVariant) -> Ret {if constexpr( !std::is_same_v<void ,Ret>)  return {}; }, std::forward<Funcs>(funcs)...}, *this);
        return std::visit(Overload{std::forward<Funcs>(funcs)...}, *this);
    }
    // bool has_value() const { return Variant::index() > 0 && Variant::index() != std::variant_npos; }
    bool has_value() const { return Variant::index() != std::variant_npos; }
    operator bool() const { return has_value(); }
};

/// Skippable
template <typename T> concept Heritable = !std::is_fundamental_v<T> && !std::is_pointer_v<T>;
template <typename T> concept NotHeritable = !Heritable<T>;

struct SkipField {
} constexpr Skip; // пропуск поля

template <std::size_t N>
struct Name {
    char p[N]{};
    constexpr Name(char const (&pp)[N]) {
        std::ranges::copy(pp, p);
    }
    operator QString() const { return QString::fromUtf8(p, N - 1); }
};

template <typename T, Name name>
struct NamedTag : T {
    using T::T;
    T& operator*() { return *this; }
    const T& operator*() const { return *this; }
};

} // namespace Xml

using Xml::NoOpt;
