/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtstruct.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 00:44:05 by nihuynh           #+#    #+#             */
/*   Updated: 2019/04/26 16:04:22 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTSTRUCT_H
# define RTSTRUCT_H

# include <stdbool.h>
# include <stdint.h>
# include "color.h"

typedef struct	s_vec3
{
	float		x;
	float		y;
	float		z;
}				t_vec3;

typedef t_vec3	t_pt3;

typedef struct	s_matrix
{
	float		m[3][3];
}				t_matrix;

typedef struct	s_ray
{
	t_pt3		origin;
	t_vec3		dir;
}				t_ray;

typedef struct	s_plane
{
	t_pt3		origin;
	t_vec3		n;
	t_vec3		x;
	t_vec3		y;
	float		size_x;
	float		size_y;
	float		rotation;
}				t_plane;

typedef struct	s_sphere
{
	t_pt3		origin;
	float		radius;
}				t_sphere;

typedef struct	s_cone
{
	t_pt3		origin;
	t_vec3		n;
	float		theta;
	float		size;
}				t_cone;

typedef struct	s_cylinder
{
	t_pt3		origin;
	t_vec3		n;
	float		radius;
	float		size;
}				t_cylinder;

typedef struct	s_light
{
	t_pt3		origin;
	t_color		color;
	float		intensity;
}				t_light;

typedef struct	s_cam
{
	t_pt3		pos;
	t_vec3		dir;
	t_matrix	rotation;
	float		y_angle;
	float		x_angle;
	bool		move_forward;
	bool		move_backward;
	bool		strafe_left;
	bool		strafe_right;
	bool		move_upward;
	bool		move_downward;
	bool		rotate_up;
	bool		rotate_down;
	bool		rotate_left;
	bool		rotate_right;
}				t_cam;

/*
** @brief Struct for material caracteristics
** http://www.lama.univ-savoie.fr/pagesmembres/lachaud/Cours/INFO805/Tests/html/
** Material_8h_source.html
*/

typedef t_color	(*f_texture)(float x, float y);

typedef struct	s_material
{
	char		*name;
	t_color		color_diffuse;
	t_color		color_specular;
	t_color		self_light;
	float		spec_idx;
	float		spec_power;
	t_color		refraction_color;
	t_color		reflection_color;
	float		refraction_idx;
	f_texture	f_texture;
}				t_material;

typedef struct s_obj	t_obj;
typedef struct s_inter	t_inter;

/*
** @brief Struct that hold the intersection.
** dist 		: minimal distant at the inter
** obj 			: object touch by the ray
** ray 			: Ray information
** point		: Intersection point
** n 			: Normal of the object at the inter
** reflected	: Vector director of the ray after the inter
** find_normal	: Methode to find the normal of the object hit
*/

struct			s_inter
{
	float		dist;
	t_obj		*obj;
	t_ray		ray;
	t_pt3		point;
	t_vec3		n;
	t_ray		deflected;
};

/*
** @brief Struct that hold any shape and is in a t_list
** type 		: Type of the shape
** shape 		: Pointer to shape data
** material 	: Material caracteristics
** diffuse 		: Outdated
** f_inter		: final color of the pixel
*/

struct			s_obj
{
	int			type;
	void		*shape;
	t_material	material;
	void		(*f_inter) (t_inter*, t_obj*);
	void		(*find_normal) (t_inter*);
	t_vec3		(*get_uv) (t_inter*);
	void		(*f_gui) (void*);
};

#endif
