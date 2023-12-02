#pragma once

#include <QBuffer>
#include <QDebug>
#include <QDomDocument>
#include <set>
#include <source_location>
#include <stack>

using sl = std::source_location;

QTextStream& operator<<(QTextStream& d, std::string_view sv);

QDebug operator<<(QDebug d, std::string_view sv);

QDebug operator<<(QDebug d, std::set<QString> c);

struct Xml {
    QDomDocument doc{"mydocument"};

    Xml(const QString& name = "../МАН2_МСИС_V2.1.fst");
    //~Xml() { qCritical() << byteArray; }
    QDomElement top() const;

    bool push(sl sl_ = sl::current());

    void push(const QDomNode& node, sl sl_ = sl::current());

    void pop(sl sl_ = sl::current());

    auto value(sl sl_ = sl::current()) -> QString;

    std::set<QString> names;
    bool isAttr{};
    bool skipPushArray{};
    bool skipPop{};
    bool isptional{};
    bool hasValue{};

    bool loging{0};

    template <typename T>
    void read(T* val);

    QByteArray byteArray;
    QBuffer buffer{&byteArray};
    QTextStream out{&buffer};

    std::stack<QDomNode> stack;
};
