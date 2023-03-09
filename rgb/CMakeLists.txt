cmake_minimum_required(VERSION 3.14)

project(rgbSimple VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Quick)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Quick)

qt5_add_resources(QT_RESOURCES qml.qrc)

add_library(${PROJECT_NAME} SHARED
    ${QT_RESOURCES}
    rgbsimplebackend.h
    rgbsimplebackend.cpp
)

find_package(Qt5Core REQUIRED)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Quick
)

