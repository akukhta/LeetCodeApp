cmake_minimum_required(VERSION 3.5)

project(LeetCodeApp VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (UNIX)
	set(CMAKE_PREFIX_PATH "C:/Qt/6.2.2/msvc2019_64/lib/cmake")
endif(UNIX)

if (WIN32)
	set(CMAKE_PREFIX_PATH "C:/Qt/6.2.2/msvc2019_64/lib/cmake")
endif(WIN32)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

if (UNIX)
	find_package(CURL REQUIRED)
endif(UNIX)

set(PROJECT_SOURCES
	src/UI/LeetCodeDesktop.ui
	src/UI/LeetCodeDesktop.h
	src/UI/LeetCodeDesktop.cpp
	src/UI/NavWidget.ui
	src/UI/NavWidget.h
	src/UI/NavWidget.cpp
	src/UI/ProblemWidget.h
	src/UI/ProblemWidget.cpp
	src/UI/ProblemWidget.ui
	src/UI/LoginWidget.ui
	src/UI/WindowTool.h
	src/UI/WindowTool.cpp
	src/UI/WindowTool.ui
	src/UI/LoginWidget.h
	src/UI/TaskViewer.h
	src/UI/TaskViewer.ui
	src/UI/TaskViewer.cpp
	src/UI/LoginWidget.cpp
	src/UI/UserWidget.h
	src/UI/UserWidget.cpp
	src/UI/UserWidget.ui
	src/API/RequestManager.h
	src/API/RequestManager.cpp
	src/Common/DefaultSizeable.h
	src/Common/ProblemWidgetData.h
	src/Common/CookieHandler.h
	src/Common/RunCodeResult.h
        src/Common/main.cpp
	src/Common/User.h
	src/Data/CachedStorage.h
	src/Data/CachedStorage.cpp
	src/Data/JsonManager.h
	src/Data/JsonManager.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(LeetCodeApp
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET LeetCodeApp APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(LeetCodeApp SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(LeetCodeApp
            ${PROJECT_SOURCES}
        )
    endif()
endif()

if (UNIX)
	message("UNIX")
	target_link_libraries(LeetCodeApp PRIVATE Qt${QT_VERSION_MAJOR}::Widgets  ${CURL_LIBRARIES} pthread)
endif(UNIX)

if (WIN32)
	message("WIN32")
	target_link_libraries(LeetCodeApp PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
endif(WIN32)

set_target_properties(LeetCodeApp PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(LeetCodeApp)
endif()
