# CMakeLists for ClipOCV
cmake_minimum_required (VERSION 3.0 FATAL_ERROR)

project (clipocv)

# from Makefile - TODO make it work
#set(GIT_VERSION "$(shell git describe --abbrev=8 --dirty --always --tags)")
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -DVERSION=\"$(GIT_VERSION)\"")

set (CMAKE_CXX_STANDARD 11)
set(BUILD_SHARED_LIBS ON)

#SET (CMAKE_CXX_FLAGS "-fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls  -Wall -Wno-sign-compare")
SET (CMAKE_CXX_FLAGS "-Wall")


find_package(OpenCV REQUIRED core imgproc imgcodecs highgui)

add_subdirectory (src)
add_subdirectory (example)
