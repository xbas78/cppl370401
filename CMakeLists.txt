cmake_minimum_required(VERSION 3.23)
project(CPPL370401)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(CPPL370401 main.cpp
                          calculatormainwindow.h
                          calculatormainwindow.cpp
                          mainwindow.h
                          mainwindow.cpp)

target_link_libraries(CPPL370401
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        )