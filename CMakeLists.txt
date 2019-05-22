cmake_minimum_required(VERSION 3.13)
project(RT C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_VERBOSE_MAKEFILE TRUE)

set(DEBUG_FLAGS -g3)
set(RELEASE_FLAGS -O2 -march=native -flto)
set(PROFILE_FLAGS -g3 -O2 -march=native)

add_compile_options(-Wall -Wextra -pedantic)

add_compile_options(-fsanitize=address -fsanitize-recover=address -g3)
add_link_options(-fsanitize=address -fsanitize-recover=address)

add_compile_options("$<$<CONFIG:DEBUG>:${DEBUG_FLAGS}>")
add_compile_options("$<$<CONFIG:RELEASE>:${RELEASE_FLAGS}>")
add_compile_options("$<$<CONFIG:PROFILE>:${PROFILE_FLAGS}>")

add_executable(RT "")

add_subdirectory(lib/libft)
add_subdirectory(lib/librt)
add_subdirectory(lib/cimgui)
add_subdirectory(lib/imgui_impl)
target_compile_options(cimgui PRIVATE -Wno-error)

target_link_libraries(RT ft)
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
        srcs/interface/fullscreen.c
        srcs/interface/interface.c
        srcs/interface/interface_lists.c
        srcs/interface/interface_menu.c
        srcs/interface/interface_objects.c
        srcs/interface/interface_scene.c
        srcs/interface/interface_tools.c
        srcs/interface/new_object.c
        srcs/interface/new_object_tools.c
        srcs/interface/object_tools.c
        srcs/interface/ui_edit_win.c
        srcs/interface/ui_file_win.c
        srcs/interface/ui_render.c
        srcs/parser/export.c
        srcs/parser/export_csg.c
        srcs/parser/export_shape.c
        srcs/parser/export_toolbox.c
        srcs/parser/obj_data.c
        srcs/parser/parse_csg.c
        srcs/parser/parse_toolbox.c
        srcs/parser/parse_txt.c
        srcs/parser/parse_utils.c
        srcs/parser/parser.c
        srcs/parser/read.c
        srcs/parser/setter.c
        srcs/render/camera.c
        srcs/render/cast.c
        srcs/render/filters.c
        srcs/render/light.c
        srcs/render/perturbation.c
        srcs/render/post_process.c
        srcs/render/render.c
        srcs/render/texture_loader.c
        srcs/render/texture_toolbox.c
        srcs/render_utils
        srcs/render_utils/error_sdl.c
        srcs/render_utils/exit_sdl.c
        srcs/render_utils/init_mthr_sdl.c
        srcs/render_utils/init_sdl.c
        srcs/render_utils/loop_sdl.c
        srcs/render_utils/render_mthr_sdl.c
        srcs/render_utils/render_pool.c
        srcs/render_utils/render_sdl.c
        srcs/render_utils/render_time.c
        srcs/render_utils/save_screenshot.c
        srcs/tools/error.c
        srcs/tools/free.c
        srcs/tools/reload.c
        srcs/tools/update.c
        srcs/tools/utils.c
        srcs/tools/free.c
        srcs/csg.c
        srcs/key_mapping.c
        srcs/main.c)
