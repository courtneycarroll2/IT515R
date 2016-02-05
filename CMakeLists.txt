cmake_minimum_required(VERSION 2.6.4)

SET(CMAKE_C_COMPILER /usr/bin/gcc)
SET(CMAKE_CXX_COMPILER /usr/bin/g++)


project(gridproject)

#Bring headers into project (file.h)
include_directories(include)

#Add sources with set command
set(SOURCES phase2initial.cc phase2final.cc phase2cin.cc)

#Make file executable
add_executable(gridproject ${SOURCES})

