#pragma once

#if 1

#include <algorithm>
#include <array>
#include <limits>
#include <ranges>
#include <set>
#include <string_view>

using std::operator""sv;

template <class Ty>
inline constexpr bool isEnum = false;

namespace Impl {

template <class Ty>
inline constexpr Ty Max = Ty{};

template <class Ty>
inline constexpr Ty Tokens = Ty{};

using sv = std::string_view;
namespace ranges = std::ranges;

inline consteval auto trim(sv str) {
    auto is_space = [](auto ch) {
        // return std::set{' ', ',', '\f', '\n', '\r', '\t', '\v'}.contains(ch);
        return ch == ' ' || ch == ',' || ch == '\f' || ch == '\n' || ch == '\r' || ch == '\t' || ch == '\v';
    };
    while (is_space(str.front())) str = str.substr(1);
    while (is_space(str.back())) str = str.substr(0, str.size() - 1);
    return str;
};

template <class E>
inline consteval auto to_num(sv str) {
    std::underlying_type_t<E> val{};
    for (auto var: str) {
        if (var == '-') continue;
        val *= 10, val += var - '0';
    }
    return str.starts_with('-') ? -val : val;
};

consteval size_t enum_size(sv enums) { return ranges::count(enums, ',') + !enums.ends_with(','); }

template <size_t N, class T>
inline consteval auto tokenize_enum(sv base) {
    size_t count{};
    std::array<std::pair<sv, T>, N> tokens;
    std::underlying_type_t<T> val{};
    sv name;
    for (auto&& word: ranges::views::split(base, ", "sv)) {
        for (int i{}; auto&& tok: ranges::views::split(word, "="sv)) {
            sv token{tok.begin(), tok.end()};
            if (!i)
                name = trim(token);
            else if (token.size())
                val = to_num<T>(trim(token));
            ++i;
        }
        tokens[count++] = {name, static_cast<T>(val++)};
    }
    return tokens;
}

} // namespace Impl

#define ENUM(Enum, ...)                                                    \
    enum class Enum : int {                                                \
        __VA_ARGS__                                                        \
    };                                                                     \
    template <>                                                            \
    inline constexpr bool isEnum<Enum> = true;                             \
    template <>                                                            \
    inline constexpr auto Impl::Max<Enum> = Impl::enum_size(#__VA_ARGS__); \
    template <>                                                            \
    inline constexpr auto Impl::Tokens<Enum> = Impl::tokenize_enum<Impl::Max<Enum>, Enum>(#__VA_ARGS__);

#define ENUM_NS(Name, Enum, ...)                                                 \
    enum class Enum : int {                                                      \
        __VA_ARGS__                                                              \
    };                                                                           \
    template <>                                                                  \
    inline constexpr bool isEnum<Name::Enum> = true;                             \
    template <>                                                                  \
    inline constexpr auto Impl::Max<Name::Enum> = Impl::enum_size(#__VA_ARGS__); \
    template <>                                                                  \
    inline constexpr auto Impl::Tokens<Name::Enum> = Impl::tokenize_enum<Impl::Max<Name::Enum>, Name::Enum>(#__VA_ARGS__);

template <class E>
    requires isEnum<E>
constexpr auto enumToString(E e) {
    auto it = std::ranges::find(Impl::Tokens<E>, e, &std::pair<Impl::sv, E>::second);
    return it == Impl::Tokens<E>.end() ? Impl::sv{} : it->first;
}

template <class E>
inline constexpr Impl::sv enumToString(E e) { return {}; }

template <class E>
    requires isEnum<E>
inline constexpr E stringToEnum(Impl::sv str) {
    auto it = std::ranges::find(Impl::Tokens<E>, str, &std::pair<Impl::sv, E>::first);
    return it == Impl::Tokens<E>.end()
        ? static_cast<E>(
            std::numeric_limits<std::underlying_type_t<E>>::min())
        : it->second;
}

template <class E>
inline constexpr E stringToEnum(Impl::sv str) {
    return {};
}

// ENUM(bfield,
//     one = 1,
//     two = 2,
//     four = 4,
//     eight = 8,
//     sixteen = 16);
// int main() {
//     std::cout << "bfield" << enumToString(static_cast<bfield>(1 | 4)) << "\n";
//     return 0;
// }

#else

#include "ctre.hpp"
#include <map>
#include <string_view>
#include <vector>

std::vector<std::string_view> parse(const char* args) {
    std::vector<std::string_view> ret;
    for (auto&& var: ctre::range<R"(\s*(\w+)\s*.*?)">(args)) {
        ret.emplace_back(var.to_view());
    }
    return ret;
}

template <typename T, typename... Ts>
std::map<T, std::string_view> make_map(const char* text, Ts... args) {
    std::vector<T> keys{args...};
    std::vector<std::string_view> vals = parse(text);
    auto k = keys.cbegin();
    auto v = vals.cbegin();
    std::map<T, std::string_view> r;
    for (; k != keys.cend(); k++, v++) {
        r.emplace(*k, *v);
    }
    return r;
}

#define ENUM(Enum, ...)                                                                             \
    enum class Enum {                                                                               \
        __VA_ARGS__                                                                                 \
    };                                                                                              \
    inline std::string_view to_string(const Enum v) {                                               \
        static const std::map<Enum, std::string_view> m{make_map<Enum>(#__VA_ARGS__, __VA_ARGS__)}; \
        return m.at(v);                                                                             \
    }

#endif
