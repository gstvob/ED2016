cmake_minimum_required(VERSION 2.6)
 
# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")
 
# Link runTests with what we want to test and the GTest and pthread library
add_executable(avl TestesNoAVL.cpp)
target_link_libraries(avl ${GTEST_LIBRARIES} pthread)