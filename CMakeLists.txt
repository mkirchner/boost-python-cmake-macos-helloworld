cmake_minimum_required (VERSION 3.5)

project(chello)

add_definitions('-g')
add_definitions('-Wall')
#add_definitions('-std=c++11')

#
# python libs
#
# find_package(PythonLibs 2.7 REQUIRED)
find_package(PythonLibs 3.7 REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})

#
# boost libs
#
# find_package(Boost COMPONENTS python REQUIRED)
find_package(Boost COMPONENTS python37 REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

message(STATUS "PYTHON_LIBRARIES = ${PYTHON_LIBRARIES}")
message(STATUS "PYTHON_EXECUTABLE = ${PYTHON_EXECUTABLE}")
message(STATUS "PYTHON_INCLUDE_DIRS = ${PYTHON_INCLUDE_DIRS}")
message(STATUS "Boost_LIBRARIES = ${Boost_LIBRARIES}")
 
#
# our module
#
# build the C++ lib
add_library(chello SHARED chello.cpp)
# build the boost-python wrapper
add_library(chello_ext SHARED chello_ext.cpp)
set_target_properties(chello_ext PROPERTIES PREFIX "")  # no 'lib' prefix
set_target_properties(chello_ext PROPERTIES SUFFIX ".so")  # must be .so (not .dylib)
target_link_libraries(chello_ext ${Boost_LIBRARIES} ${PYTHON_LIBRARIES} chello)
