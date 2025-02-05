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
        XmlAttr<Bool> checkClearances;   // Настройка DRC: проверка зазоров.
        XmlAttr<Bool> checkNetIntegrity; // Настройка DRC: проверка целостности цепей.
        XmlAttr<Bool> checkNetWidth;     // Настройка DRC: проверка ширины проводников.
        XmlAttr<Bool> copperToBoard;     // Настройка DRC: проверять зазор между полигонами и краем платы.
        XmlAttr<Bool> copperToCopper;    // Настройка DRC: проверять зазор между полигонами.
        XmlAttr<Bool> copperToKeepout;   // Настройка DRC: проверять зазор между полигонами и запретами.
        XmlAttr<Bool> copperToPad;       // Настройка DRC: проверять зазор между полигонами и контактными площадками.
        XmlAttr<Bool> copperToVia;       // Настройка DRC: проверять зазор между полигонами и переходными отверстиями.
        XmlAttr<Bool> copperToWire;      // Настройка DRC: проверять зазор между полигонами и проводниками.
        XmlAttr<Bool> createLog;         // Настройка DRC: выводить отчёт в указанный файл.
        XmlAttr<Bool> padToBoard;        // Настройка DRC: проверка зазоров между контактными площадками и краем платы.
        XmlAttr<Bool> padToKeepout;      // Настройка DRC: проверка зазоров между контактными площадками и запретами.
        XmlAttr<Bool> padToPad;          // Настройка DRC: проверка зазоров между контактными площадками.
        XmlAttr<Bool> textToBoard;       // Настройка DRC: проверять зазоры от надписей до края платы.
        XmlAttr<Bool> textToCopper;      // Настройка DRC: проверять зазоры между надписями и областями металлизации (полигонами).
        XmlAttr<Bool> textToKeepout;     // Настройка DRC: проверять зазоры между надписями и запретами.
        XmlAttr<Bool> textToPad;         // Настройка DRC: проверять зазоры между надписями и контактными площадками.
        XmlAttr<Bool> textToVia;         // Настройка DRC: проверять зазоры между надписями и переходными отверстиями.
        XmlAttr<Bool> textToWire;        // Настройка DRC: проверять зазоры между надписями и проводниками.
        XmlAttr<Bool> viaToBoard;        // Настройка DRC: проверять зазоры от переходных отверстий до края платы.
        XmlAttr<Bool> viaToKeepout;      // Настройка DRC: проверять зазоры между переходными отверстиями и запретами.
        XmlAttr<Bool> viaToPad;          // Настройка DRC: проверять зазоры между переходными отверстиями и контактными площадками.
        XmlAttr<Bool> viaToVia;          // Настройка DRC: проверять зазоры между переходными отверстиями.
        XmlAttr<Bool> wireToBoard;       // Настройка DRC: проверять зазоры от проводников до края платы.
        XmlAttr<Bool> wireToKeepout;     // Настройка DRC: проверять зазоры между проводниками и запретами.
        XmlAttr<Bool> wireToPad;         // Настройка DRC: проверять зазоры между проводниками и контактными площадками.
        XmlAttr<Bool> wireToVia;         // Настройка DRC: проверять зазоры между проводниками и переходными отверстиями.
        XmlAttr<Bool> wireToWire;        // Настройка DRC: проверять зазоры между проводниками.
        XmlAttr<QString> logFileName;    // Настройка DRC: файл для вывода отчета.
        XmlAttr<double> tolerance;       // Настройка DRC: допуск.
        XmlAttr<int> messageLimit;       // Настройка DRC: максимальное количество сообщений.
    };
    // Настройки вывода файлов Gerber.
    struct GerberSettings {
        // Настройки вывода файла Gerber.
        struct ExportFile {
            // Настройка экспорта Gerber файлов: список экспортируемых объектов для слоя.
            struct ExportObjects {
                // Настройка вывода файла Gerber: выводить контур платы.
                // [XmlAttribute("board")] public Bool board_;
                XmlAttr<Bool> board;
                // Настройка вывода файлов Geber, DXF: выводить проводники.
                // [XmlAttribute("wires")] public Bool wires_;
                XmlAttr<Bool> wires;
                // Настройка вывода файлов Gerber, DXF: выводить области металлизации (полигоны).
                // [XmlAttribute("coppers")] public Bool coppers_;
                XmlAttr<Bool> coppers;
                // Настройка вывода файлов Gerber, DXF: выводить контактные площадки.
                // [XmlAttribute("padstacks")] public Bool padstacks_;
                XmlAttr<Bool> padstacks;
                // Настройка вывода файлов Gerber, DXF: выводить переходные отверстия.
                // [XmlAttribute("vias")] public Bool vias_;
                XmlAttr<Bool> vias;
                // Настройка вывода файлов Gerber и DXF: выводить надписи.
                // [XmlAttribute("texts")] public Bool texts_;
                XmlAttr<Bool> texts;
                // Настройка вывода файлов Gerber, DXF: выводить ярлыки.
                // [XmlAttribute("labels")] public Bool labels_;
                XmlAttr<Bool> labels;
                // Настройка вывода файлов Gerber: выводить детали на механических слоях.
                // [XmlAttribute("details")] public Bool details_;
                XmlAttr<Bool> details;
                // Настройка вывода файлов Gerber, DXF: выводить реперные знаки.
                /// \note !В TopoR реперные знаки не поддерживаются.</ remarks>
                // [XmlAttribute("fiducials")] public Bool fiducials_;
                XmlAttr<Bool> fiducials;
            };
            // Имя экспортируемого файла Gerber, Drill.
            /// \note !Имя не должно содержать путь к файлу.</ remarks>
            // [XmlAttribute("fileName")] public string fileName_;
            XmlAttr<QString> fileName;
            // Настройка вывода файла Gerber: выводить файл.
            // [XmlAttribute("output")] public Bool output_;
            XmlAttr<Bool> output;
            // Настройка вывода файла Gerber: вывод слоя в зеркальном отображении.
            // [XmlAttribute("mirror")] public Bool mirror_;
            XmlAttr<Bool> mirror;
            // Настройка вывода файлов Gerber: инверсный вывод слоя.
            // [XmlAttribute("negative")] public Bool negative_;
            XmlAttr<Bool> negative;
            // Ссылка на слой.
            // [XmlElement("LayerRef")] public LayerRef layerRef;
            LayerRef layerRef;
            // Настройка экспорта Gerber файлов: список экспортируемых объектов для слоя.
            // [XmlElement("ExportObjects")] public ExportObjects ExportObjects_;
            ExportObjects ExportObjects_;
            // Настройка вывода файла Gerber: смещение объектов по осям x и y.
            // [XmlElement("Shift")] public Shift shift;
            Shift shift;
        };
        // Каталог для выходных файлов (Gerber, Drill).
        // [XmlAttribute("outPath")] public string outPath_;
        XmlAttr<QString> outPath;
        // Настройка вывода файлов Gerber, DXF, Drill: единицы измерения.
        // [XmlAttribute("units")] public units units_;
        XmlAttr<units, NoOpt> units_;
        // Настройка вывода чисел в файлы Gerber, Drill: количество цифр перед запятой.
        // [XmlAttribute("intNums", DataType = "int")] public int intNums_;
        XmlAttr<int> intNums;
        // Настройка вывода чисел в файлы Gerber, Drill: количество цифр после запятой.
        // [XmlAttribute("fractNums", DataType = "int")] public int fractNums_;
        XmlAttr<int> fractNums;
        // Настройки вывода файлов Gerber.
        // [XmlElement("ExportFile")] public List<ExportFile_GerberSettings> ExportFiles_;
        XmlArray<ExportFile> ExportFiles;
    };
    // Настройки вывода файла DXF.
    struct DXFSettings {
        // Настройки вывода слоя в файл DXF.
        struct ExportLayer {
            // Настройка экспорта слоя в файл DXF: список экспортируемых объектов для слоя.
            struct ExportObjects {
                // Настройка вывода файлов Geber, DXF: выводить проводники.
                // [XmlAttribute("wires")] public Bool wires_;
                XmlAttr<Bool> wires;
                // Настройка вывода файлов Gerber, DXF: выводить области металлизации (полигоны).
                // [XmlAttribute("coppers")] public Bool coppers_;
                XmlAttr<Bool> coppers;
                // Настройка вывода файлов Gerber, DXF: выводить контактные площадки.
                // [XmlAttribute("padstacks")] public Bool padstacks_;
                XmlAttr<Bool> padstacks;
                // Настройка вывода файлов Gerber, DXF: выводить переходные отверстия.
                // [XmlAttribute("vias")] public Bool vias_;
                XmlAttr<Bool> vias;
                // Настройка вывода файлов Gerber и DXF: выводить надписи.
                // [XmlAttribute("texts")] public Bool texts_;
                XmlAttr<Bool> texts;
                // Настройка вывода файлов Gerber, DXF: выводить ярлыки.
                // [XmlAttribute("labels")] public Bool labels_;
                XmlAttr<Bool> labels;
                // Настройка вывода файлов Gerber: выводить детали на механических слоях.
                // [XmlAttribute("details")] public Bool details_;
                XmlAttr<Bool> details;
                // Настройка вывода слоя в файл DXF: выводить очертания компонентов.
                // [XmlAttribute("compsOutline")] public Bool compsOutline_;
                XmlAttr<Bool> compsOutline;
                // Настройка вывода файлов Gerber, DXF: выводить реперные знаки.
                /// \note !В TopoR реперные знаки не поддерживаются.</ remarks>
                // [XmlAttribute("fiducials")] public Bool fiducials_;
                XmlAttr<Bool> fiducials;
            };
            // Настройка вывода слоя в файл DXF: выводить слой.
            // [XmlAttribute("output")] public Bool output_;
            XmlAttr<Bool> output;
            // Ссылка на слой.
            // [XmlElement("LayerRef")] public LayerRef layerRef;
            LayerRef layerRef;
            // Настройка экспорта слоя в файл DXF: список экспортируемых объектов для слоя.
            // [XmlElement("ExportObjects")] public ExportObjects ExportObjects_;
            ExportObjects ExportObjects_;
        };
        // Имя выходного файла (ВОМ, DXF).
        // [XmlAttribute("outFile")] public string outFile_;
        XmlAttr<QString> outFile;
        // Настройка вывода файлов Gerber, DXF, Drill: единицы измерения.
        // [XmlAttribute("units")] public units units_;
        XmlAttr<units> units_;
        // Настройка вывода файла DXF: выводить слой с контуром платы.
        // [XmlAttribute("outputBoardLayer")] public Bool outputBoardLayer_;
        XmlAttr<Bool> outputBoardLayer;
        // Настройка вывода файла DXF: выводить слой отверстий.
        // [XmlAttribute("outputDrillLayer")] public Bool outputDrillLayer_;
        XmlAttr<Bool> outputDrillLayer;
        // Настройки вывода слоя в файл DXF.
        // [XmlElement("ExportLayer")] public List<ExportLayer> ExportLayers_;
        XmlArrayElem<ExportLayer> ExportLayers;
    };
    // Настройки вывода файлов Drill.
    struct DrillSettings {
        // Настройки вывода файла Gerber.
        struct ExportFile {
            // Имя экспортируемого файла Gerber, Drill.
            /// \note !Имя не должно содержать путь к файлу.</ remarks>
            // [XmlAttribute("fileName")] public string fileName_;
            XmlAttr<QString> fileName;
        };
        // Каталог для выходных файлов (Gerber, Drill).
        // [XmlAttribute("outPath")] public string outPath_;
        XmlAttr<QString> outPath;
        // Настройка вывода файлов Gerber, DXF, Drill: единицы измерения.
        // [XmlAttribute("units")] public units units_;
        XmlAttr<units, NoOpt> units_;
        // Настройка вывода чисел в файлы Gerber, Drill: количество цифр перед запятой.
        // [XmlAttribute("intNums", DataType = "int")] public int intNums_;
        XmlAttr<int> intNums;
        // Настройка вывода чисел в файлы Gerber, Drill: количество цифр после запятой.
        // [XmlAttribute("fractNums", DataType = "int")] public int fractNums_;
        XmlAttr<int> fractNums;
        // Настройки вывода файлов Gerber.
        // [XmlElement("ExportFile")] public List<ExportFile_DrillSettings> ExportFiles_;
        XmlArray<ExportFile> ExportFiles;
    };
    // Настройки вывода BOM файла.
    struct BOMSettings {
        // Имя выходного файла (ВОМ, DXF).
        // [XmlAttribute("outFile")] public string outFile_;
        XmlAttr<QString, NoOpt> outFile;
        // Настройка диалога вывода BOM файла: выводить количество компонентов.
        // [XmlAttribute("count")] public Bool count_;
        XmlAttr<Bool> count;
        // Настройка вывода BOM файла: выводить наименование компонентов.
        // [XmlAttribute("partName")] public Bool partName_;
        XmlAttr<Bool> partName;
        // Настройка вывода BOM файла: выводить наименование посадочных мест.
        // [XmlAttribute("footprint")] public Bool footprint_;
        XmlAttr<Bool> footprint;
        // Настройка вывода BOM файла: выводить позиционные обозначения компонентов.
        // [XmlAttribute("refDes")] public Bool refDes_;
        XmlAttr<Bool> refDes;
        // Ссылка на атрибут.
        // [XmlElement("AttributeRef")] public List<AttributeRef> AttributeRefs_;
        XmlArrayElem<AttributeRef> AttributeRefs;
    };
    // Настройка фильтра сообщений.
    struct MessageFilter {
        XmlAttr<Bool> W5003; // Настройка фильтра сообщений: выводить сообщение 5003.
        XmlAttr<Bool> W5012; // Настройка фильтра сообщений: выводить сообщение 5012.
        XmlAttr<Bool> W5013; // Настройка фильтра сообщений: выводить сообщение 5013.
        XmlAttr<Bool> W5014; // Настройка фильтра сообщений: выводить сообщение 5014.
        XmlAttr<Bool> W5015; // Настройка фильтра сообщений: выводить сообщение 5015.
        XmlAttr<Bool> W5016; // Настройка фильтра сообщений: выводить сообщение 5016.
        XmlAttr<Bool> W5017; // Настройка фильтра сообщений: выводить сообщение 5017.
        XmlAttr<Bool> W5018; // Настройка фильтра сообщений: выводить сообщение 5018.
        XmlAttr<Bool> W5023; // Настройка фильтра сообщений: выводить сообщение 5023.
        XmlAttr<Bool> W5024; // Настройка фильтра сообщений: выводить сообщение 5024.
        XmlAttr<Bool> W5026; // Настройка фильтра сообщений: выводить сообщение 5026.
        XmlAttr<Bool> W5034; // Настройка фильтра сообщений: выводить сообщение 5034.
        XmlAttr<Bool> W5036; // Настройка фильтра сообщений: выводить сообщение 5036.
        XmlAttr<Bool> W5037; // Настройка фильтра сообщений: выводить сообщение 5037.

        XmlAttr<Bool> WClrnBtwComps;         // Настройка фильтра сообщений: быстрая проверка зазоров между компонентами.
        XmlAttr<Bool> WClrnBtwObjSameNet;    // Настройка фильтра сообщений: быстрая проверка зазоров между объектами одной цепи.
        XmlAttr<showWarnings> showWarnings_; // Настройка фильтра сообщений: режим показа предупреждений.
    };
    // Версия раздела.
    // [XmlAttribute("version")] public string version_;
    XmlAttr<QString> version;
    // Настройки DRC.
    // [XmlElement("DRCSettings")] public DRCSettings dRCSettings;
    Optional<DRCSettings> dRCSettings;
    // Настройки вывода файлов Gerber.
    // [XmlElement("GerberSettings")] public GerberSettings gerberSettings;
    Optional<GerberSettings> gerberSettings;
    // Настройки вывода файла DXF.
    // [XmlElement("DXFSettings")] public DXFSettings dXFSettings;
    Optional<DXFSettings> dXFSettings;
    // Настройки вывода файлов Drill.
    // [XmlElement("DrillSettings")] public DrillSettings drillSettings;
    Optional<DrillSettings> drillSettings;
    // Настройки вывода BOM файла.
    // [XmlElement("BOMSettings")] public BOMSettings bOMSettings;
    Optional<BOMSettings> bOMSettings;
    // Настройка фильтра сообщений.
    // [XmlElement("MessagesFilter")] public MessagesFilter messagesFilter;
    Optional<MessageFilter> messageFilter;
    /**************************************************************************
     * Здесь находятся функции для работы с элементами класса DialogSettings. *
     * Они не являются частью формата TopoR PCB.                              *
     * ************************************************************************/
};
} // namespace TopoR
