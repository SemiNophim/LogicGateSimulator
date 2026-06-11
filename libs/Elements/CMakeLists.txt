find_package(Qt6 REQUIRED COMPONENTS Widgets Gui Core Network)

set(ELEMENT_SOURCES
    Element.cpp
    DCPower.cpp
    LED.cpp
    Wire.cpp
    Ground.cpp

)

set(ELEMENT_HEADERS
    Element.h 
    DCPower.h
    LED.h
    Wire.h
    Pin.h
    Ground.h
    PowerElement.h
    LoadElement.h

)

add_library(Elements ${ELEMENT_SOURCES} ${ELEMENT_HEADERS})

target_link_libraries(Elements PUBLIC 
    Qt6::Widgets 
    Qt6::Gui 
    Qt6::Core 
    Qt6::Network
)

set_target_properties(Elements PROPERTIES AUTOMOC ON)

target_include_directories(Elements PUBLIC .)

