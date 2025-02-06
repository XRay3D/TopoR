#pragma once
#include "Commons.h"
#include <memory>
#include <optional>
#include <string>
#include <vector>
/* Мною, Константином aka KilkennyCat, 05 июля 2020 года создано сиё
 * на основе "Описание формата TopoR PCB версия 1.2.0 Апрель 2017 г.".
 * k@kilkennycat.pro
 * http://kilkennycat.ru  http://kilkennycat.pro
 */
namespace TopoR {
// Раздел «Настройки диалогов».
struct DialogSettings {
    // Настройки DRC.
    struct DRCSettings {
        Xml::Attr<Bool> checkClearances;   // Настройка DRC: проверка зазоров.
        Xml::Attr<Bool> checkNetIntegrity; // Настройка DRC: проверка целостности цепей.
        Xml::Attr<Bool> checkNetWidth;     // Настройка DRC: проверка ширины проводников.
        Xml::Attr<Bool> copperToBoard;     // Настройка DRC: проверять зазор между полигонами и краем платы.
        Xml::Attr<Bool> copperToCopper;    // Настройка DRC: проверять зазор между полигонами.
        Xml::Attr<Bool> copperToKeepout;   // Настройка DRC: проверять зазор между полигонами и запретами.
        Xml::Attr<Bool> copperToPad;       // Настройка DRC: проверять зазор между полигонами и контактными площадками.
        Xml::Attr<Bool> copperToVia;       // Настройка DRC: проверять зазор между полигонами и переходными отверстиями.
        Xml::Attr<Bool> copperToWire;      // Настройка DRC: проверять зазор между полигонами и проводниками.
        Xml::Attr<Bool> createLog;         // Настройка DRC: выводить отчёт в указанный файл.
        Xml::Attr<Bool> padToBoard;        // Настройка DRC: проверка зазоров между контактными площадками и краем платы.
        Xml::Attr<Bool> padToKeepout;      // Настройка DRC: проверка зазоров между контактными площадками и запретами.
        Xml::Attr<Bool> padToPad;          // Настройка DRC: проверка зазоров между контактными площадками.
        Xml::Attr<Bool> textToBoard;       // Настройка DRC: проверять зазоры от надписей до края платы.
        Xml::Attr<Bool> textToCopper;      // Настройка DRC: проверять зазоры между надписями и областями металлизации (полигонами).
        Xml::Attr<Bool> textToKeepout;     // Настройка DRC: проверять зазоры между надписями и запретами.
        Xml::Attr<Bool> textToPad;         // Настройка DRC: проверять зазоры между надписями и контактными площадками.
        Xml::Attr<Bool> textToVia;         // Настройка DRC: проверять зазоры между надписями и переходными отверстиями.
        Xml::Attr<Bool> textToWire;        // Настройка DRC: проверять зазоры между надписями и проводниками.
        Xml::Attr<Bool> viaToBoard;        // Настройка DRC: проверять зазоры от переходных отверстий до края платы.
        Xml::Attr<Bool> viaToKeepout;      // Настройка DRC: проверять зазоры между переходными отверстиями и запретами.
        Xml::Attr<Bool> viaToPad;          // Настройка DRC: проверять зазоры между переходными отверстиями и контактными площадками.
        Xml::Attr<Bool> viaToVia;          // Настройка DRC: проверять зазоры между переходными отверстиями.
        Xml::Attr<Bool> wireToBoard;       // Настройка DRC: проверять зазоры от проводников до края платы.
        Xml::Attr<Bool> wireToKeepout;     // Настройка DRC: проверять зазоры между проводниками и запретами.
        Xml::Attr<Bool> wireToPad;         // Настройка DRC: проверять зазоры между проводниками и контактными площадками.
        Xml::Attr<Bool> wireToVia;         // Настройка DRC: проверять зазоры между проводниками и переходными отверстиями.
        Xml::Attr<Bool> wireToWire;        // Настройка DRC: проверять зазоры между проводниками.
        Xml::Attr<QString> logFileName;    // Настройка DRC: файл для вывода отчета.
        Xml::Attr<double> tolerance;       // Настройка DRC: допуск.
        Xml::Attr<int> messageLimit;       // Настройка DRC: максимальное количество сообщений.
    };
    // Настройки вывода файлов Gerber.
    struct GerberSettings {
        // Настройки вывода файла Gerber.
        struct ExportFile {
            // Настройка экспорта Gerber файлов: список экспортируемых объектов для слоя.
            struct ExportObjects {
                // Настройка вывода файла Gerber: выводить контур платы.
                // [Xml::Attribute("board")] public Bool board_;
                Xml::Attr<Bool> board;
                // Настройка вывода файлов Geber, DXF: выводить проводники.
                // [Xml::Attribute("wires")] public Bool wires_;
                Xml::Attr<Bool> wires;
                // Настройка вывода файлов Gerber, DXF: выводить области металлизации (полигоны).
                // [Xml::Attribute("coppers")] public Bool coppers_;
                Xml::Attr<Bool> coppers;
                // Настройка вывода файлов Gerber, DXF: выводить контактные площадки.
                // [Xml::Attribute("padstacks")] public Bool padstacks_;
                Xml::Attr<Bool> padstacks;
                // Настройка вывода файлов Gerber, DXF: выводить переходные отверстия.
                // [Xml::Attribute("vias")] public Bool vias_;
                Xml::Attr<Bool> vias;
                // Настройка вывода файлов Gerber и DXF: выводить надписи.
                // [Xml::Attribute("texts")] public Bool texts_;
                Xml::Attr<Bool> texts;
                // Настройка вывода файлов Gerber, DXF: выводить ярлыки.
                // [Xml::Attribute("labels")] public Bool labels_;
                Xml::Attr<Bool> labels;
                // Настройка вывода файлов Gerber: выводить детали на механических слоях.
                // [Xml::Attribute("details")] public Bool details_;
                Xml::Attr<Bool> details;
                // Настройка вывода файлов Gerber, DXF: выводить реперные знаки.
                /// \note !В TopoR реперные знаки не поддерживаются.</ remarks>
                // [Xml::Attribute("fiducials")] public Bool fiducials_;
                Xml::Attr<Bool> fiducials;
            };
            // Имя экспортируемого файла Gerber, Drill.
            /// \note !Имя не должно содержать путь к файлу.</ remarks>
            // [Xml::Attribute("fileName")] public string fileName_;
            Xml::Attr<QString> fileName;
            // Настройка вывода файла Gerber: выводить файл.
            // [Xml::Attribute("output")] public Bool output_;
            Xml::Attr<Bool> output;
            // Настройка вывода файла Gerber: вывод слоя в зеркальном отображении.
            // [Xml::Attribute("mirror")] public Bool mirror_;
            Xml::Attr<Bool> mirror;
            // Настройка вывода файлов Gerber: инверсный вывод слоя.
            // [Xml::Attribute("negative")] public Bool negative_;
            Xml::Attr<Bool> negative;
            // Ссылка на слой.
            // [Xml::Element("LayerRef")] public LayerRef layerRef;
            LayerRef layerRef;
            // Настройка экспорта Gerber файлов: список экспортируемых объектов для слоя.
            // [Xml::Element("ExportObjects")] public ExportObjects ExportObjects_;
            ExportObjects ExportObjects_;
            // Настройка вывода файла Gerber: смещение объектов по осям x и y.
            // [Xml::Element("Shift")] public Shift shift;
            Shift shift;
        };
        // Каталог для выходных файлов (Gerber, Drill).
        // [Xml::Attribute("outPath")] public string outPath_;
        Xml::Attr<QString> outPath;
        // Настройка вывода файлов Gerber, DXF, Drill: единицы измерения.
        // [Xml::Attribute("units")] public units units_;
        Xml::Attr<units, NoOpt> units_;
        // Настройка вывода чисел в файлы Gerber, Drill: количество цифр перед запятой.
        // [Xml::Attribute("intNums", DataType = "int")] public int intNums_;
        Xml::Attr<int> intNums;
        // Настройка вывода чисел в файлы Gerber, Drill: количество цифр после запятой.
        // [Xml::Attribute("fractNums", DataType = "int")] public int fractNums_;
        Xml::Attr<int> fractNums;
        // Настройки вывода файлов Gerber.
        // [Xml::Element("ExportFile")] public List<ExportFile_GerberSettings> ExportFiles_;
        Xml::Array<ExportFile> ExportFiles;
    };
    // Настройки вывода файла DXF.
    struct DXFSettings {
        // Настройки вывода слоя в файл DXF.
        struct ExportLayer {
            // Настройка экспорта слоя в файл DXF: список экспортируемых объектов для слоя.
            struct ExportObjects {
                // Настройка вывода файлов Geber, DXF: выводить проводники.
                // [Xml::Attribute("wires")] public Bool wires_;
                Xml::Attr<Bool> wires;
                // Настройка вывода файлов Gerber, DXF: выводить области металлизации (полигоны).
                // [Xml::Attribute("coppers")] public Bool coppers_;
                Xml::Attr<Bool> coppers;
                // Настройка вывода файлов Gerber, DXF: выводить контактные площадки.
                // [Xml::Attribute("padstacks")] public Bool padstacks_;
                Xml::Attr<Bool> padstacks;
                // Настройка вывода файлов Gerber, DXF: выводить переходные отверстия.
                // [Xml::Attribute("vias")] public Bool vias_;
                Xml::Attr<Bool> vias;
                // Настройка вывода файлов Gerber и DXF: выводить надписи.
                // [Xml::Attribute("texts")] public Bool texts_;
                Xml::Attr<Bool> texts;
                // Настройка вывода файлов Gerber, DXF: выводить ярлыки.
                // [Xml::Attribute("labels")] public Bool labels_;
                Xml::Attr<Bool> labels;
                // Настройка вывода файлов Gerber: выводить детали на механических слоях.
                // [Xml::Attribute("details")] public Bool details_;
                Xml::Attr<Bool> details;
                // Настройка вывода слоя в файл DXF: выводить очертания компонентов.
                // [Xml::Attribute("compsOutline")] public Bool compsOutline_;
                Xml::Attr<Bool> compsOutline;
                // Настройка вывода файлов Gerber, DXF: выводить реперные знаки.
                /// \note !В TopoR реперные знаки не поддерживаются.</ remarks>
                // [Xml::Attribute("fiducials")] public Bool fiducials_;
                Xml::Attr<Bool> fiducials;
            };
            // Настройка вывода слоя в файл DXF: выводить слой.
            // [Xml::Attribute("output")] public Bool output_;
            Xml::Attr<Bool> output;
            // Ссылка на слой.
            // [Xml::Element("LayerRef")] public LayerRef layerRef;
            LayerRef layerRef;
            // Настройка экспорта слоя в файл DXF: список экспортируемых объектов для слоя.
            // [Xml::Element("ExportObjects")] public ExportObjects ExportObjects_;
            ExportObjects ExportObjects_;
        };
        // Имя выходного файла (ВОМ, DXF).
        // [Xml::Attribute("outFile")] public string outFile_;
        Xml::Attr<QString> outFile;
        // Настройка вывода файлов Gerber, DXF, Drill: единицы измерения.
        // [Xml::Attribute("units")] public units units_;
        Xml::Attr<units> units_;
        // Настройка вывода файла DXF: выводить слой с контуром платы.
        // [Xml::Attribute("outputBoardLayer")] public Bool outputBoardLayer_;
        Xml::Attr<Bool> outputBoardLayer;
        // Настройка вывода файла DXF: выводить слой отверстий.
        // [Xml::Attribute("outputDrillLayer")] public Bool outputDrillLayer_;
        Xml::Attr<Bool> outputDrillLayer;
        // Настройки вывода слоя в файл DXF.
        // [Xml::Element("ExportLayer")] public List<ExportLayer> ExportLayers_;
        Xml::ArrayElem<ExportLayer> ExportLayers;
    };
    // Настройки вывода файлов Drill.
    struct DrillSettings {
        // Настройки вывода файла Gerber.
        struct ExportFile {
            // Имя экспортируемого файла Gerber, Drill.
            /// \note !Имя не должно содержать путь к файлу.</ remarks>
            // [Xml::Attribute("fileName")] public string fileName_;
            Xml::Attr<QString> fileName;
        };
        // Каталог для выходных файлов (Gerber, Drill).
        // [Xml::Attribute("outPath")] public string outPath_;
        Xml::Attr<QString> outPath;
        // Настройка вывода файлов Gerber, DXF, Drill: единицы измерения.
        // [Xml::Attribute("units")] public units units_;
        Xml::Attr<units, NoOpt> units_;
        // Настройка вывода чисел в файлы Gerber, Drill: количество цифр перед запятой.
        // [Xml::Attribute("intNums", DataType = "int")] public int intNums_;
        Xml::Attr<int> intNums;
        // Настройка вывода чисел в файлы Gerber, Drill: количество цифр после запятой.
        // [Xml::Attribute("fractNums", DataType = "int")] public int fractNums_;
        Xml::Attr<int> fractNums;
        // Настройки вывода файлов Gerber.
        // [Xml::Element("ExportFile")] public List<ExportFile_DrillSettings> ExportFiles_;
        Xml::Array<ExportFile> ExportFiles;
    };
    // Настройки вывода BOM файла.
    struct BOMSettings {
        // Имя выходного файла (ВОМ, DXF).
        // [Xml::Attribute("outFile")] public string outFile_;
        Xml::Attr<QString, NoOpt> outFile;
        // Настройка диалога вывода BOM файла: выводить количество компонентов.
        // [Xml::Attribute("count")] public Bool count_;
        Xml::Attr<Bool> count;
        // Настройка вывода BOM файла: выводить наименование компонентов.
        // [Xml::Attribute("partName")] public Bool partName_;
        Xml::Attr<Bool> partName;
        // Настройка вывода BOM файла: выводить наименование посадочных мест.
        // [Xml::Attribute("footprint")] public Bool footprint_;
        Xml::Attr<Bool> footprint;
        // Настройка вывода BOM файла: выводить позиционные обозначения компонентов.
        // [Xml::Attribute("refDes")] public Bool refDes_;
        Xml::Attr<Bool> refDes;
        // Ссылка на атрибут.
        // [Xml::Element("AttributeRef")] public List<AttributeRef> AttributeRefs_;
        Xml::ArrayElem<AttributeRef> AttributeRefs;
    };
    // Настройка фильтра сообщений.
    struct MessageFilter {
        Xml::Attr<Bool> W5003; // Настройка фильтра сообщений: выводить сообщение 5003.
        Xml::Attr<Bool> W5012; // Настройка фильтра сообщений: выводить сообщение 5012.
        Xml::Attr<Bool> W5013; // Настройка фильтра сообщений: выводить сообщение 5013.
        Xml::Attr<Bool> W5014; // Настройка фильтра сообщений: выводить сообщение 5014.
        Xml::Attr<Bool> W5015; // Настройка фильтра сообщений: выводить сообщение 5015.
        Xml::Attr<Bool> W5016; // Настройка фильтра сообщений: выводить сообщение 5016.
        Xml::Attr<Bool> W5017; // Настройка фильтра сообщений: выводить сообщение 5017.
        Xml::Attr<Bool> W5018; // Настройка фильтра сообщений: выводить сообщение 5018.
        Xml::Attr<Bool> W5023; // Настройка фильтра сообщений: выводить сообщение 5023.
        Xml::Attr<Bool> W5024; // Настройка фильтра сообщений: выводить сообщение 5024.
        Xml::Attr<Bool> W5026; // Настройка фильтра сообщений: выводить сообщение 5026.
        Xml::Attr<Bool> W5034; // Настройка фильтра сообщений: выводить сообщение 5034.
        Xml::Attr<Bool> W5036; // Настройка фильтра сообщений: выводить сообщение 5036.
        Xml::Attr<Bool> W5037; // Настройка фильтра сообщений: выводить сообщение 5037.

        Xml::Attr<Bool> WClrnBtwComps;         // Настройка фильтра сообщений: быстрая проверка зазоров между компонентами.
        Xml::Attr<Bool> WClrnBtwObjSameNet;    // Настройка фильтра сообщений: быстрая проверка зазоров между объектами одной цепи.
        Xml::Attr<showWarnings> showWarnings_; // Настройка фильтра сообщений: режим показа предупреждений.
    };
    // Версия раздела.
    // [Xml::Attribute("version")] public string version_;
    Xml::Attr<QString> version;
    // Настройки DRC.
    // [Xml::Element("DRCSettings")] public DRCSettings dRCSettings;
    Xml::Optional<DRCSettings> dRCSettings;
    // Настройки вывода файлов Gerber.
    // [Xml::Element("GerberSettings")] public GerberSettings gerberSettings;
    Xml::Optional<GerberSettings> gerberSettings;
    // Настройки вывода файла DXF.
    // [Xml::Element("DXFSettings")] public DXFSettings dXFSettings;
    Xml::Optional<DXFSettings> dXFSettings;
    // Настройки вывода файлов Drill.
    // [Xml::Element("DrillSettings")] public DrillSettings drillSettings;
    Xml::Optional<DrillSettings> drillSettings;
    // Настройки вывода BOM файла.
    // [Xml::Element("BOMSettings")] public BOMSettings bOMSettings;
    Xml::Optional<BOMSettings> bOMSettings;
    // Настройка фильтра сообщений.
    // [Xml::Element("MessagesFilter")] public MessagesFilter messagesFilter;
    Xml::Optional<MessageFilter> messageFilter;
    /**************************************************************************
     * Здесь находятся функции для работы с элементами класса DialogSettings. *
     * Они не являются частью формата TopoR PCB.                              *
     * ************************************************************************/
};
} // namespace TopoR
