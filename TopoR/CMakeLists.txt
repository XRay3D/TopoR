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
#set(CMAKE_AUTOUIC ON)
#set(CMAKE_AUTOMOC ON)
#set(CMAKE_AUTORCC ON)

#set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_INCLUDE_CURRENT_DIR ON)

#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} / bin)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} / bin)
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} / bin)

# add_definitions(
#     -DQT_MESSAGELOGCONTEXT #qDebug()
#     -DQT_DISABLE_DEPRECATED_BEFORE=0x060000
# )

find_package(QT NAMES Qt6 Qt5 Widgets)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

#add_compile_options(
#- fconstexpr - depth = 50
#- fpermissive
#)

#file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
# file(GLOB_RECURSE JSONS ${CMAKE_CURRENT_SOURCE_DIR}/*.json)
# file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
# file(GLOB_RECURSE UIS ${CMAKE_CURRENT_SOURCE_DIR}/*.ui)

# include_directories(
#     pfr_non_boost/include
# ../compile-time-regular-expressions/single-header
#     TopoR
# )

set(FST
    /home/x-ray/Документы/TopoR/Examples/Example_04/Arcs.fst
    /home/x-ray/Документы/TopoR/Examples/Example_04/Arcs_standard_routing.fst
    /home/x-ray/Документы/TopoR/Examples/Example_05/MinVia.fst
    /home/x-ray/Документы/TopoR/Examples/Example_05/MinVia_standard_routing.fst
    /home/x-ray/Документы/TopoR/Examples/Example_02/Placement.fst
    /home/x-ray/Документы/TopoR/Examples/Example_02/Placement_standard_routing.fst
    /home/x-ray/Документы/TopoR/Examples/Example_06/Signals.fst
    /home/x-ray/Документы/TopoR/Examples/Example_01/SingleLayer.fst
    /home/x-ray/Документы/TopoR/Examples/Example_03/arz_2L.fst
    /home/x-ray/Документы/TopoR/Examples/Example_03/arz_4L.fst
    /home/x-ray/Документы/TopoR/Examples/Example_03/arz_standard_routing.fst
)
# CMAKE_CURRENT_LIST_DIR <=> CMAKE_CURRENT_SOURCE_DIR
add_library(${PROJECT_NAME} STATIC)

target_sources(${PROJECT_NAME}
    PRIVATE
    # PUBLIC
    Commons.cpp
    ComponentsOnBoard.cpp
    Connectivity.cpp
    Constructive.cpp
    DialogSettings.cpp
    DisplayControl.cpp
    Groups.cpp
    Header.cpp
    HiSpeedRules.cpp
    Layers.cpp
    LocalLibrary.cpp
    NetList.cpp
    Rules.cpp
    Settings.cpp
    TextStyles.cpp
    TopoR_PCB_File.cpp
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/Commons.h
    ${CMAKE_CURRENT_LIST_DIR}/ComponentsOnBoard.h
    ${CMAKE_CURRENT_LIST_DIR}/Connectivity.h
    ${CMAKE_CURRENT_LIST_DIR}/Constructive.h
    ${CMAKE_CURRENT_LIST_DIR}/Coordinates.h
    ${CMAKE_CURRENT_LIST_DIR}/DialogSettings.h
    ${CMAKE_CURRENT_LIST_DIR}/DisplayControl.h
    ${CMAKE_CURRENT_LIST_DIR}/Enums.h
    ${CMAKE_CURRENT_LIST_DIR}/Groups.h
    ${CMAKE_CURRENT_LIST_DIR}/Header.h
    ${CMAKE_CURRENT_LIST_DIR}/HiSpeedRules.h
    ${CMAKE_CURRENT_LIST_DIR}/Layers.h
    ${CMAKE_CURRENT_LIST_DIR}/LocalLibrary.h
    ${CMAKE_CURRENT_LIST_DIR}/NetList.h
    ${CMAKE_CURRENT_LIST_DIR}/Rules.h
    ${CMAKE_CURRENT_LIST_DIR}/Settings.h
    ${CMAKE_CURRENT_LIST_DIR}/TextStyles.h
    ${CMAKE_CURRENT_LIST_DIR}/TopoR_PCB_File.h
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(${PROJECT_NAME} PRIVATE
    # Qt${QT_VERSION_MAJOR}::Core
    # Qt${QT_VERSION_MAJOR}::Gui
    # Qt${QT_VERSION_MAJOR}::Xml
    Qt${QT_VERSION_MAJOR}::Widgets
)
