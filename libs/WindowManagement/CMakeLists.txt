find_package(Qt6 REQUIRED COMPONENTS Widgets Gui Core)

set(WINDOW_SOURCES
    MainWindow.cpp
    Windows/MainMenu.cpp
    Windows/EducationalSection.cpp
    Windows/Settings.cpp
    Windows/Constructor.cpp
    Windows/LessonConstructor.cpp
    Windows/ConstructorScheme.cpp
    Windows/TopicsPage.cpp
    Windows/Lesson.cpp
    Windows/Settings/InterfaceSettings.cpp

)

set(WINDOW_HEADERS
    MainWindow.h
    Windows/MainMenu.h
    Windows/EducationalSection.h
    Windows/Settings.h
    Windows/Constructor.h
    Windows/LessonConstructor.h
    Windows/ConstructorScheme.h
    Windows/TopicsPage.h 
    Windows/Lesson.h
    Windows/Settings/InterfaceSettings.h

    # Languages
    LanguageManager/LangManager.h 

)

add_library(WindowManagement ${WINDOW_SOURCES} ${WINDOW_HEADERS})

target_link_libraries(WindowManagement PUBLIC Qt6::Widgets Qt6::Gui Qt6::Core)

set_target_properties(WindowManagement PROPERTIES AUTOMOC ON)

target_include_directories(WindowManagement PUBLIC .)

