cmake_minimum_required(VERSION 3.13)
project(RT C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_VERBOSE_MAKEFILE TRUE)

set(DEBUG_FLAGS -g3)
set(RELEASE_FLAGS -O2 -march=native -flto)
set(PROFILE_FLAGS -g3 -O2 -march=native)

add_compile_options(-Wall -Wextra -pedantic)

#add_compile_options(-fsanitize=address -fsanitize-recover=address -g3)
#add_link_options(-fsanitize=address -fsanitize-recover=address)

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

find_package(OpenGL REQUIRED)

target_link_libraries(RT ${OPENGL_gl_LIBRARY})

target_include_directories(RT PRIVATE includes)

# Output the executable at the root
set_target_properties(RT
        PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})

target_sources(RT PRIVATE
        srcs/interface/anim_reset.c
        srcs/interface/anim_set.c
        srcs/interface/anim_toolbox.c
        srcs/interface/delete_obj.c
        srcs/interface/interface.c
        srcs/interface/new_object.c
        srcs/interface/new_object_tools.c
        srcs/interface/object_tools.c
        srcs/interface/screen_manager.c
        srcs/interface/ui_anim.c
        srcs/interface/ui_anim_selector.c
        srcs/interface/ui_anim_toolbox.c
        srcs/interface/ui_cam_win.c
        srcs/interface/ui_camera_tab.c
        srcs/interface/ui_csg.c
        srcs/interface/ui_edit_win.c
        srcs/interface/ui_file_win.c
        srcs/interface/ui_lists.c
        srcs/interface/ui_menu.c
        srcs/interface/ui_objects.c
        srcs/interface/ui_render.c
        srcs/interface/ui_render_settings.c
        srcs/interface/ui_scene_editor.c
        srcs/interface/ui_selector.c
        srcs/interface/ui_tools.c
        srcs/parser/export.c
        srcs/parser/export_anim.c
        srcs/parser/export_anim_tools.c
        srcs/parser/export_csg.c
        srcs/parser/export_shape.c
        srcs/parser/export_toolbox.c
        srcs/parser/obj_data.c
        srcs/parser/obj_name.c
        srcs/parser/parse_anim.c
        srcs/parser/parse_anim_tools.c
        srcs/parser/parse_csg.c
        srcs/parser/parse_shape.c
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
        srcs/render/normal_mapping.c
        srcs/render/perturbation.c
        srcs/render/post_process.c
        srcs/render/render.c
        srcs/render/texture_loader.c
        srcs/render/texture_toolbox.c
        srcs/render/skybox.c
        srcs/render/perlin.c
        srcs/render/perlin_texture.c
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
        srcs/tools/animate.c
        srcs/tools/free.c
        srcs/tools/free2.c
        srcs/tools/free_scene.c
        srcs/tools/get_scenes.c
        srcs/tools/hook.c
        srcs/tools/list_toolbox.c
        srcs/tools/load_tools.c
        srcs/tools/reload.c
        srcs/tools/update.c
        srcs/tools/utils.c
        srcs/key_mapping.c
        srcs/main.c)
