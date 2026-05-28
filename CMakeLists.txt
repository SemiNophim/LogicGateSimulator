cmake_minimum_required(VERSION 3.16)

project(LogicGateSimulator VERSION 1.0 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Qt compatability
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Gui Core Network)

# Directories
set(OUTPUT_DIR "${CMAKE_BINARY_DIR}/LogicGateSim")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})

# Custom libs
add_subdirectory(libs/Elements)
add_subdirectory(libs/WindowManagement)

add_executable(LogicGateSimulator 
    src/main.cpp
    src/LangInit.h

    resources.qrc
)

target_link_libraries(LogicGateSimulator PRIVATE 
    Qt6::Widgets
    Qt6::Network
    WindowManagement
)

# Translations
add_custom_command(TARGET LogicGateSimulator POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "${OUTPUT_DIR}/locales"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/locales"
        "${OUTPUT_DIR}/locales"
    COMMENT "Copying translation files to the output directory..."
)

# Lessons
add_custom_command(TARGET LogicGateSimulator POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "${OUTPUT_DIR}/lessons"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/resources/lessons"
        "${OUTPUT_DIR}/lessons"
    COMMENT "Copying lessons files to the output directory..."
)

# Config
add_custom_command(TARGET LogicGateSimulator POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/resources/configs"
        "${OUTPUT_DIR}"
    COMMENT "Copying config files to the output directory..."
)

