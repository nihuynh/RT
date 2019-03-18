/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   librt.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 00:15:12 by nihuynh           #+#    #+#             */
/*   Updated: 2019/03/15 17:36:12 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBRT_H
# define LIBRT_H

# include "rtstruct.h"
# include "color.h"

# define DEG_TO_RAD(X)	((X) * (M_PI / 180))

# define EPSILON		1e-6
# define SHADOW_BIAS	5e-2
# define HUGEVAL		1e6

# define AAAA toby[0]
# define BBBB toby[1]
# define CCCC toby[2]
# define DDDD toby[3]
# define EEEE toby[4]

/*
** Color :
*/

void		color_cpy(t_color *dst, t_color *src);

/*
** Normal :
*/

void		normal_sphere(t_inter *inter);
void		normal_cone(t_inter *inter);
void		normal_cylinder(t_inter *inter);
void		normal_plane(t_inter *inter);

/*
** Intersection :
*/

void		inter_cylinder(t_inter *data, t_obj *node);
void		inter_plane(t_inter *data, t_obj *node);
void		inter_sphere(t_inter *data, t_obj *node);
void		inter_cone(t_inter *data, t_obj *node);
void		inter_set(t_inter *inter, t_ray *ray);
void		inter_setdeflect(t_inter *inter, t_ray *res);
void		inter_setrefract(t_inter *inter, t_ray *res);
void		inter_find(t_inter *primary, t_pt3 *value);

/*
** Light :
*/

void		inter_setlight(t_inter *i, t_inter *light_i, t_light *light);

/*
** Vec3 :
*/

void		vec3_find(t_pt3 *origin, t_pt3 *dest, t_vec3 *value);
void		vec3_cpy(t_vec3 *dst, t_vec3 *src);
void		vec3_new(t_vec3 *res, float x, float y, float z);
void		vec3_add(t_vec3 *res, t_vec3 *v1, t_vec3 *v2);
float		vec3_cos(t_vec3 *v1, t_vec3 *v2);
void		vec3_cross(t_vec3 *v1, t_vec3 *v2, t_vec3 *res);
float		vec3_dot(t_vec3 *v1, t_vec3 *v2);
float		vec3_mag(t_vec3 *v1);
void		vec3_normalize(t_vec3 *v1);
void		vec3_print(t_vec3 *data);
void		vec3_scalar(t_vec3 *v1, float k);
void		vec3_sub(t_vec3 *res, t_vec3 *v1, t_vec3 *v2);
void		vec3_deflect(t_inter *inter, t_ray *res);
void		vec3_refract(t_inter *inter, t_vec3 *vf, float ior);
void		vec3_matrix_camera(t_matrix *matrix, t_cam *cam);
void		vec3_matrix_mult(t_matrix *matrix, t_matrix *add);
t_matrix	matrix_mult(const t_matrix *lhs, const t_matrix *rhs);
t_vec3		get_column(t_matrix m, int column);
void		apply_matrix(t_vec3 *v, t_matrix *mat);
void		ray_new(t_ray *res, t_pt3 *origin, t_vec3 *n);
void		print_matrix(t_matrix *mat);
void		mat3_rot(t_matrix *mat_x, t_matrix *mat_y, t_vec3 *vi, t_cam *cam);
t_matrix	set_rotation(float yz_angle, float xz_angle);
void		fresnel(t_inter *inter, float ior);

#endif
