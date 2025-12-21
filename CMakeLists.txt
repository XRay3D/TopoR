cmake_minimum_required(VERSION 3.20)

#[[
Прошло времени: 01:27. init - templates and boost::pfr
Прошло времени: 01:06. reflected enum
Прошло времени: 00:48. reflected fields
Прошло времени: 00:34. reflected attributes
]]

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


set(OPTIONAL_BUILD_TESTS OFF)
set(OPTIONAL_BUILD_PACKAGE OFF)

include(FetchContent)
FetchContent_Declare(
  optional
  GIT_REPOSITORY https://github.com/TartanLlama/optional.git
  GIT_TAG        master
)
FetchContent_MakeAvailable(optional)



add_definitions(-DQT_MESSAGELOGCONTEXT # qDebug()
                -DQT_DISABLE_DEPRECATED_BEFORE=0x060800)

if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  add_compile_options(-ftime-trace -fexpansion-statements -freflection-latest
                      -stdlib=libc++)
  add_link_options(-fuse-ld=lld -lc++ -lc++abi)
  add_definitions(-DCR=1)
else()
  add_definitions(-DGR=1 -D__glibcxx_reflection=202506L)
  add_compile_options(-freflection -stdlib=libc++)
endif()

find_package(
  Qt6
  COMPONENTS Core Gui Widgets Xml
  REQUIRED)


file(GLOB_RECURSE FST *.fst)
add_custom_target(FST_Test SOURCES ${FST})

file(GLOB SOURCES *.cpp *.h *.ui)

add_executable(${PROJECT_NAME} ${SOURCES})

#include_directories(${CMAKE_CURRENT_SOURCE_DIR})
#set_source_files_properties(${CMAKE_CURRENT_SOURCE_DIR} / mainwindow.cpp
#PROPERTIES GENERATED TRUE)

link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

#add_subdirectory(XmlSerializer)

add_subdirectory(TopoR)

add_subdirectory(littlexml)

target_link_libraries(TopoR PUBLIC lxml Qt6::Gui tl::optional)

#add_executable(Test main.cxx) target_link_libraries(Test PRIVATE TopoR)

target_link_libraries(
  ${PROJECT_NAME} PRIVATE TopoR #[[XmlSerializer]]
#[[unwind]] Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Xml)

#[[
if(WIN32_)
  target_link_libraries(${PROJECT_NAME} PRIVATE setupapi)
#windeployqt
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
#cqtdeployer - bin myApp - qmake path / to / Qt / 5.x.x / build / bin / qmake - qmlDir
#path / to / my / qml / files / dir qif
endif()
]]
