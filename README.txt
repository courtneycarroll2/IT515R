# This file explains how I built my repository and invoked CMake for my grid project.


		### Build repository ###
#Create a git repository
	#created via GitHub, named IT515R
#Cloned repository into supercomputer account, in directory ccarrol2/IT515R
	# git clone https://github.com/courtneycarroll2/IT515R.git
	# Note: my project files were already in IT515R
#Added my project files to head, adding a tag to each phase
	# git add phase1.cc
	# git commit -m "Add phase 1"
	# git tag phase1 (first 10 characters of commit ID)
	# git add phase2initial.cc phase2final.cc phase2cin.cc
	# git commit -m "Add phase 2"
	# git tag phase2 (first 10 characters of commit ID)
#Committed changes to remote repository
	# git push origin master


		## Invoke CMake ##
#Check CMake version
	#cmake -version
#Create CMakeLists.txt file
	#cmake_minimum_required(VERSION )
		#first line is minimum required CMake version, the one we
		#found from checking what version we have above
	#SET(CMAKE_C_COMPILER usr/bin/gcc)
	#SET(CMAKE_CXX_COMPILER usr/bin/g++)
		#Sets location for CMake compilers
	#project(grid)
		#Sets name of project as "gridproject"
	#include_directories(include)
		#brings headers into project
	#set(SOURCES phase1.cc phase2initial.cc phase2final.cc phase2cin.cc)
		#Sets the needed .cc sources as variable "SOURCES"
	#add_executable(gridproject ${SOURCES})
		#Uses SOURCES variable files to build "grid" program

		
		## Add CMakeLists.txt to repository ###
# git add CMakeLists.txt
# git commit -m "Add CMakeLists.txt"
# git tag phase3 (first 10 chars of commit ID) 
# git push origin master

		
		### Build the program ###
#Run cmake command on IT515R directory (contains both source code and
#CMakeLists.txt file
	#cmake .




