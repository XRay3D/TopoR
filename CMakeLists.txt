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
  COMPONENTS Gui Widgets Xml
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

include(FetchContent)

# FetchContent_Declare( pfr GIT_REPOSITORY
# "https://github.com/apolukhin/pfr_non_boost.git" GIT_TAG master)
FetchContent_Declare(
  ctre
  GIT_REPOSITORY
    "https://github.com/hanickadot/compile-time-regular-expressions.git"
  GIT_TAG main)
FetchContent_MakeAvailable(#[[pfr]] ctre)

file(GLOB_RECURSE FST *.fst)
add_custom_target(FST_Test SOURCES ${FST})

file(GLOB SOURCES *.cpp *.h *.ui)

add_executable(${PROJECT_NAME} ${SOURCES})

link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

add_subdirectory(XmlSerializer)
add_subdirectory(TopoR)

target_link_libraries(TopoR PUBLIC XmlSerializer Qt6::Core ctre::ctre)

target_link_libraries(
  ${PROJECT_NAME}
  PRIVATE TopoR
          XmlSerializer
          unwind
          # pfr::pfr
          Qt6::Core
          Qt6::Gui
          Qt6::Widgets
          Qt6::Xml)

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
