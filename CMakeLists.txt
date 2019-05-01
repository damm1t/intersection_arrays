cmake_minimum_required(VERSION 2.8)

project(VK)

include_directories(${VK_SOURCE_DIR})

add_executable(array_checker_testing
        array_checker_testing.cpp
        array_checker.h
        array_checker.cpp
        gtest/gtest-all.cc
        gtest/gtest.h
        gtest/gtest_main.cc)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11 -pedantic")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address,undefined -D_GLIBCXX_DEBUG")
endif()

target_link_libraries(array_checker_testing -lgmp -lgmpxx -lpthread)