cmake_minimum_required(VERSION 3.0.0)
project(VolumetricRenderer)
set(PROJECT_BRIEF "VolumetricRenderer")

set(CMAKE_AUTOMOC ON)

set(CMAKE_BUILD_TYPE RELEASE)
set(GCC_COMPILE_FLAGS "-std=c++11 -Wall -O3 -g -static")
set(GCC_LINK_FLAGS "")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COMPILE_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_LINK_FLAGS}")


#qt
find_package(Qt5 COMPONENTS Core Widgets Gui OpenGL)
include_directories(${Qt5Widgets_INCLUDE_DIRS})


add_subdirectory(src)
