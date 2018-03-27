cmake_minimum_required(VERSION 3.0)
project(ColorPickerWidget)

find_package(Qt5Widgets)
find_package(Qt5Xml)
find_package(Qt5Gui)
find_package(Qt5Core)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(SRC
    src/ColorPickerWidget.cpp)

set(TESTAPP
    src/TestApp.cpp)

add_library(ColorPickerWidget STATIC ${SRC})
add_executable(TestApp ${TESTAPP})
target_link_libraries(TestApp ColorPickerWidget)

qt5_use_modules(ColorPickerWidget Core Gui Widgets)
qt5_use_modules(TestApp Core Gui Widgets)
