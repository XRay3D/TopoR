#[[#############################################################################
# Author    :  Damir Bakiev                                                    #
# Version   :  na                                                              #
# Date      :  06.02.2025                                                      #
# Website   :  na                                                              #
# Copyright :  Damir Bakiev 2016-2025                                          #
# License   :                                                                  #
# Use, modification & distribution is subject to Boost Software License Ver 1. #                                                                               #
# http://www.boost.org/LICENSE_1_0.txt                                         #
##############################################################################]]
cmake_minimum_required(VERSION 3.20)

# set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CMAKE_COMMAND} -E time")
# set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK "${CMAKE_COMMAND} -E time")

project(TopoR_Test LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY
    ${CMAKE_CURRENT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}_${CMAKE_CXX_COMPILER_ID}
)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})

add_definitions(-DQT_MESSAGELOGCONTEXT # qDebug()
                -DQT_DISABLE_DEPRECATED_BEFORE=0x060000)

find_package(QT NAMES Qt6 Qt5 Core)
find_package(
  Qt${QT_VERSION_MAJOR}
  COMPONENTS Core Gui Widgets Xml
  REQUIRED)

add_compile_options(
  $<$<CXX_COMPILER_ID:MSVC>:/bigobj> # deep template instantiation
  # $<$<CXX_COMPILER_ID:MSVC>:/X> $<$<CXX_COMPILER_ID:MSVC>:/I>
  # $<$<CXX_COMPILER_ID:MSVC>:"C:/Program Files/Microsoft Visual
  # Studio/2022/Community/VC/Tools/MSVC/14.42.34433/include">
  $<$<AND:$<BOOL:${CMAKE_HOST_WIN32}>,$<CXX_COMPILER_ID:GNU>>:-Wa,-mbig-obj>
  # $<$<CXX_COMPILER_ID:GNU>:-rdynamic># stacktrace
  # $<$<CXX_COMPILER_ID:GNU>:-lstdc++_libbacktrace># stacktrace - fconstexpr -
  # depth = 50 - fpermissive
)

# add_link_options($<$<CXX_COMPILER_ID:GNU>:-Wa,-mbig-obj>)

# file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/*.h) file(GLOB_RECURSE
# JSONS ${CMAKE_CURRENT_SOURCE_DIR}/*.json) file(GLOB_RECURSE SOURCES
# ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp) file(GLOB_RECURSE UIS
# ${CMAKE_CURRENT_SOURCE_DIR}/*.ui)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../pfr/include)
# find_package(Boost) if(Boost_FOUND) # workaround for msys2 used in msvc #
# include_directories(C:/Qt/Tools/Android/Boost-for-Android/boost_1_84_0)
# include_directories(${Boost_INCLUDE_DIR}) message(==> ${Boost_INCLUDE_DIR})
# else() message(FATAL_ERROR "Boost not found!!!") endif()

include_directories(pfr_non_boost/include
                    compile-time-regular-expressions/single-header)

file(GLOB_RECURSE FST *.fst)
add_custom_target(FST_Test SOURCES ${FST})

file(GLOB SOURCES *.cpp *.h *.ui)

add_executable(${PROJECT_NAME} ${SOURCES})

# include_directories(${CMAKE_CURRENT_SOURCE_DIR})
# set_source_files_properties(${CMAKE_CURRENT_SOURCE_DIR}/mainwindow.cpp
# PROPERTIES GENERATED TRUE)

link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

add_subdirectory(XmlSerializer)
add_subdirectory(TopoR)

target_link_libraries(TopoR PRIVATE XmlSerializer)

target_link_libraries(
  ${PROJECT_NAME}
  PRIVATE TopoR XmlSerializer Qt${QT_VERSION_MAJOR}::Core
          Qt${QT_VERSION_MAJOR}::Gui Qt${QT_VERSION_MAJOR}::Widgets
          Qt${QT_VERSION_MAJOR}::Xml)

if(WIN32_)
  target_link_libraries(${PROJECT_NAME} PRIVATE setupapi)
  # windeployqt
  set(CMAKE_INSTALL_UCRT_LIBRARIES TRUE)
  get_target_property(_QMAKE_EXECUTABLE Qt${QT_VERSION_MAJOR}::qmake
                      IMPORTED_LOCATION)
  get_filename_component(_QT_BIN_DIR "${_QMAKE_EXECUTABLE}" DIRECTORY)
  find_program(WINDEPLOYQT_EXECUTABLE windeployqt HINTS "${_QT_BIN_DIR}")
  add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND
      "${CMAKE_COMMAND}" -E env PATH="${_QT_BIN_DIR}"
      "${WINDEPLOYQT_EXECUTABLE}" --verbose 1 --no-compiler-runtime
      \"$<TARGET_FILE:${PROJECT_NAME}>\"
    COMMENT "Deploying Qt...")
elseif(UNIX) # LINUX
  # cqtdeployer -bin myApp -qmake path/to/Qt/5.x.x/build/bin/qmake -qmlDir
  # path/to/my/qml/files/dir qif
endif()

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC_")
  # target_link_libraries(${PROJECT_NAME} PRIVATE setupapi) windeployqt
  # set(CMAKE_INSTALL_UCRT_LIBRARIES TRUE) get_target_property(EXECUTABLE
  # "C:/Program Files/Git/usr/bin/touch.exe" IMPORTED_LOCATION)
  # get_filename_component(_QT_BIN_DIR "${EXECUTABLE}" DIRECTORY)
  # find_program(WINDEPLOYQT_EXECUTABLE windeployqt HINTS "${_QT_BIN_DIR}")

  # add_custom_command( TARGET ${PROJECT_NAME} PRE_BUILD COMMAND "C:/Program
  # Files/Git/usr/bin/touch.exe" "${CMAKE_CURRENT_SOURCE_DIR}/mainwindow.cpp"
  # COMMENT "TOUCH Cruth...")
endif()
