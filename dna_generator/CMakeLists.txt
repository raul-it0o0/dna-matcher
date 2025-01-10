cmake_minimum_required(VERSION 3.28)
project(DNASequenceGenerator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../../bin)

add_executable(dna_generator main.cpp
        src/dna_generator.cpp)

target_include_directories(dna_generator PUBLIC include)