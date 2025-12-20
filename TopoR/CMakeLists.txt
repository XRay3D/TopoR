cmake_minimum_required(VERSION 3.20)

project(TopoR LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(QT NAMES Qt6 Core Widgets)
find_package(
  Qt6
  COMPONENTS Core Widgets
  REQUIRED)

add_library(${PROJECT_NAME} STATIC)

file(GLOB SRC ${CMAKE_CURRENT_LIST_DIR}/*.cpp)
file(GLOB HEADER ${CMAKE_CURRENT_LIST_DIR}/*.h)

target_sources(${PROJECT_NAME} PRIVATE ${SRC} #[[PUBLIC]] ${HEADER})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets Qt6::Core)
