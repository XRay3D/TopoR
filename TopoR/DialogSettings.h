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
        // </summary

        /* [XmlAttribute("createLog")] public Bool createLog_; */
        Bool _createLog{};

        /* public bool _createLogSpecified */
        bool getCreateLogSpecified() const;

        // Настройка DRC: файл для вывода отчета.
        // </summary

        /* [XmlAttribute("logFileName")] public string logFileName_; */
        QString logFileName_;

        // Настройка DRC: максимальное количество сообщений.
        // </summary

        /* [XmlAttribute("messageLimit", DataType = "int")] public int messageLimit_; */
        XmlAttr<int>messageLimit;
        int _messageLimit = 0;

        // Настройка DRC: допуск.
        // </summary

        /* [XmlAttribute("tolerance", DataType = "float")] public float tolerance_; */
        XmlAttr<float>tolerance;
        float _tolerance = 0.0F;

        // Настройка DRC: проверка целостности цепей.
        // </summary

        /* [XmlAttribute("checkNetIntegrity")] public Bool checkNetIntegrity_; */
        Bool _checkNetIntegrity{};

        /* public bool _checkNetIntegritySpecified */
        bool getCheckNetIntegritySpecified() const;

        // Настройка DRC: проверка ширины проводников.
        // </summary

        /* [XmlAttribute("checkNetWidth")] public Bool checkNetWidth_; */
        Bool _checkNetWidth{};

        /* public bool _checkNetWidthSpecified */
        bool getCheckNetWidthSpecified() const;

        // Настройка DRC: проверка зазоров.
        // </summary

        /* [XmlAttribute("checkClearances")] public Bool checkClearances_; */
        Bool _checkClearances{};

        /* public bool _checkClearancesSpecified */
        bool getCheckClearancesSpecified() const;

        // Настройка DRC: проверять зазоры между надписями и областями металлизации (полигонами).
        // </summary

        /* [XmlAttribute("textToCopper")] public Bool textToCopper_; */
        Bool _textToCopper{};

        /* public bool _textToCopperSpecified */
        bool getTextToCopperSpecified() const;

        // Настройка DRC: проверять зазоры между надписями и запретами.
        // </summary

        /* [XmlAttribute("textToKeepout")] public Bool textToKeepout_; */
        Bool _textToKeepout{};

        /* public bool _textToKeepoutSpecified */
        bool getTextToKeepoutSpecified() const;

        // Настройка DRC: проверять зазоры между надписями и переходными отверстиями.
        // </summary

        /* [XmlAttribute("textToVia")] public Bool textToVia_; */
        Bool _textToVia{};

        /* public bool _textToViaSpecified */
        bool getTextToViaSpecified() const;

        // Настройка DRC: проверять зазоры между надписями и проводниками.
        // </summary

        /* [XmlAttribute("textToWire")] public Bool textToWire_; */
        Bool _textToWire{};

        /* public bool _textToWireSpecified */
        bool getTextToWireSpecified() const;

        // Настройка DRC: проверять зазоры между надписями и контактными площадками.
        // </summary

        /* [XmlAttribute("textToPad")] public Bool textToPad_; */
        Bool _textToPad{};

        /* public bool _textToPadSpecified */
        bool getTextToPadSpecified() const;

        // Настройка DRC: проверять зазоры от надписей до края платы.
        // </summary

        /* [XmlAttribute("textToBoard")] public Bool textToBoard_; */
        Bool _textToBoard{};

        /* public bool _textToBoardSpecified */
        bool getTextToBoardSpecified() const;

        // Настройка DRC: проверять зазор между полигонами.
        // </summary

        /* [XmlAttribute("copperToCopper")] public Bool copperToCopper_; */
        Bool _copperToCopper{};

        /* public bool _copperToCopperSpecified */
        bool getCopperToCopperSpecified() const;

        // Настройка DRC: проверять зазор между полигонами и запретами.
        // </summary

        /* [XmlAttribute("copperToKeepout")] public Bool copperToKeepout_; */
        Bool _copperToKeepout{};

        /* public bool _copperToKeepoutSpecified */
        bool getCopperToKeepoutSpecified() const;

        // Настройка DRC: проверять зазор между полигонами и проводниками.
        // </summary

        /* [XmlAttribute("copperToWire")] public Bool copperToWire_; */
        Bool _copperToWire{};

        /* public bool _copperToWireSpecified */
        bool getCopperToWireSpecified() const;

        // Настройка DRC: проверять зазор между полигонами и переходными отверстиями.
        // </summary

        /* [XmlAttribute("copperToVia")] public Bool copperToVia_; */
        Bool _copperToVia{};

        /* public bool _copperToViaSpecified */
        bool getCopperToViaSpecified() const;

        // Настройка DRC: проверять зазор между полигонами и контактными площадками.
        // </summary

        /* [XmlAttribute("copperToPad")] public Bool copperToPad_; */
        Bool _copperToPad{};

        /* public bool _copperToPadSpecified */
        bool getCopperToPadSpecified() const;

        // Настройка DRC: проверять зазор между полигонами и краем платы.
        // </summary

        /* [XmlAttribute("copperToBoard")] public Bool copperToBoard_; */
        Bool _copperToBoard{};

        /* public bool _copperToBoardSpecified */
        bool getCopperToBoardSpecified() const;

        // Настройка DRC: проверять зазоры между проводниками и запретами.
        // </summary

        /* [XmlAttribute("wireToKeepout")] public Bool wireToKeepout_; */
        Bool _wireToKeepout{};

        /* public bool _wireToKeepoutSpecified */
        bool getWireToKeepoutSpecified() const;

        // Настройка DRC: проверять зазоры между переходными отверстиями и запретами.
        // </summary

        /* [XmlAttribute("viaToKeepout")] public Bool viaToKeepout_; */
        Bool _viaToKeepout{};

        /* public bool _viaToKeepoutSpecified */
        bool getViaToKeepoutSpecified() const;

        // Настройка DRC: проверка зазоров между контактными площадками и запретами.
        // </summary

        /* [XmlAttribute("padToKeepout")] public Bool padToKeepout_; */
        Bool _padToKeepout{};

        /* public bool _padToKeepoutSpecified */
        bool getPadToKeepoutSpecified() const;

        // Настройка DRC: проверять зазоры между проводниками.
        // </summary

        /* [XmlAttribute("wireToWire")] public Bool wireToWire_; */
        Bool _wireToWire{};

        /* public bool _wireToWireSpecified */
        bool getWireToWireSpecified() const;

        // Настройка DRC: проверять зазоры между проводниками и переходными отверстиями.
        // </summary

        /* [XmlAttribute("wireToVia")] public Bool wireToVia_; */
        Bool _wireToVia{};

        /* public bool _wireToViaSpecified */
        bool getWireToViaSpecified() const;

        // Настройка DRC: проверять зазоры между проводниками и контактными площадками.
        // </summary

        /* [XmlAttribute("wireToPad")] public Bool wireToPad_; */
        Bool _wireToPad{};

        /* public bool _wireToPadSpecified */
        bool getWireToPadSpecified() const;

        // Настройка DRC: проверять зазоры от проводников до края платы.
        // </summary

        /* [XmlAttribute("wireToBoard")] public Bool wireToBoard_; */
        Bool _wireToBoard{};

        /* public bool _wireToBoardSpecified */
        bool getWireToBoardSpecified() const;

        // Настройка DRC: проверять зазоры между переходными отверстиями.
        // </summary

        /* [XmlAttribute("viaToVia")] public Bool viaToVia_; */
        Bool _viaToVia{};

        /* public bool _viaToViaSpecified */
        bool getViaToViaSpecified() const;

        // Настройка DRC: проверять зазоры между переходными отверстиями и контактными площадками.
        // </summary

        /* [XmlAttribute("viaToPad")] public Bool viaToPad_; */
        Bool _viaToPad{};

        /* public bool _viaToPadSpecified */
        bool getViaToPadSpecified() const;

        // Настройка DRC: проверять зазоры от переходных отверстий до края платы.
        // </summary

        /* [XmlAttribute("viaToBoard")] public Bool viaToBoard_; */
        Bool _viaToBoard{};

        /* public bool _viaToBoardSpecified */
        bool getViaToBoardSpecified() const;

        // Настройка DRC: проверка зазоров между контактными площадками.
        // </summary

        /* [XmlAttribute("padToPad")] public Bool padToPad_; */
        Bool _padToPad{};

        /* public bool _padToPadSpecified */
        bool getPadToPadSpecified() const;

        // Настройка DRC: проверка зазоров между контактными площадками и краем платы.
        // </summary

        /* [XmlAttribute("padToBoard")] public Bool padToBoard_; */
        Bool _padToBoard{};

        /* public bool _padToBoardSpecified */
        bool getPadToBoardSpecified() const;
    };

    // Настройки вывода файлов Gerber.

    struct GerberSettings {

        // Настройки вывода файла Gerber.

        struct ExportFile_GerberSettings {

            // Настройка экспорта Gerber файлов: список экспортируемых объектов для слоя.

            struct ExportObjects_ExportFile {

                // Настройка вывода файла Gerber: выводить контур платы.
                // </summary

                /* [XmlAttribute("board")] public Bool board_; */
                Bool _board{};

                // Настройка вывода файлов Geber, DXF: выводить проводники.
                // </summary

                /* [XmlAttribute("wires")] public Bool wires_; */
                Bool _wires{};

                // Настройка вывода файлов Gerber, DXF: выводить области металлизации (полигоны).
                // </summary

                /* [XmlAttribute("coppers")] public Bool coppers_; */
                Bool _coppers{};

                // Настройка вывода файлов Gerber, DXF: выводить контактные площадки.
                // </summary

                /* [XmlAttribute("padstacks")] public Bool padstacks_; */
                Bool _padstacks{};

                // Настройка вывода файлов Gerber, DXF: выводить переходные отверстия.
                // </summary

                /* [XmlAttribute("vias")] public Bool vias_; */
                Bool _vias{};

                // Настройка вывода файлов Gerber и DXF: выводить надписи.
                // </summary

                /* [XmlAttribute("texts")] public Bool texts_; */
                Bool _texts{};

                // Настройка вывода файлов Gerber, DXF: выводить ярлыки.
                // </summary

                /* [XmlAttribute("labels")] public Bool labels_; */
                Bool _labels{};

                // Настройка вывода файлов Gerber: выводить детали на механических слоях.
                // </summary

                /* [XmlAttribute("details")] public Bool details_; */
                Bool _details{};

                // Настройка вывода файлов Gerber, DXF: выводить реперные знаки.
                // </summary
                // <remarks>! В TopoR реперные знаки не поддерживаются.</remarks>

                /* [XmlAttribute("fiducials")] public Bool fiducials_; */
                Bool _fiducials{};
            };

            // Имя экспортируемого файла Gerber, Drill.
            // </summary
            // <remarks>! Имя не должно содержать путь к файлу.</remarks>

            /* [XmlAttribute("fileName")] public string fileName_; */
            QString fileName_;

            // Настройка вывода файла Gerber: выводить файл.
            // </summary

            /* [XmlAttribute("output")] public Bool output_; */
            Bool _output{};

            // Настройка вывода файла Gerber: вывод слоя в зеркальном отображении.
            // </summary

            /* [XmlAttribute("mirror")] public Bool mirror_; */
            Bool _mirror{};

            // Настройка вывода файлов Gerber: инверсный вывод слоя.
            // </summary

            /* [XmlAttribute("negative")] public Bool negative_; */
            Bool _negative{};

            // Ссылка на слой.

            /* [XmlElement("LayerRef")] public LayerRef LayerRef_; */
            LayerRef LayerRef_;

            // Настройка экспорта Gerber файлов: список экспортируемых объектов для слоя.

            /* [XmlElement("ExportObjects")] public ExportObjects_ExportFile ExportObjects_; */
            ExportObjects_ExportFile ExportObjects_;

            // Настройка вывода файла Gerber: смещение объектов по осям x и y.

            /* [XmlElement("Shift")] public Shift Shift_; */
            Shift Shift_;
        };

        // Каталог для выходных файлов (Gerber, Drill).
        // </summary

        /* [XmlAttribute("outPath")] public string outPath_; */
        QString outPath_;

        // Настройка вывода файлов Gerber, DXF, Drill: единицы измерения.
        // </summary

        /* [XmlAttribute("units")] public units units_; */
        units _units{};

        // Настройка вывода чисел в файлы Gerber, Drill: количество цифр перед запятой.
        // </summary

        /* [XmlAttribute("intNums", DataType = "int")] public int intNums_; */
        XmlAttr<int>intNums;
        int _intNums = 0;

        // Настройка вывода чисел в файлы Gerber, Drill: количество цифр после запятой.
        // </summary

        /* [XmlAttribute("fractNums", DataType = "int")] public int fractNums_; */
        XmlAttr<int>fractNums;
        int _fractNums = 0;

        // Настройки вывода файлов Gerber.

        /* [XmlElement("ExportFile")] public List<ExportFile_GerberSettings> ExportFiles_; */
        std::vector<ExportFile_GerberSettings> ExportFiles_;
        bool ShouldSerialize_ExportFiles();
    };

    // Настройки вывода файла DXF.

    struct DXFSettings {

        // Настройки вывода слоя в файл DXF.

        struct ExportLayer {

            // Настройка экспорта слоя в файл DXF: список экспортируемых объектов для слоя.

            struct ExportObjects_ExportLayer {

                // Настройка вывода файлов Geber, DXF: выводить проводники.
                // </summary

                /* [XmlAttribute("wires")] public Bool wires_; */
                Bool _wires{};

                // Настройка вывода файлов Gerber, DXF: выводить области металлизации (полигоны).
                // </summary

                /* [XmlAttribute("coppers")] public Bool coppers_; */
                Bool _coppers{};

                // Настройка вывода файлов Gerber, DXF: выводить контактные площадки.
                // </summary

                /* [XmlAttribute("padstacks")] public Bool padstacks_; */
                Bool _padstacks{};

                // Настройка вывода файлов Gerber, DXF: выводить переходные отверстия.
                // </summary

                /* [XmlAttribute("vias")] public Bool vias_; */
                Bool _vias{};

                // Настройка вывода файлов Gerber и DXF: выводить надписи.
                // </summary

                /* [XmlAttribute("texts")] public Bool texts_; */
                Bool _texts{};

                // Настройка вывода файлов Gerber, DXF: выводить ярлыки.
                // </summary

                /* [XmlAttribute("labels")] public Bool labels_; */
                Bool _labels{};

                // Настройка вывода файлов Gerber: выводить детали на механических слоях.
                // </summary

                /* [XmlAttribute("details")] public Bool details_; */
                Bool _details{};

                // Настройка вывода слоя в файл DXF: выводить очертания компонентов.
                // </summary

                /* [XmlAttribute("compsOutline")] public Bool compsOutline_; */
                Bool _compsOutline{};

                // Настройка вывода файлов Gerber, DXF: выводить реперные знаки.
                // </summary
                // <remarks>! В TopoR реперные знаки не поддерживаются.</remarks>

                /* [XmlAttribute("fiducials")] public Bool fiducials_; */
                Bool _fiducials{};
            };

            // Настройка вывода слоя в файл DXF: выводить слой.

            /* [XmlAttribute("output")] public Bool output_; */
            Bool _output{};

            // Ссылка на слой.

            /* [XmlElement("LayerRef")] public LayerRef LayerRef_; */
            LayerRef LayerRef_;

            // Настройка экспорта слоя в файл DXF: список экспортируемых объектов для слоя.

            /* [XmlElement("ExportObjects")] public ExportObjects_ExportLayer ExportObjects_; */
            ExportObjects_ExportLayer ExportObjects_;
        };

        // Имя выходного файла (ВОМ, DXF).

        /* [XmlAttribute("outFile")] public string outFile_; */
        QString outFile_;

        // Настройка вывода файлов Gerber, DXF, Drill: единицы измерения.

        /* [XmlAttribute("units")] public units units_; */
        units _units{};

        // Настройка вывода файла DXF: выводить слой с контуром платы.

        /* [XmlAttribute("outputBoardLayer")] public Bool outputBoardLayer_; */
        Bool _outputBoardLayer{};

        /* public bool _outputBoardLayerSpecified */
        bool getOutputBoardLayerSpecified() const;

        // Настройка вывода файла DXF: выводить слой отверстий.

        /* [XmlAttribute("outputDrillLayer")] public Bool outputDrillLayer_; */
        Bool _outputDrillLayer{};

        /* public bool _outputDrillLayerSpecified */
        bool getOutputDrillLayerSpecified() const;

        // Настройки вывода слоя в файл DXF.

        /* [XmlElement("ExportLayer")] public List<ExportLayer> ExportLayers_; */
        std::vector<ExportLayer> ExportLayers_;
        bool ShouldSerialize_ExportLayers();
    };

    // Настройки вывода файлов Drill.

    struct DrillSettings {

        // Настройки вывода файла Gerber.

        struct ExportFile_DrillSettings {

            // Имя экспортируемого файла Gerber, Drill.
            // </summary
            // <remarks>! Имя не должно содержать путь к файлу.</remarks>

            /* [XmlAttribute("fileName")] public string fileName_; */
            QString fileName_;
        };

        // Каталог для выходных файлов (Gerber, Drill).
        // </summary

        /* [XmlAttribute("outPath")] public string outPath_; */
        QString outPath_;

        // Настройка вывода файлов Gerber, DXF, Drill: единицы измерения.
        // </summary

        /* [XmlAttribute("units")] public units units_; */
        units _units{};

        // Настройка вывода чисел в файлы Gerber, Drill: количество цифр перед запятой.
        // </summary

        /* [XmlAttribute("intNums", DataType = "int")] public int intNums_; */
        XmlAttr<int>intNums;
        int _intNums = 0;

        // Настройка вывода чисел в файлы Gerber, Drill: количество цифр после запятой.
        // </summary

        /* [XmlAttribute("fractNums", DataType = "int")] public int fractNums_; */
        XmlAttr<int>fractNums;
        int _fractNums = 0;

        // Настройки вывода файлов Gerber.

        /* [XmlElement("ExportFile")] public List<ExportFile_DrillSettings> ExportFiles_; */
        std::vector<ExportFile_DrillSettings> ExportFiles_;
        bool ShouldSerialize_ExportFiles();
    };

    // Настройки вывода BOM файла.

    struct BOMSettings {

        // Имя выходного файла (ВОМ, DXF).

        /* [XmlAttribute("outFile")] public string outFile_; */
        QString outFile_;

        // Настройка диалога вывода BOM файла: выводить количество компонентов.

        /* [XmlAttribute("count")] public Bool count_; */
        Bool _count{};

        /* public bool _countSpecified */
        bool getCountSpecified() const;

        // Настройка вывода BOM файла: выводить наименование компонентов.

        /* [XmlAttribute("partName")] public Bool partName_; */
        Bool _partName{};

        /* public bool _partNameSpecified */
        bool getPartNameSpecified() const;

        // Настройка вывода BOM файла: выводить наименование посадочных мест.

        /* [XmlAttribute("footprint")] public Bool footprint_; */
        Bool _footprint{};

        /* public bool _footprintSpecified */
        bool getFootprintSpecified() const;

        // Настройка вывода BOM файла: выводить позиционные обозначения компонентов.

        /* [XmlAttribute("refDes")] public Bool refDes_; */
        Bool _refDes{};

        /* public bool _refDesSpecified */
        bool getRefDesSpecified() const;

        // Ссылка на атрибут.

        /* [XmlElement("AttributeRef")] public List<AttributeRef> AttributeRefs_; */
        std::vector<AttributeRef> AttributeRefs_;
        bool ShouldSerialize_AttributeRefs();
    };

    // Настройка фильтра сообщений.

    struct MessagesFilter {

        // Настройка фильтра сообщений: режим показа предупреждений.

        /* [XmlAttribute("showWarnings")] public showWarnings showWarnings_; */
        showWarnings _showWarnings{};

        // Настройка фильтра сообщений: выводить сообщение 5003.

        /* [XmlAttribute("W5003")] public Bool W5003_; */
        Bool _W5003{};

        /* public bool _W5003Specified */
        bool getW5003Specified() const;

        // Настройка фильтра сообщений: выводить сообщение 5012.

        /* [XmlAttribute("W5012")] public Bool W5012_; */
        Bool _W5012{};

        /* public bool _W5012Specified */
        bool getW5012Specified() const;

        // Настройка фильтра сообщений: выводить сообщение 5013.

        /* [XmlAttribute("W5013")] public Bool W5013_; */
        Bool _W5013{};

        /* public bool _W5013Specified */
        bool getW5013Specified() const;

        // Настройка фильтра сообщений: выводить сообщение 5014.

        /* [XmlAttribute("W5014")] public Bool W5014_; */
        Bool _W5014{};

        /* public bool _W5014Specified */
        bool getW5014Specified() const;

        // Настройка фильтра сообщений: выводить сообщение 5015.

        /* [XmlAttribute("W5015")] public Bool W5015_; */
        Bool _W5015{};

        /* public bool _W5015Specified */
        bool getW5015Specified() const;

        // Настройка фильтра сообщений: выводить сообщение 5016.

        /* [XmlAttribute("W5016")] public Bool W5016_; */
        Bool _W5016{};

        /* public bool _W5016Specified */
        bool getW5016Specified() const;

        // Настройка фильтра сообщений: выводить сообщение 5017.

        /* [XmlAttribute("W5017")] public Bool W5017_; */
        Bool _W5017{};

        /* public bool _W5017Specified */
        bool getW5017Specified() const;

        // Настройка фильтра сообщений: выводить сообщение 5018.

        /* [XmlAttribute("W5018")] public Bool W5018_; */
        Bool _W5018{};

        /* public bool _W5018Specified */
        bool getW5018Specified() const;

        // Настройка фильтра сообщений: выводить сообщение 5023.

        /* [XmlAttribute("W5023")] public Bool W5023_; */
        Bool _W5023{};

        /* public bool _W5023Specified */
        bool getW5023Specified() const;

        // Настройка фильтра сообщений: выводить сообщение 5024.

        /* [XmlAttribute("W5024")] public Bool W5024_; */
        Bool _W5024{};

        /* public bool _W5024Specified */
        bool getW5024Specified() const;

        // Настройка фильтра сообщений: выводить сообщение 5026.

        /* [XmlAttribute("W5026")] public Bool W5026_; */
        Bool _W5026{};

        /* public bool _W5026Specified */
        bool getW5026Specified() const;

        // Настройка фильтра сообщений: выводить сообщение 5034.

        /* [XmlAttribute("W5034")] public Bool W5034_; */
        Bool _W5034{};

        /* public bool _W5034Specified */
        bool getW5034Specified() const;

        // Настройка фильтра сообщений: выводить сообщение 5036.

        /* [XmlAttribute("W5036")] public Bool W5036_; */
        Bool _W5036{};

        /* public bool _W5036Specified */
        bool getW5036Specified() const;

        // Настройка фильтра сообщений: выводить сообщение 5037.

        /* [XmlAttribute("W5037")] public Bool W5037_; */
        Bool _W5037{};

        /* public bool _W5037Specified */
        bool getW5037Specified() const;

        // Настройка фильтра сообщений: быстрая проверка зазоров между компонентами.

        /* [XmlAttribute("WClrnBtwComps")] public Bool WClrnBtwComps_; */
        Bool _WClrnBtwComps{};

        /* public bool _WClrnBtwCompsSpecified */
        bool getWClrnBtwCompsSpecified() const;

        // Настройка фильтра сообщений: быстрая проверка зазоров между объектами одной цепи.

        /* [XmlAttribute("WClrnBtwObjSameNet")] public Bool WClrnBtwObjSameNet_; */
        Bool _WClrnBtwObjSameNet{};

        /* public bool _WClrnBtwObjSameNetSpecified */
        bool getWClrnBtwObjSameNetSpecified() const;
    };

    // Версия раздела.

    /* [XmlAttribute("version")] public string version_; */
    QString version_;

    // Настройки DRC.

    /* [XmlElement("DRCSettings")] public DRCSettings DRCSettings_; */
    DRCSettings DRCSettings_;

    // Настройки вывода файлов Gerber.

    /* [XmlElement("GerberSettings")] public GerberSettings GerberSettings_; */
    GerberSettings GerberSettings_;

    // Настройки вывода файла DXF.

    /* [XmlElement("DXFSettings")] public DXFSettings DXFSettings_; */
    DXFSettings DXFSettings_;

    // Настройки вывода файлов Drill.

    /* [XmlElement("DrillSettings")] public DrillSettings DrillSettings_; */
    DrillSettings DrillSettings_;

    // Настройки вывода BOM файла.

    /* [XmlElement("BOMSettings")] public BOMSettings BOMSettings_; */
    BOMSettings BOMSettings_;

    // Настройка фильтра сообщений.

    /* [XmlElement("MessagesFilter")] public MessagesFilter MessagesFilter_; */
    MessagesFilter MessagesFilter_;

    /**************************************************************************
     * Здесь находятся функции для работы с элементами класса DialogSettings. *
     * Они не являются частью формата TopoR PCB.                              *
     * ************************************************************************/

    /**************************************************************************/
};

} // namespace TopoR_PCB_Classes
