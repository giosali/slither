cmake_minimum_required(VERSION 3.28)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
    message(FATAL_ERROR "Do not build in-source. Please remove CMakeCache.txt and the CMakeFiles/ directory. Then build out-of-source.")
endif()

project(slither VERSION 0.1.0 LANGUAGES CXX)

set(PROJECT_SOURCES
    src/gesture.cpp
    src/gestureevent.cpp
    src/gestureeventfactory.cpp
    src/gesturesfile.cpp
    src/gesturewatcher.cpp
    src/holdgestureevent.cpp
    src/inputinjector.cpp
    src/main.cpp
    src/paths.cpp
    src/pinchgestureevent.cpp
    src/swipegestureevent.cpp
)

add_executable(${CMAKE_PROJECT_NAME}
    ${PROJECT_SOURCES}
)

target_compile_features(${CMAKE_PROJECT_NAME} PRIVATE cxx_std_20)

# https://stackoverflow.com/a/29316084/18831815
find_package(PkgConfig)
pkg_check_modules(LIBEVDEV REQUIRED libevdev)
pkg_check_modules(LIBINPUT REQUIRED libinput)
pkg_check_modules(LIBUDEV REQUIRED libudev)
pkg_check_modules(SPDLOG REQUIRED spdlog)

target_link_libraries(${CMAKE_PROJECT_NAME}
    ${LIBEVDEV_LIBRARIES}
    ${LIBINPUT_LIBRARIES}
    ${LIBUDEV_LIBRARIES}
    ${SPDLOG_LIBRARIES}
)
