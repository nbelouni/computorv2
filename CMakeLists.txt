cmake_minimum_required(VERSION 3.5)
project(computerv2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(SOURCES
        src/main.cpp
        src/Computor.cpp
        src/IOperand.cpp
        )

set(HEADERS
        inc/Computor.hpp
        inc/IOperand.hpp
        )

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

add_executable(computerv2 ${SOURCES} ${HEADERS})