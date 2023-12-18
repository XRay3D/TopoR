#pragma once

#include "ctre.hpp"
#include <QString>
#include <array>
#include <limits>
#include <map>
#include <optional>
#include <string>
#include <variant>
#include <vector>

#if __has_include(<cxxabi.h>)
#include <cxxabi.h>
template <typename T>
inline QString typeName(const T& = {}) {
    int status;
    char* const realname = abi::__cxa_demangle(typeid(T).name(), NULL, NULL, &status);
    QString ret{realname};
    if (auto&& [whole, stl, name] = ctre::match<R"(std::(\w+)<.+:(\w+),.+)">(realname); whole)
        ret = QString::fromStdString(stl.to_string() + '<' + name.to_string() + '>');
    else if (auto&& [whole, name] = ctre::match<R"(\S+:XmlAttr<.+:(\w+)>)">(realname); whole)
        ret = QString::fromStdString(name.to_string());
    else if (auto&& [whole, stl, name] = ctre::match<R"(\S+::(\w+)<.+:(\w+)(?:,?.*))">(realname); whole)
        ret = QString::fromStdString(stl.to_string() + '<' + name.to_string() + '>');
    else if (auto&& [whole, name] = ctre::match<R"(.+:(\w+))">(realname); whole)
        ret = QString::fromStdString(name.to_string());
    std::free(realname);
    return ret;
}
#else

inline constexpr auto match1 = ctre::match<R"(std::(\w+)<.+:(\w+),.+)">;
inline constexpr auto match2 = ctre::match<R"(.+:XmlAttr<(?:.+:)?(\w+)>)">;
inline constexpr auto match3 = ctre::match<R"(\S+::(\w+)<.+:(\w+)(?:,?.*))">;
inline constexpr auto match4 = ctre::match<R"(.+:(\w+))">;

template <typename T>
inline QString typeName(const T& = {}) {
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

template <typename... Ts>
struct Overload : Ts... {
    using Ts::operator()...;
};

template <typename... Ts>
Overload(Ts...) -> Overload<Ts...>;

template <typename T>
using Optional = std::optional<T>;

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
