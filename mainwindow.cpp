#include "mainwindow.h"
#include "TopoR_PCB_File.h"
#include "pfr.hpp"
#include <cxxabi.h>
#include <iostream>

template <class T>
void print_names();

std::string demangle(const std::type_info& ti) {
    int status;
    char* realname;
    realname = abi::__cxa_demangle(ti.name(), NULL, NULL, &status);
    // std::cout << ti.name() << "\t=> " << realname << "\t: " << status << '\n';
    std::string ret{realname};
    std::free(realname);
    return ret;
}

static size_t indent{};

template <class Stream, class T, size_t... Is>
void print_names_impl(Stream&& out, T&& str, std::index_sequence<Is...>) {
    using Ty = std::remove_cvref_t<T>;
    out << std::string(indent++ * 4, ' ') << "{\n";
    ((out << (Is ? "\n" : "")
          << std::string(indent * 4, ' ')
          << pfr::get_name<Is, Ty>()
          << '<' << demangle(typeid(pfr::get<Is>(str))) << '>'
          << " = " << pfr::get<Is>(str)
         //<< "}"
         ),
        ...);
    out << '\n'
        << std::string(--indent * 4, ' ') << "}\n";
}

template <class Stream, class T>
void print_names(Stream&& out, T&& str) {
    using Ty = std::remove_cvref_t<T>;
    print_names_impl(
        std::forward<Stream>(out),
        std::forward<T>(str),
        std::make_index_sequence<pfr::tuple_size_v<Ty>>{});
}

template <class Stream, class T>
    requires std::is_enum_v<std::remove_cvref_t<T>>
Stream& operator<<(Stream& out, T x) {
    return out << underlying_type_t<std::remove_cvref_t<T>>(x);
}

template <class Stream, class T>
    requires(std::is_enum_v<std::remove_cvref_t<T>> == 0) // && std::is_standard_layout_v<std::remove_cvref_t<T>>)
Stream& operator<<(Stream&& out, T&& str) {
    print_names(std::forward<Stream>(out), std::forward<T>(str));
    return out;
}

template <class Stream, class T>
Stream& operator<<(Stream&& out, std::optional<T>& str) {
    if(str) out << str.value();
    return out;
}

template <class Stream, class T>
Stream& operator<<(Stream&& out, T* str) {
    if(str) out << *str;
    return out;
}

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow{parent} {

    TopoR_PCB_Classes ::TopoR_PCB_File file;
    std::cout << file << std::endl;

    exit(0);
}

MainWindow::~MainWindow() { }
