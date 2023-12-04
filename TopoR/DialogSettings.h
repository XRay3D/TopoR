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
namespace TopoR_PCB_Classes {
// Раздел «Настройки диалогов».
struct DialogSettings {
    // Настройки DRC.
    struct DRCSettings {
        // Настройка DRC: выводить отчёт в указанный файл.
        /* [XmlAttribute("createLog")] public Bool createLog_; */
        XmlAttr<Bool> createLog;
        // Настройка DRC: файл для вывода отчета.
        /* [XmlAttribute("logFileName")] public string logFileName_; */
        XmlAttr<QString> logFileName;
        // Настройка DRC: максимальное количество сообщений.
        /* [XmlAttribute("messageLimit", DataType = "int")] public int messageLimit_; */
        XmlAttr<int> messageLimit;
        // Настройка DRC: допуск.
        /* [XmlAttribute("tolerance", DataType = "float")] public float tolerance_; */
        XmlAttr<float> tolerance;
        // Настройка DRC: проверка целостности цепей.
        /* [XmlAttribute("checkNetIntegrity")] public Bool checkNetIntegrity_; */
        XmlAttr<Bool> checkNetIntegrity;
        // Настройка DRC: проверка ширины проводников.
        /* [XmlAttribute("checkNetWidth")] public Bool checkNetWidth_; */
        XmlAttr<Bool> checkNetWidth;
        // Настройка DRC: проверка зазоров.
        /* [XmlAttribute("checkClearances")] public Bool checkClearances_; */
        XmlAttr<Bool> checkClearances;
        // Настройка DRC: проверять зазоры между надписями и областями металлизации (полигонами).
        /* [XmlAttribute("textToCopper")] public Bool textToCopper_; */
        XmlAttr<Bool> textToCopper;
        // Настройка DRC: проверять зазоры между надписями и запретами.
        /* [XmlAttribute("textToKeepout")] public Bool textToKeepout_; */
        XmlAttr<Bool> textToKeepout;
        // Настройка DRC: проверять зазоры между надписями и переходными отверстиями.
        /* [XmlAttribute("textToVia")] public Bool textToVia_; */
        XmlAttr<Bool> textToVia;
        // Настройка DRC: проверять зазоры между надписями и проводниками.
        /* [XmlAttribute("textToWire")] public Bool textToWire_; */
        XmlAttr<Bool> textToWire;
        // Настройка DRC: проверять зазоры между надписями и контактными площадками.
        /* [XmlAttribute("textToPad")] public Bool textToPad_; */
        XmlAttr<Bool> textToPad;
        // Настройка DRC: проверять зазоры от надписей до края платы.
        /* [XmlAttribute("textToBoard")] public Bool textToBoard_; */
        XmlAttr<Bool> textToBoard;
        // Настройка DRC: проверять зазор между полигонами.
        /* [XmlAttribute("copperToCopper")] public Bool copperToCopper_; */
        XmlAttr<Bool> copperToCopper;
        // Настройка DRC: проверять зазор между полигонами и запретами.
        /* [XmlAttribute("copperToKeepout")] public Bool copperToKeepout_; */
        XmlAttr<Bool> copperToKeepout;
        // Настройка DRC: проверять зазор между полигонами и проводниками.
        /* [XmlAttribute("copperToWire")] public Bool copperToWire_; */
        XmlAttr<Bool> copperToWire;
        // Настройка DRC: проверять зазор между полигонами и переходными отверстиями.
        /* [XmlAttribute("copperToVia")] public Bool copperToVia_; */
        XmlAttr<Bool> copperToVia;
        // Настройка DRC: проверять зазор между полигонами и контактными площадками.
        /* [XmlAttribute("copperToPad")] public Bool copperToPad_; */
        XmlAttr<Bool> copperToPad;
        // Настройка DRC: проверять зазор между полигонами и краем платы.
        /* [XmlAttribute("copperToBoard")] public Bool copperToBoard_; */
        XmlAttr<Bool> copperToBoard;
        // Настройка DRC: проверять зазоры между проводниками и запретами.
        /* [XmlAttribute("wireToKeepout")] public Bool wireToKeepout_; */
        XmlAttr<Bool> wireToKeepout;
        // Настройка DRC: проверять зазоры между переходными отверстиями и запретами.
        /* [XmlAttribute("viaToKeepout")] public Bool viaToKeepout_; */
        XmlAttr<Bool> viaToKeepout;
        // Настройка DRC: проверка зазоров между контактными площадками и запретами.
        /* [XmlAttribute("padToKeepout")] public Bool padToKeepout_; */
        XmlAttr<Bool> padToKeepout;
        // Настройка DRC: проверять зазоры между проводниками.
        /* [XmlAttribute("wireToWire")] public Bool wireToWire_; */
        XmlAttr<Bool> wireToWire;
        // Настройка DRC: проверять зазоры между проводниками и переходными отверстиями.
        /* [XmlAttribute("wireToVia")] public Bool wireToVia_; */
        XmlAttr<Bool> wireToVia;
        // Настройка DRC: проверять зазоры между проводниками и контактными площадками.
        /* [XmlAttribute("wireToPad")] public Bool wireToPad_; */
        XmlAttr<Bool> wireToPad;
        // Настройка DRC: проверять зазоры от проводников до края платы.
        /* [XmlAttribute("wireToBoard")] public Bool wireToBoard_; */
        XmlAttr<Bool> wireToBoard;
        // Настройка DRC: проверять зазоры между переходными отверстиями.
        /* [XmlAttribute("viaToVia")] public Bool viaToVia_; */
        XmlAttr<Bool> viaToVia;
        // Настройка DRC: проверять зазоры между переходными отверстиями и контактными площадками.
        /* [XmlAttribute("viaToPad")] public Bool viaToPad_; */
        XmlAttr<Bool> viaToPad;
        // Настройка DRC: проверять зазоры от переходных отверстий до края платы.
        /* [XmlAttribute("viaToBoard")] public Bool viaToBoard_; */
        XmlAttr<Bool> viaToBoard;
        // Настройка DRC: проверка зазоров между контактными площадками.
        /* [XmlAttribute("padToPad")] public Bool padToPad_; */
        XmlAttr<Bool> padToPad;
        // Настройка DRC: проверка зазоров между контактными площадками и краем платы.
        /* [XmlAttribute("padToBoard")] public Bool padToBoard_; */
        XmlAttr<Bool> padToBoard;
    };
    // Настройки вывода файлов Gerber.
    struct GerberSettings {
        // Настройки вывода файла Gerber.
        struct ExportFile {
            // Настройка экспорта Gerber файлов: список экспортируемых объектов для слоя.
            struct ExportObjects {
                // Настройка вывода файла Gerber: выводить контур платы.
                /* [XmlAttribute("board")] public Bool board_; */
                XmlAttr<Bool> board;
                // Настройка вывода файлов Geber, DXF: выводить проводники.
                /* [XmlAttribute("wires")] public Bool wires_; */
                XmlAttr<Bool> wires;
                // Настройка вывода файлов Gerber, DXF: выводить области металлизации (полигоны).
                /* [XmlAttribute("coppers")] public Bool coppers_; */
                XmlAttr<Bool> coppers;
                // Настройка вывода файлов Gerber, DXF: выводить контактные площадки.
                /* [XmlAttribute("padstacks")] public Bool padstacks_; */
                XmlAttr<Bool> padstacks;
                // Настройка вывода файлов Gerber, DXF: выводить переходные отверстия.
                /* [XmlAttribute("vias")] public Bool vias_; */
                XmlAttr<Bool> vias;
                // Настройка вывода файлов Gerber и DXF: выводить надписи.
                /* [XmlAttribute("texts")] public Bool texts_; */
                XmlAttr<Bool> texts;
                // Настройка вывода файлов Gerber, DXF: выводить ярлыки.
                /* [XmlAttribute("labels")] public Bool labels_; */
                XmlAttr<Bool> labels;
                // Настройка вывода файлов Gerber: выводить детали на механических слоях.
                /* [XmlAttribute("details")] public Bool details_; */
                XmlAttr<Bool> details;
                // Настройка вывода файлов Gerber, DXF: выводить реперные знаки.
                // <remarks> !В TopoR реперные знаки не поддерживаются.</ remarks>
                /* [XmlAttribute("fiducials")] public Bool fiducials_; */
                XmlAttr<Bool> fiducials;
            };
            // Имя экспортируемого файла Gerber, Drill.
            // <remarks> !Имя не должно содержать путь к файлу.</ remarks>
            /* [XmlAttribute("fileName")] public string fileName_; */
            XmlAttr<QString> fileName;
            // Настройка вывода файла Gerber: выводить файл.
            /* [XmlAttribute("output")] public Bool output_; */
            XmlAttr<Bool> output;
            // Настройка вывода файла Gerber: вывод слоя в зеркальном отображении.
            /* [XmlAttribute("mirror")] public Bool mirror_; */
            XmlAttr<Bool> mirror;
            // Настройка вывода файлов Gerber: инверсный вывод слоя.
            /* [XmlAttribute("negative")] public Bool negative_; */
            XmlAttr<Bool> negative;
            // Ссылка на слой.
            /* [XmlElement("LayerRef")] public LayerRef layerRef; */
            LayerRef layerRef;
            // Настройка экспорта Gerber файлов: список экспортируемых объектов для слоя.
            /* [XmlElement("ExportObjects")] public ExportObjects ExportObjects_; */
            ExportObjects ExportObjects_;
            // Настройка вывода файла Gerber: смещение объектов по осям x и y.
            /* [XmlElement("Shift")] public Shift shift; */
            Shift shift;
        };
        // Каталог для выходных файлов (Gerber, Drill).
        /* [XmlAttribute("outPath")] public string outPath_; */
        XmlAttr<QString> outPath;
        // Настройка вывода файлов Gerber, DXF, Drill: единицы измерения.
        /* [XmlAttribute("units")] public units units_; */
        XmlAttr<units> units_;
        // Настройка вывода чисел в файлы Gerber, Drill: количество цифр перед запятой.
        /* [XmlAttribute("intNums", DataType = "int")] public int intNums_; */
        XmlAttr<int> intNums;
        // Настройка вывода чисел в файлы Gerber, Drill: количество цифр после запятой.
        /* [XmlAttribute("fractNums", DataType = "int")] public int fractNums_; */
        XmlAttr<int> fractNums;
        // Настройки вывода файлов Gerber.
        /* [XmlElement("ExportFile")] public List<ExportFile_GerberSettings> ExportFiles_; */
        std::vector<ExportFile> ExportFiles;
    };
    // Настройки вывода файла DXF.
    struct DXFSettings {
        // Настройки вывода слоя в файл DXF.
        struct ExportLayer {
            // Настройка экспорта слоя в файл DXF: список экспортируемых объектов для слоя.
            struct ExportObjects {
                // Настройка вывода файлов Geber, DXF: выводить проводники.
                /* [XmlAttribute("wires")] public Bool wires_; */
                XmlAttr<Bool> wires;
                // Настройка вывода файлов Gerber, DXF: выводить области металлизации (полигоны).
                /* [XmlAttribute("coppers")] public Bool coppers_; */
                XmlAttr<Bool> coppers;
                // Настройка вывода файлов Gerber, DXF: выводить контактные площадки.
                /* [XmlAttribute("padstacks")] public Bool padstacks_; */
                XmlAttr<Bool> padstacks;
                // Настройка вывода файлов Gerber, DXF: выводить переходные отверстия.
                /* [XmlAttribute("vias")] public Bool vias_; */
                XmlAttr<Bool> vias;
                // Настройка вывода файлов Gerber и DXF: выводить надписи.
                /* [XmlAttribute("texts")] public Bool texts_; */
                XmlAttr<Bool> texts;
                // Настройка вывода файлов Gerber, DXF: выводить ярлыки.
                /* [XmlAttribute("labels")] public Bool labels_; */
                XmlAttr<Bool> labels;
                // Настройка вывода файлов Gerber: выводить детали на механических слоях.
                /* [XmlAttribute("details")] public Bool details_; */
                XmlAttr<Bool> details;
                // Настройка вывода слоя в файл DXF: выводить очертания компонентов.
                /* [XmlAttribute("compsOutline")] public Bool compsOutline_; */
                XmlAttr<Bool> compsOutline;
                // Настройка вывода файлов Gerber, DXF: выводить реперные знаки.
                // <remarks> !В TopoR реперные знаки не поддерживаются.</ remarks>
                /* [XmlAttribute("fiducials")] public Bool fiducials_; */
                XmlAttr<Bool> fiducials;
            };
            // Настройка вывода слоя в файл DXF: выводить слой.
            /* [XmlAttribute("output")] public Bool output_; */
            XmlAttr<Bool> output;
            // Ссылка на слой.
            /* [XmlElement("LayerRef")] public LayerRef layerRef; */
            LayerRef layerRef;
            // Настройка экспорта слоя в файл DXF: список экспортируемых объектов для слоя.
            /* [XmlElement("ExportObjects")] public ExportObjects ExportObjects_; */
            ExportObjects ExportObjects_;
        };
        // Имя выходного файла (ВОМ, DXF).
        /* [XmlAttribute("outFile")] public string outFile_; */
        XmlAttr<QString> outFile;
        // Настройка вывода файлов Gerber, DXF, Drill: единицы измерения.
        /* [XmlAttribute("units")] public units units_; */
        XmlAttr<units> units_;
        // Настройка вывода файла DXF: выводить слой с контуром платы.
        /* [XmlAttribute("outputBoardLayer")] public Bool outputBoardLayer_; */
        XmlAttr<Bool> outputBoardLayer;
        // Настройка вывода файла DXF: выводить слой отверстий.
        /* [XmlAttribute("outputDrillLayer")] public Bool outputDrillLayer_; */
        XmlAttr<Bool> outputDrillLayer;
        // Настройки вывода слоя в файл DXF.
        /* [XmlElement("ExportLayer")] public List<ExportLayer> ExportLayers_; */
        std::vector<ExportLayer> ExportLayers;
    };
    // Настройки вывода файлов Drill.
    struct DrillSettings {
        // Настройки вывода файла Gerber.
        struct ExportFile {
            // Имя экспортируемого файла Gerber, Drill.
            // <remarks> !Имя не должно содержать путь к файлу.</ remarks>
            /* [XmlAttribute("fileName")] public string fileName_; */
            XmlAttr<QString> fileName;
        };
        // Каталог для выходных файлов (Gerber, Drill).
        /* [XmlAttribute("outPath")] public string outPath_; */
        XmlAttr<QString> outPath;
        // Настройка вывода файлов Gerber, DXF, Drill: единицы измерения.
        /* [XmlAttribute("units")] public units units_; */
        XmlAttr<units> units_;
        // Настройка вывода чисел в файлы Gerber, Drill: количество цифр перед запятой.
        /* [XmlAttribute("intNums", DataType = "int")] public int intNums_; */
        XmlAttr<int> intNums;
        // Настройка вывода чисел в файлы Gerber, Drill: количество цифр после запятой.
        /* [XmlAttribute("fractNums", DataType = "int")] public int fractNums_; */
        XmlAttr<int> fractNums;
        // Настройки вывода файлов Gerber.
        /* [XmlElement("ExportFile")] public List<ExportFile_DrillSettings> ExportFiles_; */
        std::vector<ExportFile> ExportFiles;
    };
    // Настройки вывода BOM файла.
    struct BOMSettings {
        // Имя выходного файла (ВОМ, DXF).
        /* [XmlAttribute("outFile")] public string outFile_; */
        XmlAttr<QString> outFile;
        // Настройка диалога вывода BOM файла: выводить количество компонентов.
        /* [XmlAttribute("count")] public Bool count_; */
        XmlAttr<Bool> count;
        // Настройка вывода BOM файла: выводить наименование компонентов.
        /* [XmlAttribute("partName")] public Bool partName_; */
        XmlAttr<Bool> partName;
        // Настройка вывода BOM файла: выводить наименование посадочных мест.
        /* [XmlAttribute("footprint")] public Bool footprint_; */
        XmlAttr<Bool> footprint;
        // Настройка вывода BOM файла: выводить позиционные обозначения компонентов.
        /* [XmlAttribute("refDes")] public Bool refDes_; */
        XmlAttr<Bool> refDes;
        // Ссылка на атрибут.
        /* [XmlElement("AttributeRef")] public List<AttributeRef> AttributeRefs_; */
        std::vector<AttributeRef> AttributeRefs;
    };
    // Настройка фильтра сообщений.
    struct MessagesFilter {
        // Настройка фильтра сообщений: режим показа предупреждений.
        /* [XmlAttribute("showWarnings")] public showWarnings showWarnings_; */
        XmlAttr<showWarnings> showWarnings_;
        // Настройка фильтра сообщений: выводить сообщение 5003.
        /* [XmlAttribute("W5003")] public Bool W5003_; */
        XmlAttr<Bool> W5003;
        // Настройка фильтра сообщений: выводить сообщение 5012.
        /* [XmlAttribute("W5012")] public Bool W5012_; */
        XmlAttr<Bool> W5012;
        // Настройка фильтра сообщений: выводить сообщение 5013.
        /* [XmlAttribute("W5013")] public Bool W5013_; */
        XmlAttr<Bool> W5013;
        // Настройка фильтра сообщений: выводить сообщение 5014.
        /* [XmlAttribute("W5014")] public Bool W5014_; */
        XmlAttr<Bool> W5014;
        // Настройка фильтра сообщений: выводить сообщение 5015.
        /* [XmlAttribute("W5015")] public Bool W5015_; */
        XmlAttr<Bool> W5015;
        // Настройка фильтра сообщений: выводить сообщение 5016.
        /* [XmlAttribute("W5016")] public Bool W5016_; */
        XmlAttr<Bool> W5016;
        // Настройка фильтра сообщений: выводить сообщение 5017.
        /* [XmlAttribute("W5017")] public Bool W5017_; */
        XmlAttr<Bool> W5017;
        // Настройка фильтра сообщений: выводить сообщение 5018.
        /* [XmlAttribute("W5018")] public Bool W5018_; */
        XmlAttr<Bool> W5018;
        // Настройка фильтра сообщений: выводить сообщение 5023.
        /* [XmlAttribute("W5023")] public Bool W5023_; */
        XmlAttr<Bool> W5023;
        // Настройка фильтра сообщений: выводить сообщение 5024.
        /* [XmlAttribute("W5024")] public Bool W5024_; */
        XmlAttr<Bool> W5024;
        // Настройка фильтра сообщений: выводить сообщение 5026.
        /* [XmlAttribute("W5026")] public Bool W5026_; */
        XmlAttr<Bool> W5026;
        // Настройка фильтра сообщений: выводить сообщение 5034.
        /* [XmlAttribute("W5034")] public Bool W5034_; */
        XmlAttr<Bool> W5034;
        // Настройка фильтра сообщений: выводить сообщение 5036.
        /* [XmlAttribute("W5036")] public Bool W5036_; */
        XmlAttr<Bool> W5036;
        // Настройка фильтра сообщений: выводить сообщение 5037.
        /* [XmlAttribute("W5037")] public Bool W5037_; */
        XmlAttr<Bool> W5037;
        // Настройка фильтра сообщений: быстрая проверка зазоров между компонентами.
        /* [XmlAttribute("WClrnBtwComps")] public Bool WClrnBtwComps_; */
        XmlAttr<Bool> WClrnBtwComps;
        // Настройка фильтра сообщений: быстрая проверка зазоров между объектами одной цепи.
        /* [XmlAttribute("WClrnBtwObjSameNet")] public Bool WClrnBtwObjSameNet_; */
        XmlAttr<Bool> WClrnBtwObjSameNet;
    };
    // Версия раздела.
    /* [XmlAttribute("version")] public string version_; */
    XmlAttr<QString> version;
    // Настройки DRC.
    /* [XmlElement("DRCSettings")] public DRCSettings dRCSettings; */
    DRCSettings dRCSettings;
    // Настройки вывода файлов Gerber.
    /* [XmlElement("GerberSettings")] public GerberSettings gerberSettings; */
    GerberSettings gerberSettings;
    // Настройки вывода файла DXF.
    /* [XmlElement("DXFSettings")] public DXFSettings dXFSettings; */
    DXFSettings dXFSettings;
    // Настройки вывода файлов Drill.
    /* [XmlElement("DrillSettings")] public DrillSettings drillSettings; */
    DrillSettings drillSettings;
    // Настройки вывода BOM файла.
    /* [XmlElement("BOMSettings")] public BOMSettings bOMSettings; */
    BOMSettings bOMSettings;
    // Настройка фильтра сообщений.
    /* [XmlElement("MessagesFilter")] public MessagesFilter messagesFilter; */
    MessagesFilter messagesFilter;
    /**************************************************************************
     * Здесь находятся функции для работы с элементами класса DialogSettings. *
     * Они не являются частью формата TopoR PCB.                              *
     * ************************************************************************/
    /**************************************************************************/
};
} // namespace TopoR_PCB_Classes
