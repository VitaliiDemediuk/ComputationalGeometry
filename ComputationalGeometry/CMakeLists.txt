cmake_minimum_required(VERSION 3.5)

project(ComputationalGeometry VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        MainWindow.cpp
        MainWindow.h
        MainWindow.ui

        CustomQt/CustomGraphicsView.h
        CustomQt/CustomGraphicsView.cpp
        CustomQt/CustomGraphicsScene.h
        CustomQt/CustomGraphicsScene.cpp
        CustomQt/LineListModel.h
        CustomQt/LineListModel.cpp

        Dialogs/AddLineDialog.h
        Dialogs/AddLineDialog.cpp
        Dialogs/AddLineDialog.ui

        Utils/LineList.h
        Utils/LineList.cpp
)

include_directories(${PROJECT_SOURCE_DIR}/CustomQt)
include_directories(${PROJECT_SOURCE_DIR}/Dialogs)
include_directories(${PROJECT_SOURCE_DIR}/Utils)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(ComputationalGeometry
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    add_executable(ComputationalGeometry
        ${PROJECT_SOURCES}
    )
endif()

target_link_libraries(ComputationalGeometry PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(ComputationalGeometry PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(ComputationalGeometry)
endif()
