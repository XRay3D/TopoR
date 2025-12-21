#include "TopoR_PCB_File.h"
#include <cstdlib>
#include <meta>
#include <thread>
#ifndef LXML_USE_MODULES
#include "lxml.hpp"
#else
import lxml;
#endif

/*
/home/x-ray/Nextcloud/SRC/AMK-310/AMK310_MCU/AMK310_MCU_V2 — копия.fst
/home/x-ray/Nextcloud/SRC/AMK-310/AMK310_MCU/AMK310_MCU_V2.fst
/home/x-ray/Документы/TopoR/Examples/Example_04/Arcs.fst
/home/x-ray/Документы/TopoR/Examples/Example_04/Arcs_standard_routing.fst
/home/x-ray/Nextcloud/HARTMASTER/B0505XT-1WR2.fst
/home/x-ray/Nextcloud/HARTMASTER/HARTMASTER.fst
/home/x-ray/Nextcloud/HARTMASTER/HARTMASTER2.fst
/home/x-ray/Документы/TopoR/Examples/Example_05/MinVia.fst
/home/x-ray/Документы/TopoR/Examples/Example_05/MinVia_standard_routing.fst
/home/x-ray/Документы/TopoR/Examples/Example_02/Placement.fst
/home/x-ray/Документы/TopoR/Examples/Example_02/Placement.fstout.fst
/home/x-ray/Документы/TopoR/Examples/Example_02/Placement_standard_routing.fst
/home/x-ray/Документы/TopoR/Examples/Example_02/Placement_standard_routing.fstout.fst
/home/x-ray/Документы/TopoR/Examples/Example_06/Signals.fst
/home/x-ray/Документы/TopoR/Examples/Example_06/Signals.fstout.fst
/home/x-ray/Документы/TopoR/Examples/Example_01/SingleLayer.fst
/home/x-ray/Документы/TopoR/Examples/Example_03/arz_2L.fst
/home/x-ray/Документы/TopoR/Examples/Example_03/arz_4L.fst
/home/x-ray/Документы/TopoR/Examples/Example_03/arz_standard_routing.fst
/home/x-ray/Nextcloud/SRC/AMK-310/AMK310_MCU/edited.fst


/home/x-ray/Nextcloud/HARTMASTER/B0505XT-1WR2.fst
/home/x-ray/Документы/TopoR/Examples/Example_01/SingleLayer.fst
/home/x-ray/Nextcloud/SRC/AMK-310/AMK310_MCU/AMK310_MCU_V2_PNP.fst
/home/x-ray/Документы/TopoR/Examples/Example_06/Signals.fst
/home/x-ray/Документы/TopoR/Examples/Example_02/Placement_standard_routing.fst
/home/x-ray/Документы/TopoR/Examples/Example_05/MinVia.fst
/home/x-ray/Документы/TopoR/Examples/Example_05/MinVia_standard_routing.fst
/home/x-ray/Документы/TopoR/Examples/Example_04/Arcs_standard_routing.fst
/home/x-ray/Документы/TopoR/Examples/Example_02/Placement.fst
/home/x-ray/Документы/TopoR/Examples/Example_04/Arcs.fst
/home/x-ray/Документы/TopoR/Examples/Example_03/arz_4L.fst
/home/x-ray/Nextcloud/SRC/AMK-310/AMK-310_Soft/AMK_TESTER/AMK_TESTER_ASCII.fst
/home/x-ray/Документы/TopoR/Examples/Example_03/arz_standard_routing.fst
/home/x-ray/Документы/TopoR/Examples/Example_03/arz_2L.fst
/home/x-ray/Nextcloud/HARTMASTER/HARTMASTER.fst
/home/x-ray/Nextcloud/SRC/AMK-310/AMK310_MCU/AMK310_MCU_V1.fst
/home/x-ray/Nextcloud/SRC/AMK-310/AMK310_MCU/AMK310_MCU_V2_POS.fst
/home/x-ray/Nextcloud/SRC/AMK-310/AMK310_MCU/AMK310_MCU_V2.


/home/x-ray/Nextcloud/HARTMASTER/B0505XT-1WR2.fst
/home/x-ray/Nextcloud/HARTMASTER/HARTMASTER.fst
/home/x-ray/Nextcloud/HARTMASTER/HARTMASTER2.fst
/home/x-ray/Nextcloud/SRC/AMK-310/AMK310_MCU/AMK310_MCU_V2 — копия.fst
/home/x-ray/Nextcloud/SRC/AMK-310/AMK310_MCU/AMK310_MCU_V2.fst
/home/x-ray/Nextcloud/SRC/AMK-310/AMK310_MCU/edited.fst
/home/x-ray/projects/qt/TopoR/bin/Debug_Clang/out.fst
/home/x-ray/projects/qt/TopoR/bin/Release_Clang/out.fst
/home/x-ray/projects/qt/TopoR_/bin/Debug_GNU/in.fst
/home/x-ray/projects/qt/TopoR_/bin/Debug_GNU/out.fst
/home/x-ray/projects/qt/TopoR_/bin/Release_GNU/out.fst
/home/x-ray/Документы/TopoR/Examples/Example_01/SingleLayer.fst
/home/x-ray/Документы/TopoR/Examples/Example_02/Placement.fst
/home/x-ray/Документы/TopoR/Examples/Example_02/Placement_standard_routing.fst
/home/x-ray/Документы/TopoR/Examples/Example_03/arz_2L.fst
/home/x-ray/Документы/TopoR/Examples/Example_03/arz_4L.fst
/home/x-ray/Документы/TopoR/Examples/Example_03/arz_standard_routing.fst
/home/x-ray/Документы/TopoR/Examples/Example_04/Arcs.fst
/home/x-ray/Документы/TopoR/Examples/Example_04/Arcs_standard_routing.fst
/home/x-ray/Документы/TopoR/Examples/Example_05/MinVia.fst
/home/x-ray/Документы/TopoR/Examples/Example_05/MinVia_standard_routing.fst
/home/x-ray/Документы/TopoR/Examples/Example_06/Signals.fst


C:/Users/bakiev/Nextcloud/HARTMASTER/HARTMASTER.fst
C:/Users/bakiev/Nextcloud/SRC/AMK-310/AMK310_MCU/AMK310_MCU_V2 — копия.fst
C:/Users/bakiev/Nextcloud/SRC/AMK-310/AMK310_MCU/AMK310_MCU_V2.fst
C:/Users/bakiev/Documents/TopoR/Examples/Example_06/Signals — копия.fst
C:/Users/bakiev/Documents/TopoR/Examples/Example_03/arz_2L.fst
C:/Users/bakiev/Documents/TopoR/Examples/Example_03/arz_standard_routing.fst
C:/Users/bakiev/Nextcloud/SRC/AMK-310/AMK310_MCU/edited.fst
C:/Users/bakiev/Documents/TopoR/Examples/Example_06/Signals.fst
C:/Users/bakiev/Documents/TopoR/Examples/Example_03/arz_4L.fst
C:/Users/bakiev/Documents/TopoR/Examples/Example_04/Arcs.fst
C:/Users/bakiev/Documents/TopoR/Examples/Example_02/Placement.fst
C:/Users/bakiev/Documents/TopoR/Examples/Example_02/Placement_standard_routing.fst
C:/Users/bakiev/Documents/TopoR/Examples/Example_04/Arcs_standard_routing.fst
C:/Users/bakiev/Documents/TopoR/Examples/Example_05/MinVia.fst
C:/Users/bakiev/Documents/TopoR/Examples/Example_05/MinVia_standard_routing.fst
C:/Users/bakiev/AppData/Roaming/Code/User/History/-7b696c37/S3LA.fst
C:/Users/bakiev/Documents/TopoR/Examples/Example_01/SingleLayer.fst
C:/Users/bakiev/AppData/Roaming/Code/User/History/1242cc84/xgDw.fst
C:/Users/bakiev/Новая папка/Untitled2.fst
C:/Users/bakiev/AppData/Roaming/Code/User/History/-279b128c/HTKV.fst
C:/Users/bakiev/Nextcloud/HARTMASTER/B0505XT-1WR2.fst
C:/Users/bakiev/AppData/Roaming/Code/User/History/-6cf00ffa/q4xy.fst
C:/Users/bakiev/AppData/Roaming/Code/User/History/-6cf00ffa/bOUg.fst
C:/Users/bakiev/AppData/Roaming/Code/User/History/-30f33682/Jf3L.fst
C:/Users/bakiev/Nextcloud/HARTMASTER/HARTMASTER2.fst
C:/Users/bakiev/AppData/Roaming/Code/User/History/-30f33682/8QKH.fst
C:/Users/bakiev/Documents/TopoR/Examples/Example_03/arz_2L_.fst


 test.xml
*/

using namespace std ::meta;
using namespace std ::literals;

static constexpr auto CTX = access_context::unchecked();

template <typename T>
void print(const T& str, size_t times = 0, bool field = false);

template <typename... Ts>
void print(const std::variant<Ts...>& variant, size_t times = 0, bool field = 0) {
    variant.visit([=](auto&& arg) { print(arg, times, field); });
}

template <typename T>
void print(const T& str, size_t times, bool field) {
    constexpr size_t INDENT = 2u;
    static constexpr auto CTX = access_context::unchecked();
    const auto indent = XML::v::repeat(' ', INDENT * times);
    const auto indent2 = XML::v::repeat(' ', INDENT * ++times);
    if constexpr(std::is_same_v<T, std::string>) {
        std::println("{}string{}: {}\"{}\"{}", XML::Green, XML::Cancel, XML::Magenta, str, XML::Cancel);
    } else if constexpr(is_arithmetic_type(^^T)) {
        std::println("{}{}{}: {}", XML::Yellow, display_string_of(^^T), XML::Cancel, str);
    } else if constexpr(std::is_enum_v<T>) {
        std::println("{}{}{}: {}", XML::Green, display_string_of(^^T), XML::Cancel, XML::toString(str));
    } else if constexpr(std::ranges::range<T>) {
        if(str.empty()) {
            std::println("{}range{}: []", XML::Green, XML::Cancel);
        } else {
            std::println("{}range{}: [", XML::Green, XML::Cancel);
            for(auto&& var: str) print(var, times);
            std::println("{:s}]", indent);
        }
    } else if constexpr(is_class_type(^^T)) {
        if(!field) std::print("{:s}", indent);
        std::println("{}{}{} {{", XML::Green, display_string_of(^^T), XML::Cancel);
        template for(int i{}; constexpr auto MEMBER: XML::members(^^T)) {
            std::print("{:s}{}{}{} ", indent2, XML::Cyan, display_string_of(MEMBER), XML::Cancel);
            print(str.[:MEMBER:], times, true);
        }
        std::println("{:s}}}", indent);
    }
};

int main() {

    // std::string_view file = "/home/x-ray/Документы/TopoR/Examples/Example_01/SingleLayer.fst";
    // std::string_view file = "/home/x-ray/Документы/TopoR/Examples/Example_02/Placement.fst";
    // std::string_view file = "/home/x-ray/Документы/TopoR/Examples/Example_02/Placement_standard_routing.fst";
    // std::string_view file = "/home/x-ray/Документы/TopoR/Examples/Example_03/arz_2L.fst";
    // std::string_view file = "/home/x-ray/Документы/TopoR/Examples/Example_03/arz_4L.fst";
    // std::string_view file = "/home/x-ray/Документы/TopoR/Examples/Example_03/arz_standard_routing.fst";
    // std::string_view file = "/home/x-ray/Документы/TopoR/Examples/Example_04/Arcs_standard_routing.fst";
    // std::string_view file = "/home/x-ray/Документы/TopoR/Examples/Example_05/MinVia.fst";
    // std::string_view file = "/home/x-ray/Документы/TopoR/Examples/Example_05/MinVia_standard_routing.fst";
    std::string_view file = "/home/x-ray/Документы/TopoR/Examples/Example_04/Arcs.fst";
    // std::string_view file = "/home/x-ray/Nextcloud/HARTMASTER/HARTMASTER.fst";
    // std::string_view file = "C:/Users/bakiev/Nextcloud/HARTMASTER/HARTMASTER.fst";

    XML::Document doc;
#if 0
    if(doc.load(file)) {
        doc.write("out.xml", 4);
        file = "out.xml";
        if(doc.load(file)) {
        }
    }
    //--palette='ad=1;3;38;5;154:de=1;3;38;5;9'
    // system("diff --color -b -B -u /home/x-ray/Nextcloud/HARTMASTER/B0505XT-1WR2.fst out.xml");
    // system(std::format("diff --color -b -B -u {} out.xml", file).c_str());
    // system(std::format("kdiff3 {} out.xml", file).c_str());
#else

    if(!doc.load(file)) return 1;

    doc.write(file = "out.fst", 4);

    TopoR::TopoR_PCB_File topor;

    XML::Serializer{file} >> topor;
    XML::Serializer{file = "out2.fst"} << topor;

    // print(topor);
    system(std::format("diff --color -b -B -u out.fst out2.fst", file).c_str());

    std::this_thread::sleep_for(0.5s);

#endif
    return 0;
}
