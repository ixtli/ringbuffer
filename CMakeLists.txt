cmake_minimum_required (VERSION 2.6)

project (RingBuffer)

add_subdirectory ("${PROJECT_SOURCE_DIR}/src")

add_executable (ringbuffer ${SOURCE})


