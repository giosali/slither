cmake_minimum_required(VERSION 3.28)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
    message(FATAL_ERROR "Do not build in-source. Please remove CMakeCache.txt and the CMakeFiles/ directory. Then build out-of-source.")
endif()

project(slither_test VERSION 0.1.0 LANGUAGES CXX)

set(PROJECT_SOURCES
    ../src/gesture.cpp
    ../src/gesture.h
    ../src/gesturesfile.cpp
    ../src/gesturesfile.h
    ../src/inputinjector.cpp
    ../src/inputinjector.h
    ../src/json.hpp
    ../src/paths.cpp
    ../src/paths.h
    ../src/swipeparser.cpp
    ../src/swipeparser.h
    ../src/utils.cpp
    ../src/utils.h
    gesture_test.h
    gesturesfile_test.h
    inputinjector_test.h
    main.cpp
    paths_test.h
    swipeparser_test.h
    ut.hpp
    utils_test.h
)

add_executable(${CMAKE_PROJECT_NAME}
    ${PROJECT_SOURCES}
)

target_compile_features(${CMAKE_PROJECT_NAME} PRIVATE cxx_std_20)

find_package(PkgConfig)
pkg_check_modules(LIBEVDEV REQUIRED libevdev)

target_link_libraries(${CMAKE_PROJECT_NAME}
    ${LIBEVDEV_LIBRARIES}
)