cmake_minimum_required(VERSION 3.13)
project(rt C)

add_library(rt "")

target_include_directories(rt PUBLIC includes)
target_include_directories(rt PRIVATE ../libft/includes)

target_sources(rt PRIVATE
        srcs/color_add.c
        srcs/color_bool.c
        srcs/color_clamp.c
        srcs/color_linear_inter.c
        srcs/color_max.c
        srcs/color_mult.c
        srcs/color_scalar.c
        srcs/color_sub.c
        srcs/colortoi.c
        srcs/fresnel.c
        srcs/inter_cone.c
        srcs/inter_csg.c
        srcs/inter_csg_op.c
        srcs/inter_csg_inside.c
        srcs/inter_cylinder.c
        srcs/inter_find.c
        srcs/inter_plane.c
        srcs/inter_plane_finite.c
        srcs/inter_set.c
        srcs/inter_setdeflect.c
        srcs/inter_setlight.c
        srcs/inter_setrefract.c
        srcs/inter_sphere.c
        srcs/inter_cube.c
        srcs/inter_tore.c
        srcs/itocolor.c
        srcs/mat3.c
        srcs/mat3_rot.c
        srcs/mat_transpose.c
        srcs/mat_orbit.c
        srcs/normal_cone.c
        srcs/normal_cube.c
        srcs/normal_cylinder.c
        srcs/normal_plane.c
        srcs/normal_sphere.c
        srcs/normal_tore.c
        srcs/print_matrix.c
        srcs/ray_new.c
        srcs/ray_offset_origin.c
        srcs/ray_transform.c
        srcs/uv_mapping.c
        srcs/vec3_add.c
        srcs/vec3_mul.c
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
        srcs/vec3_spherical_cartesian.c
        srcs/vec3_sub.c)
