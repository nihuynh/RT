cmake_minimum_required(VERSION 3.13)
project(RT C)

set(CMAKE_C_STANDARD 11)

#set(CMAKE_VERBOSE_MAKEFILE TRUE)

add_executable(RT "")

set(DEBUG_FLAGS -g3)
set(RELEASE_FLAGS -O2 -march=native -flto)
set(PROFILE_FLAGS -g3 -O2 -march=native)

add_compile_options(-Wall -Wextra -Werror)
add_compile_options("$<$<CONFIG:DEBUG>:${DEBUG_FLAGS}>")
add_compile_options("$<$<CONFIG:RELEASE>:${RELEASE_FLAGS}>")
add_compile_options("$<$<CONFIG:PROFILE>:${PROFILE_FLAGS}>")

add_subdirectory(lib/libft)
add_subdirectory(lib/libui)
add_subdirectory(lib/librt)

target_link_libraries(RT ft)
target_link_libraries(RT ui)
target_link_libraries(RT rt)

target_include_directories(RT PRIVATE includes)

# Output the executable at the root
set_target_properties(RT
        PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})

target_sources(RT PRIVATE
        srcs/camera.c
        srcs/init.c
        srcs/cast.c
        srcs/update.c
        srcs/error.c
        srcs/key_mapping.c
        srcs/light.c
        srcs/main.c
        srcs/parse_toolbox.c
        srcs/parser.c
        srcs/read.c
        srcs/render.c
        srcs/setter.c)
