cmake_minimum_required(VERSION 3.16)

project(Practica_4 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Practica_4 main.cpp
    enrutador.h enrutador.cpp
    red.h red.cpp
    Data.txt
)

include(GNUInstallDirs)
install(TARGETS Practica_4
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
