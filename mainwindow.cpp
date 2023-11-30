#include "mainwindow.h"
#include "TopoR_PCB_File.h"
#include "pfr.hpp"
#include <QTextStream>
#include <iostream>
#include <string>

#if __has_include(<cxxabi.h>)
#include <cxxabi.h>
inline QString demangle(const std::type_info& ti) {
    int status;
    char* const realname = abi::__cxa_demangle(ti.name(), NULL, NULL, &status);
    char* type1{realname};
    char* type2{};
    // while (*type1)
    //     if (*type1++ == ':') type2 = type1;
    // std::cout << ti.name() << "\t=> " << realname << "\t: " << status << '\n';
    QString ret{(type2 && *type2) ? type2 : realname};
    std::free(realname);
    return ret;
}
#else
inline QString demangle(const std::type_info& ti) {
    QString ret{ti.name()};
    return ret;
}
#endif

namespace TopoR_PCB_Classes {

template <class T>
void print_names();

static size_t indent{};

template <size_t Is, class Stream, class T>
inline void print_name_impl(Stream& out, T& str) {
    if (Is) out << "\n";
    out << QString(indent * 4, ' ').toStdString();
    out << pfr::get_name<Is, T>();
    out << '<' << demangle(typeid(pfr::get<Is>(str))).toStdString() << '>';
    out << " = ";
    out << pfr::get<Is>(str);
    // out << "}";
}

template <class Stream, class T, size_t... Is>
inline void print_names_impl(Stream& out, T& str, std::index_sequence<Is...>) {
    using Ty = T;
    indent++;
    out << demangle(typeid(T)).toStdString() << "{\n";
    (print_name_impl<Is>(out, str), ...);
    out << '\n'
        << QString(--indent * 4, ' ') << "}\n";
}

// template <class Stream, class T>
// inline void print_names(Stream& out, T& str) {
//     using Ty = T;
//     if (str)
//         print_names_impl(out, str.value(), std::make_index_sequence<pfr::tuple_size_v<Ty>>{});
// }

template <class Stream, class T>
inline void print_names(Stream& out, std::vector<T>& str) {
    using Ty = T;
    // if (str)
    // print_names_impl(out, str.value(), std::make_index_sequence<pfr::tuple_size_v<Ty>>{});
}

template <class Stream, class T>
inline void print_names(Stream& out, T& str) {
    using Ty = T;
    print_names_impl(out, str, std::make_index_sequence<pfr::tuple_size_v<Ty>>{});
}

// template <class Stream, class T>
//     requires(std::is_enum_v<T> == 0 && std::is_standard_layout_v<T> /*&& std::is_trivial_v<T>*/)
// inline Stream& operator<<(Stream& out, T& str) {
//     if (str)
//         print_names(out, str.value());
//     return out;
// }

template <class Stream, class T>
    requires std::is_enum_v<T>
inline Stream& operator<<(Stream& out, T x) {
    return out << std::underlying_type_t<T>(x);
}

template <class Stream, class T>
    requires(std::is_enum_v<T> == 0 && std::is_standard_layout_v<T> /*&& std::is_trivial_v<T>*/)
inline Stream& operator<<(Stream& out, T& str) {
    print_names(out, str);
    return out;
}

// template <class Stream, class T>
// inline Stream& operator<<(Stream& out, T& str) {
//     return out << __PRETTY_FUNCTION__;
//     // return out << __FUNCSIG__;
// }

struct Str2 {
    int field{};
};

struct Str {
    Str2 field1{2};
    Str2 field2{};
} str;

} // namespace TopoR_PCB_Classes

template <class Stream, class T>
inline Stream& operator<<(Stream& out, std::vector<T> v) {
    for (auto&& val: v)
        out << val;
    return out;
}

template <class Stream>
inline Stream& operator<<(Stream& out, const QString& str) {
    return out << str.toStdString();
}

// D:\Junk_Yard\PRO\QT\Elemer\MAN\MAN_ElekrtoSila\МАН2_SCH_PCB\V2\МАН2_МСИС_V2.1.fsx

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow{parent} {

    TopoR_PCB_Classes::TopoR_PCB_File file;
    /*
        QByteArray data;
        QTextStream stream{data};
        stream << file;
    */
    // std::cout << data.data();
    std::cout << file;

    for (auto&& [name, val]: TopoR_PCB_Classes::Impl::Tokens<TopoR_PCB_Classes::align>) {
        std::cout << name << " = " << val << '\n';
    }

    for (auto&& [whole, name, var]: ctre::range<R"((\w+)(?: = (\w+))?,?)">("CM, LT = 10, CT, RT, LM, RM = 0x10, LB, CB, RB = FF")) {
        // if (var) val = to_num<T>(var);
        // tokens[count++] = {name, static_cast<T>(val++)};

        std::cout << "{" << name.to_view();
        std::cout << "},{" << var.to_view() << "}\n";
    }

    exit(0);
}

MainWindow::~MainWindow() { }
