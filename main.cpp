#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <set>

QTextStream& operator<<(QTextStream& d, std::string_view sv) {
    return d << QByteArray{sv.data(), static_cast<int>(sv.size())};
}

QDebug operator<<(QDebug d, std::string_view sv) {
    return d.noquote() << QByteArray{sv.data(), static_cast<int>(sv.size())};
}

QDebug operator<<(QDebug d, std::set<QString> c) {
    const bool oldSetting = d.autoInsertSpaces();
    d.nospace() << "set" << '(';
    auto it = c.begin(), end = c.end();
    if(it != end) d << *it++;
    while(it != end) d << ", " << *it++;
    d << ')';
    d.setAutoInsertSpaces(oldSetting);
    return d.maybeSpace();
}

auto messageHandler = qInstallMessageHandler(nullptr);
void myMessageHandler(QtMsgType type, const QMessageLogContext& context, const QString& message) {
    auto file = context.file;
    // if(type == QtInfoMsg) return;
    QMessageLogContext& context_ = const_cast<QMessageLogContext&>(context);
    while(file && *file)
        if(std::set{'/', '\\'}.contains(*file++))
            context_.file = file;

    // QString data{context_.function};
    // data.replace(QRegularExpression(R"((\w+\:\:))"), "");
    // context_.function = data.toUtf8().data();
    messageHandler(type, context, message);
}

int main(int argc, char* argv[]) {
    qInstallMessageHandler(myMessageHandler);
    qSetMessagePattern(QLatin1String(
        "%{if-critical}\x1b[38;2;255;0;0m"
        "C %{endif}"
        "%{if-debug}\x1b[38;2;196;196;196m"
        "D %{endif}"
        "%{if-fatal}\x1b[1;38;2;255;0;0m"
        "F %{endif}"
        "%{if-info}\x1b[38;2;128;255;255m"
        "I %{endif}"
        "%{if-warning}\x1b[38;2;255;128;0m"
        "W %{endif}"
        // "%{time HH:mm:ss.zzz} "
        // "%{appname} %{pid} %{threadid} "
        // "%{type} "
        // "%{file}:%{line} %{function} "
        "%{if-category}%{category}%{endif}%{message} "
        "\x1b[38;2;64;64;64m <- %{function} <- %{file} : %{line}\x1b[0m"));

    QApplication a(argc, argv);
    QApplication::setOrganizationName("XrSoft");
    QApplication::setApplicationName("TopoR_File");

    MainWindow w;
    w.show();
    return a.exec();
}

#include "TopoR_PCB_File.h"
#include "treemodel.h"
#include "ui_mainwindow.h"
#include <QtWidgets>
#include <boost/stacktrace.hpp>

using namespace TopoR;
#include "xmlserializer.h"

void MainWindow::loadFile() {
    Xml::Serializer xml{dir};

    // for(auto&& tk: TopoR::Enumerations::Impl::Tokens<TopoR::Enumerations::Handling>.tokens) {
    //     qInfo() << tk.name.data() << +tk.value;
    // }

    try {
        xml >> *file;
        xml << *file;
        xml.save("out.fst");
    } catch(const std::set<QString>& names) {
        qCritical() << names;
    } catch(const std::exception& ex) {
        qCritical() << ex.what();
        // auto trace = std::stacktrace::current();
        // qCritical() << std::to_string(trace).data();
        auto stacktrace = boost::stacktrace::stacktrace{}.as_vector();
        qCritical() << boost::stacktrace::detail::to_string(stacktrace.data(), stacktrace.size());
        // for(auto&& trace: stacktrace)
        // qCritical() << trace.name() << trace.name();
        // qCritical() << boost::stacktrace::stacktrace();
    } catch(...) {
    }
    // qInfo() << xml.byteArray.data();
    // ui->plainTextEdit->appendPlainText(xml.byteArray);
    ui->plainTextEdit->setLineWrapMode(QPlainTextEdit::NoWrap);

    connect(new QLineEdit{ui->plainTextEdit}, &QLineEdit::textEdited, [this](const QString& str) {
        if(!ui->plainTextEdit->find(str)) {
            ui->plainTextEdit->moveCursor(QTextCursor::Start);
            ui->plainTextEdit->find(str);
        }
    });

    const QStringList headers({tr("Title"), tr("Description")});
    TreeModel* model = new TreeModel{xml.getItem(), headers, this};

    ui->treeView->setModel(model);
    ui->treeView->header()->setSectionResizeMode(QHeaderView::Stretch);
    ui->treeView->header()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui->treeView->header()->setSectionResizeMode(1, QHeaderView::ResizeToContents);

    ui->treeView->expandAll();
    ui->treeView->setAlternatingRowColors(true);
    for(int column = 0; column < model->columnCount(); ++column)
        ui->treeView->resizeColumnToContents(column);
    ui->treeView->collapseAll();

    connect(ui->treeView, &QTreeView::doubleClicked, [this](const QModelIndex& index) {
        ui->treeView->expandRecursively(index, 1);
    });
}
