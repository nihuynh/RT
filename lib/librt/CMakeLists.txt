cmake_minimum_required(VERSION 3.13)
project(rt C)

add_library(rt "")

target_include_directories(rt PUBLIC includes)
target_include_directories(rt PRIVATE ../libft/includes)

target_sources(rt PRIVATE
        srcs/color_cpy.c
        srcs/inter_cone.c
        srcs/inter_cylinder.c
        srcs/inter_find.c
        srcs/inter_plane.c
        srcs/inter_set.c
        srcs/inter_setdeflect.c
        srcs/inter_setlight.c
        srcs/inter_setrefract.c
        srcs/inter_sphere.c
        srcs/mat3_rot.c
        srcs/normal_cone.c
        srcs/normal_cylinder.c
        srcs/normal_plane.c
        srcs/normal_sphere.c
        srcs/print_matrix.c
        srcs/ray_new.c
        srcs/vec3_add.c
        srcs/vec3_cos.c
        srcs/vec3_cpy.c
        srcs/vec3_cross.c
        srcs/vec3_deflect.c
        srcs/vec3_dot.c
        srcs/vec3_find.c
        srcs/vec3_mag.c
        srcs/vec3_matrix_apply.c
        srcs/vec3_matrix_mult.c
        srcs/vec3_new.c
        srcs/vec3_normalize.c
        srcs/vec3_print.c
        srcs/vec3_refract.c
        srcs/vec3_scalar.c
        srcs/vec3_sub.c)