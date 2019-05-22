cmake_minimum_required(VERSION 3.13)
project(imgui_impl CXX)

#set(CMAKE_C_STANDARD 11)

#set(CMAKE_VERBOSE_MAKEFILE TRUE)

add_library(imgui_impl "")

target_include_directories(imgui_impl INTERFACE .)
target_include_directories(imgui_impl PRIVATE ../cimgui/imgui)
target_link_libraries(imgui_impl -lstdc++)

#################     OPENGL

find_package(OpenGL REQUIRED)
target_link_libraries(imgui_impl ${OPENGL_gl_LIBRARY})

#################     SDL2 + SDL2_image

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})

list(APPEND SDL2_PATH "/Users/tdarchiv/.brew")
list(APPEND SDL2_IMAGE_PATH "/Users/tdarchiv/.brew")

message("${CMAKE_MODULE_PATH}")
message("${CMAKE_PREFIX_PATH}")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

target_link_libraries(imgui_impl SDL2::Main)
target_link_libraries(imgui_impl SDL2::Image)

##########################

target_sources(imgui_impl PRIVATE
        imgui_impl_opengl2.cpp
        imgui_impl_sdl.cpp)
