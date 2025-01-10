cmake_minimum_required(VERSION 3.28)
project(DNAMatcher)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../../bin)

add_executable(dna_matcher main.cpp
        src/dna_matcher.cpp
        src/TrieTree.cpp)

target_include_directories(dna_matcher PUBLIC include)