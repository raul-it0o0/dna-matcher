cmake_minimum_required(VERSION 3.28)
project(PaternityChecker)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)

add_executable(PaternityChecker main.cpp
        src/utils.cpp
        include/utils.hpp)

target_include_directories(PaternityChecker PUBLIC include)