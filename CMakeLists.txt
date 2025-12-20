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

execute_process(
  COMMAND git rev-parse --abbrev-ref HEAD
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_VARIABLE GIT_BRANCH
  OUTPUT_STRIP_TRAILING_WHITESPACE)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY
    ${CMAKE_CURRENT_SOURCE_DIR}/bin_${GIT_BRANCH}/${CMAKE_BUILD_TYPE}_${CMAKE_CXX_COMPILER_ID}
)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})

add_definitions(-DQT_DISABLE_DEPRECATED_BEFORE=0x060800)

find_package(
  Qt6
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

include(FetchContent)
FetchContent_Declare(
  pfr
  GIT_REPOSITORY "https://github.com/apolukhin/pfr_non_boost.git"
  GIT_TAG master)
FetchContent_Declare(
  ctre
  GIT_REPOSITORY
    "https://github.com/hanickadot/compile-time-regular-expressions.git"
  GIT_TAG main)
FetchContent_MakeAvailable(pfr ctre)

file(GLOB_RECURSE FST *.fst)
add_custom_target(FST_Test SOURCES ${FST})

file(GLOB SOURCES *.cpp *.h *.ui)

add_executable(${PROJECT_NAME} ${SOURCES})

# include_directories(${CMAKE_CURRENT_SOURCE_DIR})
# set_source_files_properties(${CMAKE_CURRENT_SOURCE_DIR}/mainwindow.cpp
# PROPERTIES GENERATED TRUE)

link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

add_subdirectory(XmlSerializer)
target_link_libraries(XmlSerializer PUBLIC pfr::pfr)

add_subdirectory(TopoR)
target_link_libraries(TopoR PRIVATE XmlSerializer)

target_link_libraries(${PROJECT_NAME} PRIVATE TopoR XmlSerializer Qt6::Core
                                              Qt6::Gui Qt6::Widgets Qt6::Xml)

if(WIN32_)
  target_link_libraries(${PROJECT_NAME} PRIVATE setupapi)
  # windeployqt
  set(CMAKE_INSTALL_UCRT_LIBRARIES TRUE)
  get_target_property(_QMAKE_EXECUTABLE Qt6::qmake IMPORTED_LOCATION)
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
