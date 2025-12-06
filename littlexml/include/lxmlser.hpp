#pragma once

#include "lxml.hpp"
#include <algorithm>
#include <cassert>
#include <charconv>
#include <memory>
#include <meta>
#include <optional>
#include <print>
#include <ranges>
#include <stack>
#include <unordered_map>
#include <vector>

namespace XML {

namespace r = std ::ranges;
namespace v = std ::views;
using std ::print;
using std ::println;
using std ::string_view;

// =============== Serialiser ===============

struct Ignore_ {
} inline constexpr Ignore;

struct Type {
    enum eType {
        Null,
        Element,
        Attr,
        Root,
        Array,
    } type{};
    const char* name = nullptr;
    consteval auto operator()(string_view name) const noexcept -> Type {
#if CR
        return {.type = type, .name = std::define_static_string(name)};
#else
        return {.type = type, .name = name.data()};
#endif
    }
    constexpr auto operator<=>(const Type&) const noexcept = default;
    constexpr operator string_view() const noexcept { return name ? name : string_view{}; };
} inline constexpr Elem{Type::Element},
    Attr{Type::Attr},
    Root{Type::Root},
    Array{Type::Array};

namespace meta = std ::meta;

// template <typename T>
// consteval std::optional<T> annotationOfType(meta::info r) {
//     auto v = annotations_of(r, ^^T);
//     std::optional<T> result{};
//     for(meta::info a: v) {
//         if(auto val = meta::extract<T>(a); result.has_value() && *result != val)
//             throw "inconsistent annotations";
//         else {
//             result = std::move(val);
//         }
//     }
//     return result;
// }

#if GR

#define annotations_of annotations_of_with_type

template <typename T>
consteval std::optional<T> annotation_of_type(meta::info r) {
    auto v = annotations_of(r, ^^T);
    std::optional<T> result{};
    for(meta::info a: v) {
        if(result.has_value()) {
            if(extract<T>(a) != result) {
                throw "inconsistent annotations";
            }
        } else {
            result = extract<T>(a);
        }
    }
    return result;
}
#endif

template <meta::info INFO> concept HasXmlAnnotation
    = meta::annotations_of(INFO, ^^Type).size() == 1;

template <meta::info INFO> concept IsRoot
    = HasXmlAnnotation<INFO>
    && annotation_of_type<Type>(INFO)->type == Type::Root;

template <meta::info INFO> concept IsElem
    = HasXmlAnnotation<INFO>
    && annotation_of_type<Type>(INFO)->type == Type::Element;

template <meta::info INFO> concept IsAttr
    = HasXmlAnnotation<INFO>
    && annotation_of_type<Type>(INFO)->type == Type::Attr;

template <meta::info INFO> concept IsArr
    = HasXmlAnnotation<INFO>
    && annotation_of_type<Type>(INFO)->type == Type::Array;

template <typename R> concept IsRange
    = requires(R r) { r::begin(r); r::end(r); };

template <typename T> concept IsEnum = std::is_enum_v<T>;

inline constexpr const char Black[]{"\033[30m"};
inline constexpr const char Blue[]{"\033[34m"};
inline constexpr const char Cyan[]{"\033[36m"};
inline constexpr const char Gray[]{"\033[90m"};
inline constexpr const char Green[]{"\033[32m"};
inline constexpr const char Magenta[]{"\033[35m"};
inline constexpr const char Red[]{"\033[31m"};
inline constexpr const char White[]{"\033[37m"};
inline constexpr const char Yellow[]{"\033[33m"};

inline constexpr const char Cancel[]{"\033[39m"};
template <size_t N>
struct Str {
    static constexpr size_t SIZE = N;
    char data[N + 1]{};
    constexpr Str(const char (&str)[N]) noexcept { r::copy(str, data); }
    constexpr operator string_view() const noexcept { return data; }
};
// template <size_t N>
// Str(const char (&)[N]) -> Str<N>;

template <Str Color>
struct Log {
    template <typename... Args>
    static constexpr void operator()(std::format_string<Args...> format, Args&&... args) {
        print(Color);
        println(format, std::forward<Args>(args)...);
        print(Cancel);
    }
};

inline constexpr auto logBlack = Log<Black>{};
inline constexpr auto logBlue = Log<Blue>{};
inline constexpr auto logCyan = Log<Cyan>{};
inline constexpr auto logGray = Log<Gray>{};
inline constexpr auto logGreen = Log<Green>{};
inline constexpr auto logMagenta = Log<Magenta>{};
inline constexpr auto logRed = Log<Red>{};
inline constexpr auto logWhite = Log<White>{};
inline constexpr auto logYellow = Log<Yellow>{};

template <IsEnum Enum>
inline constexpr auto toEnum(string_view name) -> Enum {
    template for(constexpr meta::info ENUM:
        std::define_static_array(enumerators_of(^^Enum))) {
        if(std::meta::display_string_of(ENUM) == name) return [:ENUM:];
    }
    return Enum{};
}

template <IsEnum Enum>
inline constexpr auto toString(Enum e) -> string_view {
    // clang-format off
    switch(e) {
    template for(constexpr meta::info ENUM: std::define_static_array(enumerators_of(^^Enum)))
    case [:ENUM:]: return display_string_of(ENUM);
    default: return {};
    }
    // clang-format on
}

template <typename T>
static consteval auto members() {
    static constexpr auto CTX = meta::access_context::unchecked();
    return std::define_static_array([] consteval {
        auto members = nonstatic_data_members_of(^^T, CTX);
        [&members](this auto self, auto&& bases) -> void {
            for(meta::info base: bases | v::transform(meta::type_of)) {
                self(bases_of(base, CTX));
                members.append_range(meta::nonstatic_data_members_of(base, CTX));
            }
        }(bases_of(^^T, CTX));
        return members;
    }());
}

struct Serialiser {
    Serialiser(string_view path)
        : path{path}, loaded{document.load(path)}, node{&document.root} { }

    template <typename T>
    void operator>>(T& data) {
        constexpr string_view NAME_OF{nameOf<^^T>()};
        if(loaded) load<^^T>(data, node);
    }

private:
    string_view path;
    Document document;
    bool loaded;

    static constexpr auto CTX = meta::access_context::unchecked();

    template <meta::info INFO>
    static consteval auto nameOf() -> string_view {
        constexpr string_view A_NAME{[] consteval -> string_view {
            if constexpr(HasXmlAnnotation<INFO>)
                return *annotation_of_type<Type>(INFO);
            return string_view{};
        }()};
        constexpr string_view T_NAME{is_type(INFO)
                ? display_string_of(INFO)
                : display_string_of(type_of(INFO))};
        constexpr string_view F_NAME{is_type(INFO)
                ? ""
                : display_string_of(INFO)};
        // logYellow("nameOf -> A: {}, T: {}, F: {}", A_NAME, T_NAME, F_NAME);
        return A_NAME.size() ? A_NAME : (F_NAME.size() ? F_NAME : T_NAME);
    }

    template <typename T>
    static consteval auto nameOf() -> string_view { return nameOf<^^T>(); }

    template <meta::info INFO>
    static consteval auto typeOf() -> Type::eType {
        if constexpr(HasXmlAnnotation<INFO>)
            return annotation_of_type<Type>(INFO)->type;
        return {};
    }
    template <typename T>
    static consteval auto typeOf() -> Type::eType { return typeOf<^^T>(); }

    // ======================================================================

#if 0
    using ptree = boost::property_tree::ptree;

    ptree& node;

    template <meta::info INFO, typename T>
    static void load(T& data, ptree& node) {
        constexpr string_view NAME_OF{nameOf<INFO>()};
        logRed("name {}", NAME_OF);

        node.get_optional(NAME_OF);

        // Data* val = IsAttr<INFO> ? node->attr(NAME_OF)
        //                          : node->firstChild(NAME_OF);
        // if(!val) {
        //     // logRed("data {} {}", NAME_OF, display_string_of(^^T));
        //     data = {};
        //     return;
        // }
        if constexpr(std::is_same_v<T, std::string>) {
            data = node.get<T>(NAME_OF, {});
        } else if constexpr(std::is_enum_v<T>) {
            data = toEnum<string_view>(node.get<T>(NAME_OF, {}));
        } else if constexpr(std::is_arithmetic_v<T>) {
            data = node.get<T>(NAME_OF, {});
        } else {
            auto tree = node.get_child_optional(NAME_OF);
            static_assert(members<T>().size(), display_string_of(^^T));
            template for(constexpr meta::info MEMBER: members<T>())
                load<MEMBER>(data.[:MEMBER:], node);
        }
    }

#else

    NodeTag* node;
    std::stack<NodeTag*> stack;

    // ======================================================================

    template <typename T>
    static void load(T& data, NodeTag* node) { load<^^T>(data, node); }

    template <meta::info INFO, typename T>
    static void load(T& data, NodeTag* node) {
        constexpr string_view NAME_OF{nameOf<INFO>()};
        Data* val = IsAttr<INFO> ? node->attr(NAME_OF)
                                 : node->firstChild(NAME_OF);
        if(!val) {
            // logRed("data {} {}", NAME_OF, display_string_of(^^T));
            data = {};
            return;
        }
        if constexpr(std::is_same_v<T, std::string>) {
            data = val->value;
            // logGreen("{} {}", display_string_of(^^T), data);
        } else if constexpr(std::is_enum_v<T>) {
            data = toEnum<T>(val->value);
            // logGreen("{} {}", display_string_of(^^T), val->value);
        } else if constexpr(std::is_arithmetic_v<T>) {
            std::from_chars(
                val->value.data(),
                val->value.data() + val->value.size(),
                data);
            // logGreen("{} {}", display_string_of(^^T), data);
        } else {
            logRed("data {} {}", NAME_OF, display_string_of(^^T));
            // static_assert(false, display_string_of(^^T)); // TODO
        }
    }

    template <meta::info INFO, typename... Ts>
    static void load(std::variant<Ts...>& data, NodeTag* node) { // for ,Node* ndall
        struct Pair {
            string_view name;
            void (*func)(std::variant<Ts...>& data, NodeTag* node);
        };
        static constexpr std::array NAMES{
            Pair{nameOf<^^Ts>(), +[](std::variant<Ts...>& data, NodeTag* node) {
                     load<^^Ts>(data.template emplace<Ts>(), node);
                 }}
            ...
        };
        for(auto&& node: *node) {
            for(auto [name, load]: NAMES) {
                if(node->tag() == name)
                    return load(data, node.get());
            }
        }
        logRed("variant {} {} {} {}", node->tag(), NAMES | v::transform(&Pair::name), node->size(), *node | v::transform(&Data::key));
        return;
        // auto begin = r::find_first_of(*node, NAMES, {}, &NodeTag::key, &Pair::name);
        // if(begin == node->end()) {
        //     logRed("variant {} {} {} {}", node->tag(), NAMES | v::transform(&Pair::name), node->size(), *node | v::transform(&Data::key));
        //     return;
        // }
        // if(!node) return;
        // logMagenta("var type {}", NAMES | v::transform(&Pair::name));
        // logYellow("var node {}", *node | v::transform(&Data::key));
        // load(data, node);
    }

    template <meta::info INFO, typename... Ts>
    // requires IsElem<INFO>
    static void load(std::vector<std::variant<Ts...>>& data, NodeTag* node) {

        static const std::unordered_map<string_view, std::variant<Ts...> (*)(NodeTag* node)> loaders{
            {nameOf<^^Ts>(), +[](NodeTag* node) -> std::variant<Ts...> {
                 std::variant<Ts...> tmp{};
                 // load<^^Ts>(tmp, node);
                 load<^^Ts>(tmp.template emplace<Ts>(), node);
                 return tmp;
             }}
            ...
        };

        static constexpr std::array NAMES{nameOf<^^Ts>()...};

        // struct Pair {
        //     string_view name;
        //     std::variant<Ts...> (*func)(NodeTag* node);
        // };
        // static constexpr std::array LOADERS{
        //     Pair{nameOf<^^Ts>(), +[](NodeTag* node) -> std::variant<Ts...> {
        //              Ts tmp;
        //              load<^^Ts>(tmp, node);
        //              return tmp;
        //          }}
        //     ...
        // };
        decltype(std::span{*node}) span;

        if constexpr(IsArr<INFO>) {
            constexpr string_view NAME_OF{nameOf<INFO>()};
            if(node = node->firstChild(NAME_OF); !node) {
                logRed("vec var {} {} {} {}", node->tag(), NAMES, node->size(), *node | v::transform(&Data::key));
                return;
            }
            span = *node;
        } else {
            auto begin = r::find_first_of(*node, NAMES, {}, &NodeTag::key);
            if(begin == node->end()) {
                logRed("vec var {} {} {} {}", node->tag(), NAMES, node->size(), *node | v::transform(&Data::key));
                return;
            }
            span = {begin, node->end()};
        }
        if constexpr(requires { data.clear(); }) data.clear();
        if constexpr(requires { data.reserve(0u); }) data.reserve(span.size());
        for(auto&& node: span) {
            data.emplace_back(loaders.at(node->tag())(node.get()));
            // for(auto [name, load]: LOADERS) {
            //     if(node->tag() == name) {
            //         data.emplace_back(load(node.get()));
            //         break;
            //     }
            // }
        }
        // logGreen("vec var {} {}", data.size(), std::distance(begin, node->end()));
    }

    template <meta::info INFO, typename T>
        requires IsElem<INFO>
    static void load(std::vector<T>& data, NodeTag* node) {
        constexpr string_view NAME_OF{nameOf<^^T>()};
        auto begin = r::find(*node, NAME_OF, &NodeTag::key);
        if(begin == node->end()) return;
        auto end = r::find_last(*node, NAME_OF, &Data::key);
        assert(end.begin() != node->end());
        // logGreen("vector {} {}", NAME_OF, display_string_of(^^T));
        if constexpr(requires { data.resize(0u); }) {
            data.resize(node->size());
            for(auto&& [dst, src]: v::zip(data, std::span{begin, end.begin()}))
                load(dst, src.get());
        } else
            static_assert(false, display_string_of(^^T)); // TODO
    }

    template <meta::info INFO, typename T>
        requires IsArr<INFO>
    static void load(T& data, NodeTag* node) {
        constexpr string_view NAME_OF{nameOf<INFO>()};
        if(node = node->firstChild(NAME_OF); !node) return;
        // logCyan("array {}", NAME_OF);
        if constexpr(requires { data.resize(0u); }) {
            data.resize(node->size());
            for(auto&& [dst, src]: v::zip(data, *node))
                load(dst, src.get());
        } else
            static_assert(false, display_string_of(^^T)); // TODO
    }

    template <meta::info INFO, typename T>
        requires IsRoot<INFO> || ((std::is_class_v<T> || IsElem<INFO>) && !IsRange<T>)
    static void load(T& data, NodeTag* node) {
        constexpr string_view NAME_OF{nameOf<INFO>()};
        if(node->tag() != NAME_OF)
            if(node = node->firstChild(NAME_OF); !node)
                return;
        static_assert(members<T>().size(), display_string_of(^^T));
        template for(constexpr meta::info MEMBER: members<T>())
            load<MEMBER>(data.[:MEMBER:], node);
    }
#endif
};

} // namespace XML
// LXML_END_MODULE_EXPORT
