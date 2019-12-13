cmake_minimum_required(VERSION 3.5)
project(computerv2)

set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(SOURCES
        src/main.cpp
        src/LexerParser.cpp
        src/Operand.cpp
		src/Rational.cpp
		src/Complex.cpp
		src/Matrix.cpp
		src/Monomial.cpp
		src/Token.cpp
		src/Equation.cpp
		src/Variable.cpp
        src/Computor.cpp
        )

set(HEADERS
        inc/LexerParser.hpp
        inc/Operand.hpp
        inc/Rational.hpp
        inc/Complex.hpp
		inc/Matrix.hpp
		inc/Monomial.hpp
		inc/Token.hpp
		inc/Equation.hpp
        inc/Variable.hpp
        inc/Computor.hpp
        )

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

add_executable(computerv2 ${SOURCES} ${HEADERS})
