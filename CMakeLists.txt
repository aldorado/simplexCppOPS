cmake_minimum_required(VERSION 3.3)
project(simplex)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp utilities.cpp utilities.h matrice.cpp matrice.h simplex.cpp simplex.h)
add_executable(simplex ${SOURCE_FILES})