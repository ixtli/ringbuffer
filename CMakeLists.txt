cmake_minimum_required (VERSION 2.6)

project (RingBuffer)

add_subdirectory ("${PROJECT_SOURCE_DIR}/src")

set (CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++")

add_executable (ringbuffer ${SOURCE})

