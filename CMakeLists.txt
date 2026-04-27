cmake_minimum_required(VERSION 3.16)

project(LogicGateSimulator VERSION 1.0 LANGUAGES CXX)

# Neovim compatability with Qt
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Qt compatability
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Gui Core)

# Custom libs
add_subdirectory(
    libs/MyLib
)

add_executable(LogicGateSimulator src/main.cpp)

target_link_libraries(LogicGateSimulator PRIVATE 
    Qt6::Widgets
    MyLib
)

