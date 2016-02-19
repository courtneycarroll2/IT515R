cmake_minimum_required(VERSION 2.6.4)

# Don't set g++ or cc+, let it find the ones to use

project(gridproject)

#Bring headers into project (file.h)
include_directories(include)

#Make file executable
add_executable(phase2initial phase2initial.cc)
add_executable(phase2final phase2final.cc)
add_executable(phase2cin phase2cin.cc)

#Set target properties: enable C++ 14
set_target_properties(phase2initial phase2final phase2cin PROPERTIES 
	CXX_STANDARD 14
	CXX_EXTENSIONS FALSE
	CXX_STANDARD_REQUIRED TRUE
)


