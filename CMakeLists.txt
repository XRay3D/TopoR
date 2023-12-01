#/*******************************************************************************
#* Author    :  Damir Bakiev                                                    *
#* Version   :  na                                                              *
#* Date      :  03 October 2022                                                 *
#* Website   :  na                                                              *
#* Copyright :  Damir Bakiev 2016-2022                                          *
#* License   :                                                                  *
#* Use, modification & distribution is subject to Boost Software License Ver 1. *
#* http://www.boost.org/LICENSE_1_0.txt                                         *
#*******************************************************************************/
cmake_minimum_required(VERSION 3.20)


project(TopoR LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

add_definitions(
    -DQT_MESSAGELOGCONTEXT# qDebug()
    -DQT_DISABLE_DEPRECATED_BEFORE=0x060000
)

find_package(QT NAMES #[[Qt6]] Qt5 Core)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Gui Widgets Xml REQUIRED)

add_compile_options(
    -fconstexpr-depth=50
    # -fpermissive
)

# file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
# file(GLOB_RECURSE JSONS ${CMAKE_CURRENT_SOURCE_DIR}/*.json)
# file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
# file(GLOB_RECURSE UIS ${CMAKE_CURRENT_SOURCE_DIR}/*.ui)

include_directories(
    pfr_non_boost/include
    compile-time-regular-expressions/single-header
)

add_executable(${PROJECT_NAME}
    # ${HEADERS}
    # ${JSONS}
    # ${SOURCES}
    # ${UIS}
    # qserializer.h
    # topor_cellon.h
    # topor_file.cpp
    # topor_file.h
    # topor_formatstate.cpp
    # topor_highlighter.cpp
    # topor_highlighter.h
    # topor_node.cpp
    # topor_node.h
    # topor_parser.cpp
    # topor_parser.h
    # topor_plugin.cpp
    # topor_plugin.h
    # topor_settingstab.cpp
    # topor_settingstab.h
    # topor_types.h
    Commons.cpp
    Commons.h
    ComponentsOnBoard.cpp
    ComponentsOnBoard.h
    Connectivity.cpp
    Connectivity.h
    Constructive.cpp
    Constructive.h
    DialogSettings.cpp
    DialogSettings.h
    DisplayControl.cpp
    DisplayControl.h
    Enums.h
    Groups.cpp
    Groups.h
    Header.cpp
    Header.h
    HiSpeedRules.cpp
    HiSpeedRules.h
    Layers.cpp
    Layers.h
    LocalLibrary.cpp
    LocalLibrary.h
    NetList.cpp
    NetList.h
    Rules.cpp
    Rules.h
    Settings.cpp
    Settings.h
    TextStyles.cpp
    TextStyles.h
    TopoR_PCB_File.cpp
    TopoR_PCB_File.h
    enumerator.h
    main.cpp
    mainwindow.cpp
    mainwindow.h
    serializer.cpp
    serializer.h
    Coordinates.h
    МАН2_МСИС_V2.1.fst
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Xml
)

