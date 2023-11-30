#pragma once

#include <string>
#if 0
template <class T>
void print_names();

inline QString demangle(const std::type_info& ti) {
    int status;
    char* realname;
    realname = abi::__cxa_demangle(ti.name(), NULL, NULL, &status);
    // std::cout << ti.name() << "\t=> " << realname << "\t: " << status << '\n';
    QString ret{realname};
    std::free(realname);
    return ret;
}

static size_t indent{};

template <class Stream, class T, size_t... Is>
inline void print_names_impl(Stream& out, T&& str, std::index_sequence<Is...>) {
    using Ty = std::remove_cvref_t<T>;
    out << QString(indent++ * 4, ' ') << "{\n";
    ((
         out << (Is ? "\n" : ""),
         out << QString(indent * 4, ' '),
         out << pfr::get_name<Is, Ty>(),
         out << '<' << demangle(typeid(pfr::get<Is>(str))) << '>',
         out << " = ",
         out << pfr::get<Is>(str),
         // out << "}",
         out),
        ...);
    out << '\n'
        << QString(--indent * 4, ' ') << "}\n";
}

template <class Stream, class T>
inline void print_names(Stream& out, T&& str) {
    using Ty = std::remove_cvref_t<T>;
    print_names_impl(out,
        std::forward<T>(str),
        std::make_index_sequence<pfr::tuple_size_v<Ty>>{});
}

template <class Stream, class T>
    requires std::is_enum_v<std::remove_cvref_t<T>>
inline Stream& operator<<(Stream& out, T x) {
    return out << underlying_type_t<std::remove_cvref_t<T>>(x);
}

template <class Stream, class T>
    requires(std::is_enum_v<std::remove_cvref_t<T>> == 0
        && std::is_standard_layout_v<std::remove_cvref_t<T>>
        // && std::is_trivial_v<std::remove_cvref_t<T>>
        //
        )
inline Stream& operator<<(Stream& out, T&& str) {
    print_names(out, std::forward<T>(str));
    return out;
}

template <class Stream, class T>
inline Stream& operator<<(Stream& out, T&& str) {
    return out << __PRETTY_FUNCTION__;
}
#endif

class serializer {
public:
    serializer();
};
