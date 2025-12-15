cmake_minimum_required(VERSION 3.28)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
    message(FATAL_ERROR "Do not build in-source. Please remove CMakeCache.txt and the CMakeFiles/ directory. Then build out-of-source.")
endif()

set(CMAKE_CXX_SCAN_FOR_MODULES OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(slither VERSION 0.1.0 LANGUAGES CXX)

include_directories(${PROJECT_SOURCE_DIR}/include)

set(PROJECT_SOURCES
    src/core/directorywatcher.cpp
    src/core/gesture.cpp
    src/core/gestureevent.cpp
    src/core/gestureeventfactory.cpp
    src/core/gesturesfile.cpp
    src/core/gesturewatcher.cpp
    src/core/holdgestureevent.cpp
    src/core/inputinjector.cpp
    src/core/paths.cpp
    src/core/pinchgestureevent.cpp
    src/core/settings.cpp
    src/core/settingsfile.cpp
    src/core/swipegestureevent.cpp
    src/core/utilities.cpp
    src/main.cpp
    src/ui/app.cpp
    src/ui/colors.cpp
    src/ui/gestureformdialog.cpp
    src/ui/gesturepage.cpp
    src/ui/gesturespage.cpp
    src/ui/mainframe.cpp
    src/ui/settingspage.cpp
)

add_executable(${CMAKE_PROJECT_NAME}
    ${PROJECT_SOURCES}
)

target_compile_features(${CMAKE_PROJECT_NAME} PRIVATE cxx_std_23)

find_package(wxWidgets REQUIRED)
include(${wxWidgets_USE_FILE})

# https://stackoverflow.com/a/29316084/18831815
find_package(PkgConfig)
pkg_check_modules(LIBEVDEV REQUIRED libevdev)
pkg_check_modules(LIBINPUT REQUIRED libinput)
pkg_check_modules(LIBUDEV REQUIRED libudev)
pkg_check_modules(SPDLOG REQUIRED spdlog)

target_include_directories(${CMAKE_PROJECT_NAME}
    PRIVATE
        ${LIBEVDEV_INCLUDE_DIRS}
)

target_link_libraries(${CMAKE_PROJECT_NAME}
    ${LIBEVDEV_LIBRARIES}
    ${LIBINPUT_LIBRARIES}
    ${LIBUDEV_LIBRARIES}
    ${SPDLOG_LIBRARIES}
    ${wxWidgets_LIBRARIES}
)
