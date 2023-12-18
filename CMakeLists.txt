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

set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CMAKE_COMMAND} -E time")
set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK "${CMAKE_COMMAND} -E time")

project(TopoRTest LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}_${CMAKE_CXX_COMPILER_ID})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})

add_definitions(
    -DQT_MESSAGELOGCONTEXT #qDebug()
    -DQT_DISABLE_DEPRECATED_BEFORE=0x060000
)

find_package(QT NAMES Qt6 Qt5 Core)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Gui Widgets Xml REQUIRED)

add_compile_options(
    $<$<CXX_COMPILER_ID:MSVC>:/bigobj># deep template instantiation
    # $<$<CXX_COMPILER_ID:GNU>:-rdynamic># stacktrace
    # $<$<CXX_COMPILER_ID:GNU>:-lstdc++_libbacktrace># stacktrace
    #- fconstexpr - depth = 50
    #- fpermissive
)

# add_link_options(
#     $<$<CXX_COMPILER_ID:GNU>:-lstdc++_libbacktrace># stacktrace
# )

#file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
# file(GLOB_RECURSE JSONS ${CMAKE_CURRENT_SOURCE_DIR}/*.json)
# file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
# file(GLOB_RECURSE UIS ${CMAKE_CURRENT_SOURCE_DIR}/*.ui)

find_package(Boost)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIR})
    message(${Boost_INCLUDE_DIR})
else()
    message(FATAL_ERROR "Boost not found!!!")
endif()

include_directories(
    pfr_non_boost/include
    compile-time-regular-expressions/single-header
)

set(FST
    # /home/x-ray/Документы/TopoR/Examples/Example_04/Arcs.fst
    # /home/x-ray/Документы/TopoR/Examples/Example_04/Arcs_standard_routing.fst
    # /home/x-ray/Документы/TopoR/Examples/Example_05/MinVia.fst
    # /home/x-ray/Документы/TopoR/Examples/Example_05/MinVia_standard_routing.fst
    # /home/x-ray/Документы/TopoR/Examples/Example_02/Placement.fst
    # /home/x-ray/Документы/TopoR/Examples/Example_02/Placement_standard_routing.fst
    # /home/x-ray/Документы/TopoR/Examples/Example_06/Signals.fst
    # /home/x-ray/Документы/TopoR/Examples/Example_01/SingleLayer.fst
    # /home/x-ray/Документы/TopoR/Examples/Example_03/arz_2L.fst
    # /home/x-ray/Документы/TopoR/Examples/Example_03/arz_4L.fst
    # /home/x-ray/Документы/TopoR/Examples/Example_03/arz_standard_routing.fst
)

add_executable(${PROJECT_NAME}
    # ${HEADERS}
    # ${JSONS}
    # ${SOURCES}
    # ${UIS}
    magicgetruntime.h
    main.cpp
    xmlserializer.cpp
    xmlserializer.h
    mainwindow.h
    mainwindow.cpp
    mainwindow.ui
    graphicsview.h
    graphicsview.cpp

    treeitem.h
    treemodel.h
    treeitem.cpp
    treemodel.cpp
    listmodel.h listmodel.cpp
    tablemodel.h tablemodel.cpp
    xmlserializertypes.h
    # Coordinates.h
)

# include_directories(${CMAKE_CURRENT_SOURCE_DIR})
# set_source_files_properties(${CMAKE_CURRENT_SOURCE_DIR}/mainwindow.cpp
#     PROPERTIES GENERATED TRUE)

link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

target_link_libraries(${PROJECT_NAME} PRIVATE
    TopoR
    # "stdc++_libbacktrace"
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Xml
)

add_subdirectory(TopoR)



# if(WIN32)
#     target_link_libraries(${PROJECT_NAME} PRIVATE setupapi)
#     # windeployqt
#     set(CMAKE_INSTALL_UCRT_LIBRARIES TRUE)
#     get_target_property(_QMAKE_EXECUTABLE Qt${QT_VERSION_MAJOR}::qmake IMPORTED_LOCATION)
#     get_filename_component(_QT_BIN_DIR "${_QMAKE_EXECUTABLE}" DIRECTORY)
#     find_program(WINDEPLOYQT_EXECUTABLE windeployqt HINTS "${_QT_BIN_DIR}")
#     add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#         COMMAND "${CMAKE_COMMAND}" -E
#         env PATH="${_QT_BIN_DIR}" "${WINDEPLOYQT_EXECUTABLE}"
#         --verbose 1
#         --no-compiler-runtime
#         \"$<TARGET_FILE:${PROJECT_NAME}>\"
#         COMMENT "Deploying Qt..."
#     )
# elseif (UNIX)#LINUX
#     #    cqtdeployer -bin myApp -qmake path/to/Qt/5.x.x/build/bin/qmake -qmlDir path/to/my/qml/files/dir qif
# endif()

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    # target_link_libraries(${PROJECT_NAME} PRIVATE setupapi)
    # windeployqt
    # set(CMAKE_INSTALL_UCRT_LIBRARIES TRUE)
    # get_target_property(EXECUTABLE "C:/Program Files/Git/usr/bin/touch.exe" IMPORTED_LOCATION)
    # get_filename_component(_QT_BIN_DIR "${EXECUTABLE}" DIRECTORY)
    # find_program(WINDEPLOYQT_EXECUTABLE windeployqt HINTS "${_QT_BIN_DIR}")
    add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
        COMMAND "C:/Program Files/Git/usr/bin/touch.exe"
        "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
        COMMENT "TOUCH Cruth..."
    )
endif()




# C:\Program Files\Git\usr\bin\touch.exe
