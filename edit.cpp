#include "mainwindow.h"
#include <QFile>
#include <QRegularExpression>
#include <TopoR_PCB_File.h>
#include <xmlserializer.h>

void MainWindow::edit() {
    QRegularExpression re{"^(G\\d+)|(REL\\S+)$"};
    // QStringList resistors;

    std::map<QString, QStringList> map;

    for(auto&& net: file->netList.Nets) {
        if(net.name.value.contains(re)) {
            qWarning() << net.name;
            for(auto&& ref: net.refs) {
                ref.visit(
                    [&map, &net](const auto& val) {
                        if(val.compName.value.startsWith('R')
                            || val.compName.value.startsWith("VT")
                                && !map[val.compName].contains(net.name.value))
                            map[val.compName].push_back(net.name.value);
                    });
            }
        }
    }

    for(auto&& [compName, nets]: map) {
        for(auto&& net: file->netList.Nets) {
            for(auto&& ref: net.refs) {
                ref.visit(
                    [&](const PinRef& val) -> void {
                        if(val.compName.value == compName && val.pinName.value == "2")
                            map[val.compName].push_back(net.name.value);
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
}

/*
 *
I "R10" ("G2", "NET00283")  <- MainWindow::edit <- edit.cpp : 40
I "R11" ("G3", "NET00279")  <- MainWindow::edit <- edit.cpp : 40
I "R12" ("G4", "NET00284")  <- MainWindow::edit <- edit.cpp : 40
I "R13" ("G5", "NET00280")  <- MainWindow::edit <- edit.cpp : 40
I "R14" ("G6", "NET00285")  <- MainWindow::edit <- edit.cpp : 40
I "R15" ("G7", "NET00281")  <- MainWindow::edit <- edit.cpp : 40
I "R16" ("G8", "NET00282")  <- MainWindow::edit <- edit.cpp : 40
I "R17" ("G9", "NET00322")  <- MainWindow::edit <- edit.cpp : 40
I "R18" ("G10", "NET00320")  <- MainWindow::edit <- edit.cpp : 40
I "R19" ("G11", "NET00324")  <- MainWindow::edit <- edit.cpp : 40
I "R20" ("G12", "NET00317")  <- MainWindow::edit <- edit.cpp : 40
I "R21" ("G13", "NET00315")  <- MainWindow::edit <- edit.cpp : 40
I "R22" ("G14", "NET00314")  <- MainWindow::edit <- edit.cpp : 40
I "R23" ("G15", "NET00312")  <- MainWindow::edit <- edit.cpp : 40
I "R24" ("G16", "NET00310")  <- MainWindow::edit <- edit.cpp : 40
I "R25" ("G17", "NET00361")  <- MainWindow::edit <- edit.cpp : 40
I "R26" ("G18", "NET00359")  <- MainWindow::edit <- edit.cpp : 40
I "R27" ("G19", "NET00363")  <- MainWindow::edit <- edit.cpp : 40
I "R28" ("G20", "NET00356")  <- MainWindow::edit <- edit.cpp : 40
I "R29" ("G21", "NET00354")  <- MainWindow::edit <- edit.cpp : 40
I "R30" ("G22", "NET00352")  <- MainWindow::edit <- edit.cpp : 40
I "R31" ("G23", "NET00351")  <- MainWindow::edit <- edit.cpp : 40
I "R32" ("G24", "NET00349")  <- MainWindow::edit <- edit.cpp : 40
I "R33" ("G25", "NET00400")  <- MainWindow::edit <- edit.cpp : 40
I "R34" ("G26", "NET00398")  <- MainWindow::edit <- edit.cpp : 40
I "R35" ("G27", "NET00403")  <- MainWindow::edit <- edit.cpp : 40
I "R36" ("G28", "NET00395")  <- MainWindow::edit <- edit.cpp : 40
I "R37" ("G29", "NET00393")  <- MainWindow::edit <- edit.cpp : 40
I "R38" ("G30", "NET00391")  <- MainWindow::edit <- edit.cpp : 40
I "R39" ("G31", "NET00390")  <- MainWindow::edit <- edit.cpp : 40
I "R40" ("G32", "NET00388")  <- MainWindow::edit <- edit.cpp : 40
I "R41" ("G33", "NET00440")  <- MainWindow::edit <- edit.cpp : 40
I "R42" ("G34", "NET00438")  <- MainWindow::edit <- edit.cpp : 40
I "R43" ("G35", "NET00442")  <- MainWindow::edit <- edit.cpp : 40
I "R44" ("G36", "NET00435")  <- MainWindow::edit <- edit.cpp : 40
I "R45" ("G37", "NET00433")  <- MainWindow::edit <- edit.cpp : 40
I "R46" ("G38", "NET00431")  <- MainWindow::edit <- edit.cpp : 40
I "R47" ("G39", "NET00430")  <- MainWindow::edit <- edit.cpp : 40
I "R48" ("G40", "NET00428")  <- MainWindow::edit <- edit.cpp : 40
I "R49" ("G41", "NET00479")  <- MainWindow::edit <- edit.cpp : 40
I "R50" ("G42", "NET00477")  <- MainWindow::edit <- edit.cpp : 40
I "R51" ("G43", "NET00482")  <- MainWindow::edit <- edit.cpp : 40
I "R52" ("G44", "NET00474")  <- MainWindow::edit <- edit.cpp : 40
I "R53" ("G45", "NET00472")  <- MainWindow::edit <- edit.cpp : 40
I "R54" ("G46", "NET00470")  <- MainWindow::edit <- edit.cpp : 40
I "R55" ("G47", "NET00469")  <- MainWindow::edit <- edit.cpp : 40
I "R56" ("G48", "NET00467")  <- MainWindow::edit <- edit.cpp : 40
I "R9" ("G1", "NET00278")  <- MainWindow::edit <- edit.cpp : 40

I "VT1" ("REL_IN_MV", "REL_IN_V", "NET00278")  <- MainWindow::edit <- edit.cpp : 40
I "VT10" ("REL_R5", "REL_R6", "NET00363")  <- MainWindow::edit <- edit.cpp : 40
I "VT11" ("REL_R8", "REL_R7", "NET00354")  <- MainWindow::edit <- edit.cpp : 40
I "VT12" ("REL_R4W", "REL_R3W", "NET00351")  <- MainWindow::edit <- edit.cpp : 40
I "VT13" ("REL_N400R", "REL_N0R", "NET00400")  <- MainWindow::edit <- edit.cpp : 40
I "VT14" ("REL_N500R", "REL_N1K", "NET00403")  <- MainWindow::edit <- edit.cpp : 40
I "VT15" ("REL_N2K", "REL_NXX", "NET00393")  <- MainWindow::edit <- edit.cpp : 40
I "VT16" ("REL_N20MA", "REL_N5MA", "NET00390")  <- MainWindow::edit <- edit.cpp : 40
I "VT17" ("REL_HART_1", "REL_HART_2", "NET00440")  <- MainWindow::edit <- edit.cpp : 40
I "VT18" ("REL_HART_3", "REL_HART_4", "NET00442")  <- MainWindow::edit <- edit.cpp : 40
I "VT19" ("REL_HART_5", "REL_HART_6", "NET00433")  <- MainWindow::edit <- edit.cpp : 40
I "VT2" ("REL_IN_MA", "REL_INV", "NET00279")  <- MainWindow::edit <- edit.cpp : 40
I "VT20" ("REL_HART_7", "REL_HART_8", "NET00430")  <- MainWindow::edit <- edit.cpp : 40
I "VT21" ("REL_HART_9", "REL_HART_10", "NET00479")  <- MainWindow::edit <- edit.cpp : 40
I "VT22" ("REL_HART_11", "REL_HART_12", "NET00482")  <- MainWindow::edit <- edit.cpp : 40
I "VT3" ("REL_MV1", "REL_MV2", "NET00280")  <- MainWindow::edit <- edit.cpp : 40
I "VT4" ("REL_MV_TC", "REL_V_NEW", "NET00281")  <- MainWindow::edit <- edit.cpp : 40
I "VT5" ("REL_V_OLD", "REL_MA", "NET00322")  <- MainWindow::edit <- edit.cpp : 40
I "VT6" ("REL_RESERVE1", "REL_RESERVE2", "NET00324")  <- MainWindow::edit <- edit.cpp : 40
I "VT7" ("REL_RESERVE4", "REL_RESERVE3", "NET00315")  <- MainWindow::edit <- edit.cpp : 40
I "VT8" ("REL_R1", "REL_R2", "NET00312")  <- MainWindow::edit <- edit.cpp : 40
I "VT9" ("REL_R3", "REL_R4", "NET00361")  <- MainWindow::edit <- edit.cpp : 40

*/
