cmake_minimum_required(VERSION 3.16)
project(SzymanekPaulina-etap3)

set(CMAKE_CXX_STANDARD 14)

if(MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

include_directories(.)

add_executable(SzymanekPaulina-etap3
        main.cpp Magazyn.cpp Magazyn.h Paleciak.cpp Paleciak.h Produkt.cpp Produkt.h ProduktT.h)