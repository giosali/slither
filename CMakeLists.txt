cmake_minimum_required(VERSION 3.28)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
    message(FATAL_ERROR "Do not build in-source. Please remove CMakeCache.txt and the CMakeFiles/ directory. Then build out-of-source.")
endif()

project(slither VERSION 0.1.0 LANGUAGES CXX)

set(PROJECT_SOURCES
    src/main.cpp
)

add_executable(${CMAKE_PROJECT_NAME}
    ${PROJECT_SOURCES}
)

target_compile_features(${CMAKE_PROJECT_NAME} PRIVATE cxx_std_20)

find_package(Libinput)
target_link_libraries(${CMAKE_PROJECT_NAME}
    PRIVATE
        Libinput::Libinput
)