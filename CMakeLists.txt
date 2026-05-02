cmake_minimum_required(VERSION 3.21)
project(de_lab_rk_method LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick QuickControls2 Graphs QuickLayouts Widgets PrintSupport)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(de_lab_rk_method
        main.cpp
        qcustomplot.cpp
        qcustomplot.h
)

qt_add_qml_module(de_lab_rk_method
    URI de_lab_rk_method
    VERSION 1.0
    QML_FILES
        main.qml
    SOURCES
        solver.cpp solver.h
        solverWrapper.h
)

target_link_libraries(de_lab_rk_method PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Qml
        Qt6::Quick
        Qt6::QuickControls2
        Qt6::Graphs
        Qt6::QuickLayouts
        Qt6::Widgets
        Qt6::PrintSupport
)

set_source_files_properties(qcustomplot.cpp PROPERTIES COMPILE_FLAGS "-g0 -O2")
