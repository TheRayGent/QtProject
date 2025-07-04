cmake_minimum_required(VERSION 3.16)

project(QtProject VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


list(APPEND CMAKE_PREFIX_PATH "C:/Qt/6.9.1/msvc2022_64")
find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()

qt_add_executable(QtProject
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        QFlowLayout.cpp
        QFlowLayout.h
        nlohmann/json.hpp
        Templates.h
        Templates.cpp
)

target_link_libraries(QtProject PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(QtProject PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS QtProject
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
