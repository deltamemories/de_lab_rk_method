cmake_minimum_required(VERSION 3.21)
project(de_lab_rk_method LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick QuickControls2)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(de_lab_rk_method main.cpp)

qt_add_qml_module(de_lab_rk_method
    URI de_lab_rk_method
    VERSION 1.0
    QML_FILES
        main.qml
    SOURCES
        solver.cpp solver.h
        solverWrapper.cpp solverWrapper.h
)

target_link_libraries(de_lab_rk_method PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
    Qt6::QuickControls2
)
