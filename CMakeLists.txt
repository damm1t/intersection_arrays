cmake_minimum_required(VERSION 2.8)

project(VK)

include_directories(${VK_SOURCE_DIR})

add_executable(counter_testing
        HyperLogLog.cpp
        HyperLogLog.h
        Storage.cpp
        Storage.h
        utils/MurmurHash.cpp
        utils/MurmurHash.h
        uniq_counter_testing.cpp)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11 -pedantic -O3")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address,undefined -D_GLIBCXX_DEBUG")
endif()

target_link_libraries(counter_testing -lgmp -lgmpxx -lpthread)