#pragma once

#include "ctre.hpp"
#include "qdebug.h"
#include <QString>
#include <array>
#include <limits>
#include <map>
#include <optional>
#include <ranges>
#include <string>
#include <variant>
#include <vector>

#if 0
#if __has_include(<cxxabi.h>)
#include <cxxabi.h>

// [22/23 0.3/sec] Building CXX object CMakeFiles/TopoRTest.dir/main.cpp.obj
// Elapsed time: 59 s. (time), 59.486 s. (clock)

inline constexpr auto match1 = ctre::match<R"(std::(\w+)<.+:(\w+),.+)">;
inline constexpr auto match2 = ctre::match<R"(\S+:XmlAttr<.+:(\w+)>)">;
inline constexpr auto match3 = ctre::match<R"(\S+::(\w+)<.+:(\w+)(?:,?.*))">;
inline constexpr auto match4 = ctre::match<R"(.+:(\w+))">;

template <typename T>
inline QString typeName(const T& = {}) {
    int status;
    char* const realname = abi::__cxa_demangle(typeid(T).name(), NULL, NULL, &status);
    QString ret{realname};
    if (auto&& [whole, stl, name] = match1(realname); whole)
        ret = QString::fromStdString(stl.to_string() + '<' + name.to_string() + '>');
    else if (auto&& [whole, name] = match2(realname); whole)
        ret = QString::fromStdString(name.to_string());
    else if (auto&& [whole, stl, name] = match3(realname); whole)
        ret = QString::fromStdString(stl.to_string() + '<' + name.to_string() + '>');
    else if (auto&& [whole, name] = match4(realname); whole)
        ret = QString::fromStdString(name.to_string());
    std::free(realname);
    qWarning() << ret << __PRETTY_FUNCTION__;
    return ret;
}
#else

inline constexpr auto match1 = ctre::match<R"(std::(\w+)<.+:(\w+),.+)">;
inline constexpr auto match2 = ctre::match<R"(\S+:XmlAttr<.+:(\w+)>)">;
// inline constexpr auto match2 = ctre::match<R"(.+:XmlAttr<(?:.+:)?(\w+)>)">;
inline constexpr auto match3 = ctre::match<R"(\S+::(\w+)<.+:(\w+)(?:,?.*))">;
inline constexpr auto match4 = ctre::match<R"(.+:(\w+))">;

template <typename T>
inline consteval auto typeName(const T& = {}) {
std::string_view sv{}
    QString ret{typeid(T).name()};
    QByteArray realname{ret.toUtf8()};
    if (auto&& [whole, stl, name] = match1(realname); whole)
        ret = QString::fromStdString(stl.to_string() + '<' + name.to_string() + '>');
    else if (auto&& [whole, name] = match2(realname); whole)
        ret = QString::fromStdString(name.to_string());
    else if (auto&& [whole, stl, name] = match3(realname); whole)
        ret = QString::fromStdString(stl.to_string() + '<' + name.to_string() + '>');
    else if (auto&& [whole, name] = match4(realname); whole)
        ret = QString::fromStdString(name.to_string());
    return ret;
}
#endif
#else

// template <std::size_t N>
// struct String {
//     char16_t data[N]{};
//     constexpr String(char16_t const (&str)[N]) { std::ranges::copy(str, data); };
//     constexpr auto staticData() const { return staticData(std::make_index_sequence<N>{}); };
// private:
//     template <std::size_t... Is>
//     constexpr auto staticData(std::index_sequence<Is...>) const {
//         return QStaticStringData<N>{
//             QArrayData{{-1}, N - 1, 0, 0, sizeof(QStringData)},
//             {data[Is]...},
//         };
//     };
// };
// template <String Str>
// /*constexpr*/ auto operator"" _qs() noexcept {
//     static auto qstring_literal = Str.staticData();
//     return QString{{qstring_literal.data_ptr()}};
// }

// Elapsed time: 40 s. (time), 39.405 s. (clock)
namespace Impl {
template <typename T>
inline consteval auto typeName() {
#ifdef _MSC_VER
    constexpr std::string_view sv = __FUNCSIG__;
    constexpr auto last = sv.find_last_not_of(" &>(}", sv.size() - 6);
#else
    constexpr std::string_view sv{__PRETTY_FUNCTION__};
    constexpr auto last = sv.find_last_not_of(" &>]");
#endif
    constexpr auto first = sv.find_last_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_0123456789", last);
    constexpr size_t size = last - first + 1;
    std::array<char, size> res{};
    auto it = res.data();
    for (auto a{first + 1}; a <= last; ++a) *it++ = sv[a];
    return res;
}

template <typename T>
inline constexpr auto Name = typeName<T>();

} // namespace Impl

template <typename T>
inline constexpr auto TypeName = QLatin1String{Impl::Name<T>.data(), Impl::Name<T>.size() - 1};

#endif

template <typename... Ts>
struct Overload : Ts... {
    using Ts::operator()...;
};

template <typename... Ts>
Overload(Ts...) -> Overload<Ts...>;

template <typename T>
using Optional = std::optional<T>;
// struct Optional : std::optional<T> {
//     using Opt = std::optional<T>;
//     using Opt::operator bool;
//     operator const T&() const { return Opt::value(); }
// };

template <typename T>
struct XmlAttr {
    using TypeName = T;
    T value{};

    // XmlAttr() { } // disable std::is_aggregate_v<T>
    // XmlAttr(const T& val = {})
    //     : value{val} { }
    // XmlAttr(T&& val)
    //     : value{std::move(val)} { }
    // XmlAttr(const XmlAttr&) = default;
    // XmlAttr(XmlAttr&&) = default;

    operator T&() noexcept { return value; }
    operator const T&() const noexcept { return value; }
    T& operator=(const T& val) noexcept { return value = val; }
    T& operator=(T&& val) noexcept { return value = val; }

    // auto operator<=>(const T& other) const {
    //     return value <=> other;
    // }
};

template <typename T>
struct XmlArray : std::vector<T>, std::false_type {
    using std::vector<T>::vector;
};

template <typename T>
struct XmlArrayElem : std::vector<T>, std::true_type {
    using std::vector<T>::vector;
};

template <typename... Ts>
struct XmlVariant : std::variant<Ts...> {
    using std::variant<Ts...>::variant;
    using Variant = std::variant<Ts...>;
    template <typename Func>
    auto visit(Func&& func) {
        return std::visit(std::forward<Func>(func), *this);
    }
    template <typename Func>
    auto visit(Func&& func) const {
        return std::visit(std::forward<Func>(func), *this);
    }
    template <typename... Funcs>
    auto visit(Funcs&&... funcs) {
        return std::visit(Overload{std::forward<Funcs>(funcs)...}, *this);
    }
    template <typename... Funcs>
    auto visit(Funcs&&... funcs) const {
        return std::visit(Overload{std::forward<Funcs>(funcs)...}, *this);
    }
    bool has_value() const { return Variant::index() != std::variant_npos; }
    operator bool() const { return has_value(); }
};
