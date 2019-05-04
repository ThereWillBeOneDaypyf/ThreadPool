cmake_minimum_required(VERSION 3.5)
project(tl_thread_pool VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_FLAGS "-ggdb3 -std=c++11 -pthread ${CMAKE_CXX_FLAGS} -Wall -ltcmalloc_minimal -D_FILE_OFFSET_BITS=64 -DFUSE_USE_VERSION=25")

add_library(tl_thread_pool ThreadPool.cpp)
