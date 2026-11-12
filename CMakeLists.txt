cmake_minimum_required(VERSION 3.16)
project(Grupo5_Decorator LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Nucleo del patron (C++ puro, sin dependencias de Qt)
add_library(core STATIC
    src/core/BasicReport.cpp
    src/core/DateDecorator.cpp
    src/core/AuthorDecorator.cpp
    src/core/SignatureDecorator.cpp
    src/core/ReportComposer.cpp)
target_include_directories(core PUBLIC src/core)


# Version consola (siempre se compila)
add_executable(decorator_console src/console/main_console.cpp)
target_link_libraries(decorator_console PRIVATE core)


# Pruebas
enable_testing()
add_executable(test_decorator tests/test_decorator.cpp)
target_link_libraries(test_decorator PRIVATE core)
add_test(NAME decorator COMMAND test_decorator)


# Version grafica con Qt (solo si Qt esta instalado)
find_package(Qt6 QUIET COMPONENTS Widgets)
if(NOT Qt6_FOUND)
    find_package(Qt5 QUIET COMPONENTS Widgets)
endif()


if(Qt6_FOUND OR Qt5_FOUND)
    set(CMAKE_AUTOMOC ON)
    add_executable(decorator_qt
        src/qt/main_qt.cpp
        src/qt/MainWindow.cpp)
    if(Qt6_FOUND)
        target_link_libraries(decorator_qt PRIVATE core Qt6::Widgets)
    else()
        target_link_libraries(decorator_qt PRIVATE core Qt5::Widgets)
    endif()
else()
    message(STATUS "Qt no encontrado: se compila solo la version consola")
endif()
