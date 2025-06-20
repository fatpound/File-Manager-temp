cmake_minimum_required(VERSION 3.19)

project(File-Manager LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_SCAN_FOR_MODULES FALSE)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(File-Manager
    WIN32 MACOSX_BUNDLE
    main.cpp
    MainWindow.hpp MainWindow.cpp
    mainwindow.ui

    TabWidgetManager.hpp TabWidgetManager.cpp
    TableViewManager.hpp TableViewManager.cpp

    .clang-format .clang-tidy
)

include(CompileOptions.cmake)

target_link_libraries(File-Manager
    PRIVATE
        Qt::Core
        Qt::Widgets
        FatCxx::CompileOptions
)

include(GNUInstallDirs)

install(TARGETS File-Manager
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET File-Manager
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
