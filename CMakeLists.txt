MESSAGE( STATUS ">> -------------------------------------------------------------------- <<" )
MESSAGE( STATUS ">> ----------------------- RANGES ------------------------------------- <<" )

######### CMake Version ###############################################
cmake_minimum_required( VERSION 3.9 FATAL_ERROR )
### We need at least C++17
set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
### Distinction between Clang and AppleClang
cmake_policy( SET CMP0025 NEW )
#######################################################################


### Set the cmake subdirectory
# list( APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMake" )


######### Meta information about the project ##########################
set( META_PROJECT_NAME         "ranges-syntax" )
set( META_PROJECT_DESCRIPTION  "..." )
#######################################################################


######### Project Name ################################################
project( RANGES )
#######################################################################



######### Where to search for library headers #########################
set( RANGES_INCLUDE_DIRS 
     ${PROJECT_SOURCE_DIR} 
     ${PROJECT_SOURCE_DIR}/include )
include_directories( ${RANGES_INCLUDE_DIRS} )
#######################################################################



add_executable( ${PROJECT_NAME} main.cpp )



MESSAGE( STATUS ">> ----------------------- RANGES done -------------------------------- <<" )
MESSAGE( STATUS ">> -------------------------------------------------------------------- <<" )