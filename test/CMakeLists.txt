cmake_minimum_required(VERSION 3.28)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
    message(FATAL_ERROR "Do not build in-source. Please remove CMakeCache.txt and the CMakeFiles/ directory. Then build out-of-source.")
endif()

project(slither_test VERSION 0.1.0 LANGUAGES CXX)

include_directories(../include)

set(PROJECT_SOURCES
    ../src/core/gesture.cpp
    ../src/core/gestureevent.cpp
    ../src/core/gestureeventfactory.cpp
    ../src/core/gesturesfile.cpp
    ../src/core/holdgestureevent.cpp
    ../src/core/inputinjector.cpp
    ../src/core/paths.cpp
    ../src/core/pinchgestureevent.cpp
    ../src/core/swipegestureevent.cpp
    main.cpp
)

add_executable(${CMAKE_PROJECT_NAME}
    ${PROJECT_SOURCES}
)

target_compile_features(${CMAKE_PROJECT_NAME} PRIVATE cxx_std_20)

find_package(PkgConfig)
pkg_check_modules(LIBEVDEV REQUIRED libevdev)
pkg_check_modules(LIBINPUT REQUIRED libinput)
pkg_check_modules(SPDLOG REQUIRED spdlog)

target_include_directories(${CMAKE_PROJECT_NAME}
    PRIVATE
        ${LIBEVDEV_INCLUDE_DIRS}
)

target_link_libraries(${CMAKE_PROJECT_NAME}
    ${LIBEVDEV_LIBRARIES}
    ${LIBINPUT_LIBRARIES}
    ${SPDLOG_LIBRARIES}
)