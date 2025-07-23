#include "mainwindow.h"
#include <QFile>
#include <QRegularExpression>
#include <TopoR_PCB_File.h>
#include <xmlserializer.h>

void MainWindow::edit() {
    QRegularExpression re{"^(G\\d+)|(REL\\S+)$"};
    // QStringList resistors;

    std::map<QString, QStringList> map;
#if 0
    for(auto&& net: file->netList.Nets) {
        if(net.name.contains(re)) {
            qWarning() << net.name;
            for(auto&& ref: net.refs) {
                ref.visit(
                    [&map, &net](const auto& val) {
                        if(val.compName.startsWith('R')
                            || val.compName.startsWith("VT")
                                && !map[val.compName].contains(net.name))
                            map[val.compName].push_back(net.name);
                    });
            }
        }
    }

    for(auto&& [compName, nets]: map) {
        for(auto&& net: file->netList.Nets) {
            for(auto&& ref: net.refs) {
                ref.visit(
                    [&](const PinRef& val) -> void {
                        if(val.compName == compName && val.pinName == "2")
                            map[val.compName].push_back(net.name);
                    },
                    [](const PadRef& val) -> void {
                    });
            }
        }
        qInfo() << compName << nets;
    }

    return;

    auto xml = (Xml::Serializer{""} << *file).toString();

    for(auto&& [compName, nets]: map) {
        assert(nets.size() == 2);
        xml.replace(nets.back(), nets.front());
    }

    for(auto&& [compName, nets]: map)
        file->netList.Nets.erase(std::ranges::find(file->netList.Nets, nets.back(), &NetList::Net::name));

    if(QFile file{"edited.fst"}; file.open(QFile::WriteOnly)) {
        file.write(xml.toUtf8());
    } else
        qWarning() << file.errorString();

    //     for(auto&& resRefDes: resistors) {
    //         auto* comp = file->componentsOnBoard.getComponentOf(resRefDes);
    //         if(!comp) continue;
    //         qWarning() << comp->name;
    //         qWarning() << comp->Pins.size();
    //     }
#endif
}
