cmake_minimum_required(VERSION 3.13)
project(ui C)

add_library(ui "")

target_include_directories(ui PUBLIC includes)
target_include_directories(ui PRIVATE ../libft/includes)
target_include_directories(ui PRIVATE ../imgui_impl)

# Add SDL2 path to list of searched paths for packages
#set(CMAKE_PREFIX_PATH "D:/Dev/Lib/SDL2-2.0.8")

find_package(SDL2 REQUIRED)

# Stay compatible with old style find_package results
if (NOT TARGET SDL2::SDL2)
    message("SDL2 found with old style cmake config")
    target_link_libraries(ui ${SDL2_LIBRARIES})
    target_include_directories(ui PUBLIC ${SDL2_INCLUDE_DIRS})
else()
    message("SDL2 found with modern style cmake config")
    target_link_libraries(ui SDL2::SDL2)
endif()

target_sources(ui PRIVATE
        srcs/error_sdl.c
        srcs/exit_sdl.c
        srcs/init_mthr_sdl.c
        srcs/init_sdl.c
        srcs/loop_sdl.c
        srcs/render_mthr_sdl.c
        srcs/render_sdl.c
        srcs/save_screenshot.c)
