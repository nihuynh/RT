cmake_minimum_required(VERSION 3.13)
project(RT C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_VERBOSE_MAKEFILE TRUE)

set(SRC
        srcs/camera.c
        srcs/error.c
        srcs/key_mapping.c
        srcs/light.c
        srcs/main.c
        srcs/parse_toolbox.c
        srcs/parser.c
        srcs/read.c
        srcs/render.c
        srcs/setter.c
        )
#        archives/archives.c

add_executable(RT ${SRC})

set(DEBUG_FLAGS -g3 -Og)
set(RELEASE_FLAGS -O2 -march=native -flto)
set(PROFILE_FLAGS -g3 -O2 -march=native)

target_compile_options(RT PRIVATE -Wall -Wextra -Werror)
target_compile_options(RT PRIVATE "$<$<CONFIG:DEBUG>:${DEBUG_FLAGS}>")
target_compile_options(RT PRIVATE "$<$<CONFIG:RELEASE>:${RELEASE_FLAGS}>")
target_compile_options(RT PRIVATE "$<$<CONFIG:PROFILE>:${PROFILE_FLAGS}>")

target_include_directories(RT PRIVATE includes)

set(LIB_DIR ../lib)

target_include_directories(RT PRIVATE ${LIB_DIR}/librt/includes)
target_link_directories(RT PRIVATE ${LIB_DIR}/librt/)
target_link_libraries(RT librt.a)

target_include_directories(RT PRIVATE ${LIB_DIR}/libft/includes)
target_link_directories(RT PRIVATE ${LIB_DIR}/libui/)
target_link_libraries(RT libui.a)

target_include_directories(RT PRIVATE ${LIB_DIR}/libui/includes)
target_link_directories(RT PRIVATE ${LIB_DIR}/libft/)
target_link_libraries(RT libft.a)

set_target_properties(RT PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})

# Add SDL2 path to list of searched paths for packages
#set(CMAKE_PREFIX_PATH "D:/Dev/Lib/SDL2-2.0.8")

find_package(SDL2 REQUIRED)

# Stay compatible with old style find_package results
if (NOT TARGET SDL2::SDL2)
    message("SDL2 found with old style cmake config")
    target_link_libraries(RT ${SDL2_LIBRARIES})
    target_include_directories(RT PRIVATE ${SDL2_INCLUDE_DIRS})
else()
    message("SDL2 found with modern style cmake config")
    target_link_libraries(fractol SDL2::SDL2)
endif()