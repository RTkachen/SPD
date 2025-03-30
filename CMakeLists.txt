cmake_minimum_required(VERSION 3.10)
project(SPD)

# Ustawienie katalogu dla pliku wykonywalnego
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Ustawienie standardu C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Dodanie katalogu z plikami nagłówkowymi
include_directories(${CMAKE_SOURCE_DIR}/inc)

# Znalezienie wszystkich plików źródłowych (*.cpp) w katalogu src
file(GLOB SOURCES "src/*.cpp")

# Znalezienie wszystkich plików nagłówkowych (*.hpp) w katalogu inc
file(GLOB HEADERS "inc/*.hpp")

# Dodanie katalogu z plikami nagłówkowymi do CMake
include_directories(${CMAKE_SOURCE_DIR}/inc)

# Dodanie katalogu z plikami źródłowymi
add_executable(rgcmax ${SOURCES})