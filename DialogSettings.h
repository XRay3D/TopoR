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

        //[XmlAttribute("createLog")] public Bool _createLog;
        Bool _createLog{};

        //[XmlIgnore] public bool _createLogSpecified
        bool getCreateLogSpecified() const;

        // Настройка DRC: файл для вывода отчета.
        // </summary

        //[XmlAttribute("logFileName")] public string _logFileName;
        std::string _logFileName;

        // Настройка DRC: максимальное количество сообщений.
        // </summary

        //[XmlAttribute("messageLimit", DataType = "int")] public int _messageLimit;
        int _messageLimit = 0;

        // Настройка DRC: допуск.
        // </summary

        //[XmlAttribute("tolerance", DataType = "float")] public float _tolerance;
        float _tolerance = 0.0F;

        // Настройка DRC: проверка целостности цепей.
        // </summary

        //[XmlAttribute("checkNetIntegrity")] public Bool _checkNetIntegrity;
        Bool _checkNetIntegrity{};

        //[XmlIgnore] public bool _checkNetIntegritySpecified
        bool getCheckNetIntegritySpecified() const;

        // Настройка DRC: проверка ширины проводников.
        // </summary

        //[XmlAttribute("checkNetWidth")] public Bool _checkNetWidth;
        Bool _checkNetWidth{};

        //[XmlIgnore] public bool _checkNetWidthSpecified
        bool getCheckNetWidthSpecified() const;

        // Настройка DRC: проверка зазоров.
        // </summary

        //[XmlAttribute("checkClearances")] public Bool _checkClearances;
        Bool _checkClearances{};

        //[XmlIgnore] public bool _checkClearancesSpecified
        bool getCheckClearancesSpecified() const;

        // Настройка DRC: проверять зазоры между надписями и областями металлизации (полигонами).
        // </summary

        //[XmlAttribute("textToCopper")] public Bool _textToCopper;
        Bool _textToCopper{};

        //[XmlIgnore] public bool _textToCopperSpecified
        bool getTextToCopperSpecified() const;

        // Настройка DRC: проверять зазоры между надписями и запретами.
        // </summary

        //[XmlAttribute("textToKeepout")] public Bool _textToKeepout;
        Bool _textToKeepout{};

        //[XmlIgnore] public bool _textToKeepoutSpecified
        bool getTextToKeepoutSpecified() const;

        // Настройка DRC: проверять зазоры между надписями и переходными отверстиями.
        // </summary

        //[XmlAttribute("textToVia")] public Bool _textToVia;
        Bool _textToVia{};

        //[XmlIgnore] public bool _textToViaSpecified
        bool getTextToViaSpecified() const;

        // Настройка DRC: проверять зазоры между надписями и проводниками.
        // </summary

        //[XmlAttribute("textToWire")] public Bool _textToWire;
        Bool _textToWire{};

        //[XmlIgnore] public bool _textToWireSpecified
        bool getTextToWireSpecified() const;

        // Настройка DRC: проверять зазоры между надписями и контактными площадками.
        // </summary

        //[XmlAttribute("textToPad")] public Bool _textToPad;
        Bool _textToPad{};

        //[XmlIgnore] public bool _textToPadSpecified
        bool getTextToPadSpecified() const;

        // Настройка DRC: проверять зазоры от надписей до края платы.
        // </summary

        //[XmlAttribute("textToBoard")] public Bool _textToBoard;
        Bool _textToBoard{};

        //[XmlIgnore] public bool _textToBoardSpecified
        bool getTextToBoardSpecified() const;

        // Настройка DRC: проверять зазор между полигонами.
        // </summary

        //[XmlAttribute("copperToCopper")] public Bool _copperToCopper;
        Bool _copperToCopper{};

        //[XmlIgnore] public bool _copperToCopperSpecified
        bool getCopperToCopperSpecified() const;

        // Настройка DRC: проверять зазор между полигонами и запретами.
        // </summary

        //[XmlAttribute("copperToKeepout")] public Bool _copperToKeepout;
        Bool _copperToKeepout{};

        //[XmlIgnore] public bool _copperToKeepoutSpecified
        bool getCopperToKeepoutSpecified() const;

        // Настройка DRC: проверять зазор между полигонами и проводниками.
        // </summary

        //[XmlAttribute("copperToWire")] public Bool _copperToWire;
        Bool _copperToWire{};

        //[XmlIgnore] public bool _copperToWireSpecified
        bool getCopperToWireSpecified() const;

        // Настройка DRC: проверять зазор между полигонами и переходными отверстиями.
        // </summary

        //[XmlAttribute("copperToVia")] public Bool _copperToVia;
        Bool _copperToVia{};

        //[XmlIgnore] public bool _copperToViaSpecified
        bool getCopperToViaSpecified() const;

        // Настройка DRC: проверять зазор между полигонами и контактными площадками.
        // </summary

        //[XmlAttribute("copperToPad")] public Bool _copperToPad;
        Bool _copperToPad{};

        //[XmlIgnore] public bool _copperToPadSpecified
        bool getCopperToPadSpecified() const;

        // Настройка DRC: проверять зазор между полигонами и краем платы.
        // </summary

        //[XmlAttribute("copperToBoard")] public Bool _copperToBoard;
        Bool _copperToBoard{};

        //[XmlIgnore] public bool _copperToBoardSpecified
        bool getCopperToBoardSpecified() const;

        // Настройка DRC: проверять зазоры между проводниками и запретами.
        // </summary

        //[XmlAttribute("wireToKeepout")] public Bool _wireToKeepout;
        Bool _wireToKeepout{};

        //[XmlIgnore] public bool _wireToKeepoutSpecified
        bool getWireToKeepoutSpecified() const;

        // Настройка DRC: проверять зазоры между переходными отверстиями и запретами.
        // </summary

        //[XmlAttribute("viaToKeepout")] public Bool _viaToKeepout;
        Bool _viaToKeepout{};

        //[XmlIgnore] public bool _viaToKeepoutSpecified
        bool getViaToKeepoutSpecified() const;

        // Настройка DRC: проверка зазоров между контактными площадками и запретами.
        // </summary

        //[XmlAttribute("padToKeepout")] public Bool _padToKeepout;
        Bool _padToKeepout{};

        //[XmlIgnore] public bool _padToKeepoutSpecified
        bool getPadToKeepoutSpecified() const;

        // Настройка DRC: проверять зазоры между проводниками.
        // </summary

        //[XmlAttribute("wireToWire")] public Bool _wireToWire;
        Bool _wireToWire{};

        //[XmlIgnore] public bool _wireToWireSpecified
        bool getWireToWireSpecified() const;

        // Настройка DRC: проверять зазоры между проводниками и переходными отверстиями.
        // </summary

        //[XmlAttribute("wireToVia")] public Bool _wireToVia;
        Bool _wireToVia{};

        //[XmlIgnore] public bool _wireToViaSpecified
        bool getWireToViaSpecified() const;

        // Настройка DRC: проверять зазоры между проводниками и контактными площадками.
        // </summary

        //[XmlAttribute("wireToPad")] public Bool _wireToPad;
        Bool _wireToPad{};

        //[XmlIgnore] public bool _wireToPadSpecified
        bool getWireToPadSpecified() const;

        // Настройка DRC: проверять зазоры от проводников до края платы.
        // </summary

        //[XmlAttribute("wireToBoard")] public Bool _wireToBoard;
        Bool _wireToBoard{};

        //[XmlIgnore] public bool _wireToBoardSpecified
        bool getWireToBoardSpecified() const;

        // Настройка DRC: проверять зазоры между переходными отверстиями.
        // </summary

        //[XmlAttribute("viaToVia")] public Bool _viaToVia;
        Bool _viaToVia{};

        //[XmlIgnore] public bool _viaToViaSpecified
        bool getViaToViaSpecified() const;

        // Настройка DRC: проверять зазоры между переходными отверстиями и контактными площадками.
        // </summary

        //[XmlAttribute("viaToPad")] public Bool _viaToPad;
        Bool _viaToPad{};

        //[XmlIgnore] public bool _viaToPadSpecified
        bool getViaToPadSpecified() const;

        // Настройка DRC: проверять зазоры от переходных отверстий до края платы.
        // </summary

        //[XmlAttribute("viaToBoard")] public Bool _viaToBoard;
        Bool _viaToBoard{};

        //[XmlIgnore] public bool _viaToBoardSpecified
        bool getViaToBoardSpecified() const;

        // Настройка DRC: проверка зазоров между контактными площадками.
        // </summary

        //[XmlAttribute("padToPad")] public Bool _padToPad;
        Bool _padToPad{};

        //[XmlIgnore] public bool _padToPadSpecified
        bool getPadToPadSpecified() const;

        // Настройка DRC: проверка зазоров между контактными площадками и краем платы.
        // </summary

        //[XmlAttribute("padToBoard")] public Bool _padToBoard;
        Bool _padToBoard{};

        //[XmlIgnore] public bool _padToBoardSpecified
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

                //[XmlAttribute("board")] public Bool _board;
                Bool _board{};

                // Настройка вывода файлов Geber, DXF: выводить проводники.
                // </summary

                //[XmlAttribute("wires")] public Bool _wires;
                Bool _wires{};

                // Настройка вывода файлов Gerber, DXF: выводить области металлизации (полигоны).
                // </summary

                //[XmlAttribute("coppers")] public Bool _coppers;
                Bool _coppers{};

                // Настройка вывода файлов Gerber, DXF: выводить контактные площадки.
                // </summary

                //[XmlAttribute("padstacks")] public Bool _padstacks;
                Bool _padstacks{};

                // Настройка вывода файлов Gerber, DXF: выводить переходные отверстия.
                // </summary

                //[XmlAttribute("vias")] public Bool _vias;
                Bool _vias{};

                // Настройка вывода файлов Gerber и DXF: выводить надписи.
                // </summary

                //[XmlAttribute("texts")] public Bool _texts;
                Bool _texts{};

                // Настройка вывода файлов Gerber, DXF: выводить ярлыки.
                // </summary

                //[XmlAttribute("labels")] public Bool _labels;
                Bool _labels{};

                // Настройка вывода файлов Gerber: выводить детали на механических слоях.
                // </summary

                //[XmlAttribute("details")] public Bool _details;
                Bool _details{};

                // Настройка вывода файлов Gerber, DXF: выводить реперные знаки.
                // </summary
                // <remarks>! В TopoR реперные знаки не поддерживаются.</remarks>

                //[XmlAttribute("fiducials")] public Bool _fiducials;
                Bool _fiducials{};
            };

            // Имя экспортируемого файла Gerber, Drill.
            // </summary
            // <remarks>! Имя не должно содержать путь к файлу.</remarks>

            //[XmlAttribute("fileName")] public string _fileName;
            std::string _fileName;

            // Настройка вывода файла Gerber: выводить файл.
            // </summary

            //[XmlAttribute("output")] public Bool _output;
            Bool _output{};

            // Настройка вывода файла Gerber: вывод слоя в зеркальном отображении.
            // </summary

            //[XmlAttribute("mirror")] public Bool _mirror;
            Bool _mirror{};

            // Настройка вывода файлов Gerber: инверсный вывод слоя.
            // </summary

            //[XmlAttribute("negative")] public Bool _negative;
            Bool _negative{};

            // Ссылка на слой.

            //[XmlElement("LayerRef")] public LayerRef _LayerRef;
            std::optional<LayerRef> _LayerRef;

            // Настройка экспорта Gerber файлов: список экспортируемых объектов для слоя.

            //[XmlElement("ExportObjects")] public ExportObjects_ExportFile _ExportObjects;
            std::optional<ExportObjects_ExportFile> _ExportObjects;

            // Настройка вывода файла Gerber: смещение объектов по осям x и y.

            //[XmlElement("Shift")] public Shift _Shift;
            std::optional<Shift> _Shift;
        };

        // Каталог для выходных файлов (Gerber, Drill).
        // </summary

        //[XmlAttribute("outPath")] public string _outPath;
        std::string _outPath;

        // Настройка вывода файлов Gerber, DXF, Drill: единицы измерения.
        // </summary

        //[XmlAttribute("units")] public units _units;
        units _units{};

        // Настройка вывода чисел в файлы Gerber, Drill: количество цифр перед запятой.
        // </summary

        //[XmlAttribute("intNums", DataType = "int")] public int _intNums;
        int _intNums = 0;

        // Настройка вывода чисел в файлы Gerber, Drill: количество цифр после запятой.
        // </summary

        //[XmlAttribute("fractNums", DataType = "int")] public int _fractNums;
        int _fractNums = 0;

        // Настройки вывода файлов Gerber.

        //[XmlElement("ExportFile")] public List<ExportFile_GerberSettings> _ExportFiles;
        std::vector<std::optional<ExportFile_GerberSettings>> _ExportFiles;
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

                //[XmlAttribute("wires")] public Bool _wires;
                Bool _wires{};

                // Настройка вывода файлов Gerber, DXF: выводить области металлизации (полигоны).
                // </summary

                //[XmlAttribute("coppers")] public Bool _coppers;
                Bool _coppers{};

                // Настройка вывода файлов Gerber, DXF: выводить контактные площадки.
                // </summary

                //[XmlAttribute("padstacks")] public Bool _padstacks;
                Bool _padstacks{};

                // Настройка вывода файлов Gerber, DXF: выводить переходные отверстия.
                // </summary

                //[XmlAttribute("vias")] public Bool _vias;
                Bool _vias{};

                // Настройка вывода файлов Gerber и DXF: выводить надписи.
                // </summary

                //[XmlAttribute("texts")] public Bool _texts;
                Bool _texts{};

                // Настройка вывода файлов Gerber, DXF: выводить ярлыки.
                // </summary

                //[XmlAttribute("labels")] public Bool _labels;
                Bool _labels{};

                // Настройка вывода файлов Gerber: выводить детали на механических слоях.
                // </summary

                //[XmlAttribute("details")] public Bool _details;
                Bool _details{};

                // Настройка вывода слоя в файл DXF: выводить очертания компонентов.
                // </summary

                //[XmlAttribute("compsOutline")] public Bool _compsOutline;
                Bool _compsOutline{};

                // Настройка вывода файлов Gerber, DXF: выводить реперные знаки.
                // </summary
                // <remarks>! В TopoR реперные знаки не поддерживаются.</remarks>

                //[XmlAttribute("fiducials")] public Bool _fiducials;
                Bool _fiducials{};
            };

            // Настройка вывода слоя в файл DXF: выводить слой.

            //[XmlAttribute("output")] public Bool _output;
            Bool _output{};

            // Ссылка на слой.

            //[XmlElement("LayerRef")] public LayerRef _LayerRef;
            std::optional<LayerRef> _LayerRef;

            // Настройка экспорта слоя в файл DXF: список экспортируемых объектов для слоя.

            //[XmlElement("ExportObjects")] public ExportObjects_ExportLayer _ExportObjects;
            std::optional<ExportObjects_ExportLayer> _ExportObjects;
        };

        // Имя выходного файла (ВОМ, DXF).

        //[XmlAttribute("outFile")] public string _outFile;
        std::string _outFile;

        // Настройка вывода файлов Gerber, DXF, Drill: единицы измерения.

        //[XmlAttribute("units")] public units _units;
        units _units{};

        // Настройка вывода файла DXF: выводить слой с контуром платы.

        //[XmlAttribute("outputBoardLayer")] public Bool _outputBoardLayer;
        Bool _outputBoardLayer{};

        //[XmlIgnore] public bool _outputBoardLayerSpecified
        bool getOutputBoardLayerSpecified() const;

        // Настройка вывода файла DXF: выводить слой отверстий.

        //[XmlAttribute("outputDrillLayer")] public Bool _outputDrillLayer;
        Bool _outputDrillLayer{};

        //[XmlIgnore] public bool _outputDrillLayerSpecified
        bool getOutputDrillLayerSpecified() const;

        // Настройки вывода слоя в файл DXF.

        //[XmlElement("ExportLayer")] public List<ExportLayer> _ExportLayers;
        std::vector<std::optional<ExportLayer>> _ExportLayers;
        bool ShouldSerialize_ExportLayers();
    };

    // Настройки вывода файлов Drill.

    struct DrillSettings {

        // Настройки вывода файла Gerber.

        struct ExportFile_DrillSettings {

            // Имя экспортируемого файла Gerber, Drill.
            // </summary
            // <remarks>! Имя не должно содержать путь к файлу.</remarks>

            //[XmlAttribute("fileName")] public string _fileName;
            std::string _fileName;
        };

        // Каталог для выходных файлов (Gerber, Drill).
        // </summary

        //[XmlAttribute("outPath")] public string _outPath;
        std::string _outPath;

        // Настройка вывода файлов Gerber, DXF, Drill: единицы измерения.
        // </summary

        //[XmlAttribute("units")] public units _units;
        units _units{};

        // Настройка вывода чисел в файлы Gerber, Drill: количество цифр перед запятой.
        // </summary

        //[XmlAttribute("intNums", DataType = "int")] public int _intNums;
        int _intNums = 0;

        // Настройка вывода чисел в файлы Gerber, Drill: количество цифр после запятой.
        // </summary

        //[XmlAttribute("fractNums", DataType = "int")] public int _fractNums;
        int _fractNums = 0;

        // Настройки вывода файлов Gerber.

        //[XmlElement("ExportFile")] public List<ExportFile_DrillSettings> _ExportFiles;
        std::vector<std::optional<ExportFile_DrillSettings>> _ExportFiles;
        bool ShouldSerialize_ExportFiles();
    };

    // Настройки вывода BOM файла.

    struct BOMSettings {

        // Имя выходного файла (ВОМ, DXF).

        //[XmlAttribute("outFile")] public string _outFile;
        std::string _outFile;

        // Настройка диалога вывода BOM файла: выводить количество компонентов.

        //[XmlAttribute("count")] public Bool _count;
        Bool _count{};

        //[XmlIgnore] public bool _countSpecified
        bool getCountSpecified() const;

        // Настройка вывода BOM файла: выводить наименование компонентов.

        //[XmlAttribute("partName")] public Bool _partName;
        Bool _partName{};

        //[XmlIgnore] public bool _partNameSpecified
        bool getPartNameSpecified() const;

        // Настройка вывода BOM файла: выводить наименование посадочных мест.

        //[XmlAttribute("footprint")] public Bool _footprint;
        Bool _footprint{};

        //[XmlIgnore] public bool _footprintSpecified
        bool getFootprintSpecified() const;

        // Настройка вывода BOM файла: выводить позиционные обозначения компонентов.

        //[XmlAttribute("refDes")] public Bool _refDes;
        Bool _refDes{};

        //[XmlIgnore] public bool _refDesSpecified
        bool getRefDesSpecified() const;

        // Ссылка на атрибут.

        //[XmlElement("AttributeRef")] public List<AttributeRef> _AttributeRefs;
        std::vector<std::optional<AttributeRef>> _AttributeRefs;
        bool ShouldSerialize_AttributeRefs();
    };

    // Настройка фильтра сообщений.

    struct MessagesFilter {

        // Настройка фильтра сообщений: режим показа предупреждений.

        //[XmlAttribute("showWarnings")] public showWarnings _showWarnings;
        showWarnings _showWarnings{};

        // Настройка фильтра сообщений: выводить сообщение 5003.

        //[XmlAttribute("W5003")] public Bool _W5003;
        Bool _W5003{};

        //[XmlIgnore] public bool _W5003Specified
        bool getW5003Specified() const;

        // Настройка фильтра сообщений: выводить сообщение 5012.

        //[XmlAttribute("W5012")] public Bool _W5012;
        Bool _W5012{};

        //[XmlIgnore] public bool _W5012Specified
        bool getW5012Specified() const;

        // Настройка фильтра сообщений: выводить сообщение 5013.

        //[XmlAttribute("W5013")] public Bool _W5013;
        Bool _W5013{};

        //[XmlIgnore] public bool _W5013Specified
        bool getW5013Specified() const;

        // Настройка фильтра сообщений: выводить сообщение 5014.

        //[XmlAttribute("W5014")] public Bool _W5014;
        Bool _W5014{};

        //[XmlIgnore] public bool _W5014Specified
        bool getW5014Specified() const;

        // Настройка фильтра сообщений: выводить сообщение 5015.

        //[XmlAttribute("W5015")] public Bool _W5015;
        Bool _W5015{};

        //[XmlIgnore] public bool _W5015Specified
        bool getW5015Specified() const;

        // Настройка фильтра сообщений: выводить сообщение 5016.

        //[XmlAttribute("W5016")] public Bool _W5016;
        Bool _W5016{};

        //[XmlIgnore] public bool _W5016Specified
        bool getW5016Specified() const;

        // Настройка фильтра сообщений: выводить сообщение 5017.

        //[XmlAttribute("W5017")] public Bool _W5017;
        Bool _W5017{};

        //[XmlIgnore] public bool _W5017Specified
        bool getW5017Specified() const;

        // Настройка фильтра сообщений: выводить сообщение 5018.

        //[XmlAttribute("W5018")] public Bool _W5018;
        Bool _W5018{};

        //[XmlIgnore] public bool _W5018Specified
        bool getW5018Specified() const;

        // Настройка фильтра сообщений: выводить сообщение 5023.

        //[XmlAttribute("W5023")] public Bool _W5023;
        Bool _W5023{};

        //[XmlIgnore] public bool _W5023Specified
        bool getW5023Specified() const;

        // Настройка фильтра сообщений: выводить сообщение 5024.

        //[XmlAttribute("W5024")] public Bool _W5024;
        Bool _W5024{};

        //[XmlIgnore] public bool _W5024Specified
        bool getW5024Specified() const;

        // Настройка фильтра сообщений: выводить сообщение 5026.

        //[XmlAttribute("W5026")] public Bool _W5026;
        Bool _W5026{};

        //[XmlIgnore] public bool _W5026Specified
        bool getW5026Specified() const;

        // Настройка фильтра сообщений: выводить сообщение 5034.

        //[XmlAttribute("W5034")] public Bool _W5034;
        Bool _W5034{};

        //[XmlIgnore] public bool _W5034Specified
        bool getW5034Specified() const;

        // Настройка фильтра сообщений: выводить сообщение 5036.

        //[XmlAttribute("W5036")] public Bool _W5036;
        Bool _W5036{};

        //[XmlIgnore] public bool _W5036Specified
        bool getW5036Specified() const;

        // Настройка фильтра сообщений: выводить сообщение 5037.

        //[XmlAttribute("W5037")] public Bool _W5037;
        Bool _W5037{};

        //[XmlIgnore] public bool _W5037Specified
        bool getW5037Specified() const;

        // Настройка фильтра сообщений: быстрая проверка зазоров между компонентами.

        //[XmlAttribute("WClrnBtwComps")] public Bool _WClrnBtwComps;
        Bool _WClrnBtwComps{};

        //[XmlIgnore] public bool _WClrnBtwCompsSpecified
        bool getWClrnBtwCompsSpecified() const;

        // Настройка фильтра сообщений: быстрая проверка зазоров между объектами одной цепи.

        //[XmlAttribute("WClrnBtwObjSameNet")] public Bool _WClrnBtwObjSameNet;
        Bool _WClrnBtwObjSameNet{};

        //[XmlIgnore] public bool _WClrnBtwObjSameNetSpecified
        bool getWClrnBtwObjSameNetSpecified() const;
    };

    // Версия раздела.

    //[XmlAttribute("version")] public string _version;
    std::string _version;

    // Настройки DRC.

    //[XmlElement("DRCSettings")] public DRCSettings _DRCSettings;
    std::optional<DRCSettings> _DRCSettings;

    // Настройки вывода файлов Gerber.

    //[XmlElement("GerberSettings")] public GerberSettings _GerberSettings;
    std::optional<GerberSettings> _GerberSettings;

    // Настройки вывода файла DXF.

    //[XmlElement("DXFSettings")] public DXFSettings _DXFSettings;
    std::optional<DXFSettings> _DXFSettings;

    // Настройки вывода файлов Drill.

    //[XmlElement("DrillSettings")] public DrillSettings _DrillSettings;
    std::optional<DrillSettings> _DrillSettings;

    // Настройки вывода BOM файла.

    //[XmlElement("BOMSettings")] public BOMSettings _BOMSettings;
    std::optional<BOMSettings> _BOMSettings;

    // Настройка фильтра сообщений.

    //[XmlElement("MessagesFilter")] public MessagesFilter _MessagesFilter;
    std::optional<MessagesFilter> _MessagesFilter;

    /**************************************************************************
     * Здесь находятся функции для работы с элементами класса DialogSettings. *
     * Они не являются частью формата TopoR PCB.                              *
     * ************************************************************************/

    /**************************************************************************/
};
} // namespace TopoR_PCB_Classes
