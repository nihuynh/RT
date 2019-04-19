cmake_minimum_required(VERSION 3.13)
project(RT C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_VERBOSE_MAKEFILE TRUE)

set(DEBUG_FLAGS -g3)
set(RELEASE_FLAGS -O2 -march=native -flto)
set(PROFILE_FLAGS -g3 -O2 -march=native)

add_compile_options(-Wall -Wextra -pedantic)

#add_compile_options(-fsanitize=address -g3)
#add_link_options(-fsanitize=address -fsanitize-recover=address)

add_compile_options("$<$<CONFIG:DEBUG>:${DEBUG_FLAGS}>")
add_compile_options("$<$<CONFIG:RELEASE>:${RELEASE_FLAGS}>")
add_compile_options("$<$<CONFIG:PROFILE>:${PROFILE_FLAGS}>")

add_executable(RT "")

add_subdirectory(lib/libft)
add_subdirectory(lib/libui)
add_subdirectory(lib/librt)
add_subdirectory(lib/cimgui)
add_subdirectory(lib/imgui_impl)
target_compile_options(cimgui PRIVATE -Wno-error)

target_link_libraries(RT ft)
target_link_libraries(RT ui)
target_link_libraries(RT rt)
target_link_libraries(RT cimgui)
target_link_libraries(RT imgui_impl)

target_include_directories(RT PRIVATE lib/cimgui)

find_package(OpenGL REQUIRED)

target_link_libraries(RT ${OPENGL_gl_LIBRARY})

target_include_directories(RT PRIVATE includes)

# Output the executable at the root
set_target_properties(RT
        PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})

target_sources(RT PRIVATE
        srcs/interface/init_interface.c
        srcs/interface/interface.c
        srcs/interface/interface_scene.c
        srcs/interface/interface_objects.c
        srcs/interface/object_tools.c
        srcs/parser/parse_toolbox.c
        srcs/parser/parser.c
        srcs/parser/read.c
        srcs/parser/setter.c
        srcs/render/camera.c
        srcs/render/cast.c
        srcs/render/light.c
        srcs/render/render.c
        srcs/render/texture.c
        srcs/tools/error.c
        srcs/tools/update.c
        srcs/tools/utils.c
        srcs/init.c
        srcs/key_mapping.c
        srcs/main.c
        )
