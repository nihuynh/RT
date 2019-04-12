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

#################     SDL

find_package(SDL2 REQUIRED)

# Stay compatible with old style find_package results
if (NOT TARGET SDL2::SDL2)
    message("SDL2 found with old style cmake config")
    target_link_libraries(imgui_impl ${SDL2_LIBRARIES})
    target_include_directories(imgui_impl PUBLIC ${SDL2_INCLUDE_DIRS})
else()
    message("SDL2 found with modern style cmake config")
    target_link_libraries(imgui_impl SDL2::SDL2)
endif()

##########################

target_sources(imgui_impl PRIVATE
        imgui_impl_opengl2.cpp
        imgui_impl_sdl.cpp)
