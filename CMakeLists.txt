cmake_minimum_required(VERSION 3.16)

project(SlayTheShrike VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Multimedia)
find_package(Qt6 REQUIRED COMPONENTS MultimediaWidgets)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

include_directories(View/include/character/)
include_directories(View/src/character/)
include_directories(View/include/card/)
include_directories(View/src/card/)
include_directories(ViewModel/include/card/)
include_directories(ViewModel/src/card/)
include_directories(Model/include/card/)
include_directories(Model/src/card/)
include_directories(Model/include/buff/)
include_directories(Model/src/buff/)
include_directories(Model/include/character/)
include_directories(Model/src/character/)
include_directories(View/include/page/)
include_directories(View/src/page/)
include_directories(View/include/play/)
include_directories(View/src/play/)
include_directories(ViewModel/include/character/)
include_directories(ViewModel/src/character/)
include_directories(ViewModel/include/combat)
include_directories(ViewModel/src/combat)
include_directories(App)
include_directories(Common)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    find_package(Qt6 REQUIRED COMPONENTS Widgets)

    qt_add_executable(SlayTheShrike
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        res.qrc
        View/include/card/Card.h View/src/card/Card.cpp
        Model/include/buff/Buff.h Model/src/buff/Buff.cpp
        ViewModel/include/card/Card_Manager.h ViewModel/src/card/Card_Manager.cpp
        Model/include/card/Card_Meta.h Model/src/card/Card_Meta.cpp

        View/include/character/Healthbar.h View/src/character/Healthbar.cpp
        View/src/card/Card_Button.cpp
        View/include/card/Card_Button.h
        Model/src/card/CardController.cpp
        Model/include/card/CardController.h
        Music_Manager.cpp
        Music_Manager.h
        View/src/card/CardView.cpp
        View/include/card/CardView.h
        View/src/card/CardAnimation.cpp
        View/include/card/CardAnimation.h
        View/src/card/CardPileAnimation.cpp
        View/include/card/CardPileAnimation.h
        View/src/card/CardPile.cpp
        View/include/card/CardPile.h

        View/include/page/PageManager.h
        View/src/page/PageManager.cpp

        View/src/card/HoverButton.cpp
        View/include/card/HoverButton.h

        View/src/play/Arrow.cpp
        View/include/play/Arrow.h

        View/src/character/Manabar.cpp
        View/include/character/Manabar.h
        View/include/character/CharacterAnimation.h
        View/src/character/CharacterAnimation.cpp
        View/include/character/PlayerAnimation.h
        View/src/character/PlayerAnimation.cpp
        View/include/character/EnemyAnimation.h
        View/src/character/EnemyAnimation.cpp
        Defs.h
        View/include/page/CardRewardPage.h
        View/src/page/CardRewardPage.cpp
        View/src/card/CardReward.cpp
            View/include/card/CardReward.h
        Model/src/card/CardGenerator.cpp
            Model/include/card/CardGenerator.h
        Model/include/character/CharacterMeta.h
        Model/include/character/PlayerMeta.h
        Model/include/character/EnemyMeta.h
        Model/src/character/CharacterMeta.cpp
        Model/src/character/PlayerMeta.cpp
        Model/src/character/EnemyMeta.cpp

        ViewModel/include/character/Enemy.h
        ViewModel/src/character/Enemy.cpp
        ViewModel/include/character/Player.h
        ViewModel/src/character/Player.cpp
            View/include/page/HomePage.h
            View/src/page/HomePage.cpp
            View/src/page/MapPage.cpp
            View/include/page/MapPage.h
            View/include/page/BattlePage.h
            View/src/page/BattlePage.cpp
            ViewModel/include/combat/Combat.h
            ViewModel/src/combat/Combat.cpp
            App/MainApp.cpp
            App/MainApp.h
            View/src/play/CombatView.cpp
            View/include/play/CombatView.h
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET SlayTheShrike APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(SlayTheShrike SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(SlayTheShrike
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(SlayTheShrike PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(SlayTheShrike PRIVATE Qt6::Widgets)
target_link_libraries(SlayTheShrike PRIVATE Qt6::Multimedia)
target_link_libraries(SlayTheShrike PRIVATE Qt6::MultimediaWidgets)
# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.SlayTheShrike)
endif()
set_target_properties(SlayTheShrike PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS SlayTheShrike
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(SlayTheShrike)
endif()
