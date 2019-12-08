cmake_minimum_required(VERSION 3.5)
project(computerv2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(SOURCES
        src/Operand.cpp
        src/Real.cpp
        src/Complex.cpp
		src/Matrix.cpp
		src/Variable.cpp
		src/Token.cpp
		src/Function.cpp
        src/Computor.cpp
        src/LexerParser.cpp
        src/main.cpp
#        src/IOperand.cpp
        )

set(HEADERS
        inc/Operand.hpp
        inc/Real.hpp
        inc/Complex.hpp
		inc/Matrix.hpp
		inc/Variable.hpp
		inc/Function.hpp
		inc/Token.hpp
        inc/Computor.hpp
        inc/LexerParser.hpp
#        inc/IOperand.hpp
        )

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

add_executable(computerv2 ${SOURCES} ${HEADERS})
