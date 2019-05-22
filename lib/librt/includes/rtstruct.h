/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtstruct.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 00:44:05 by nihuynh           #+#    #+#             */
/*   Updated: 2019/05/21 17:29:57 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTSTRUCT_H
# define RTSTRUCT_H

# include <stdbool.h>
# include <stdint.h>
# include "ftbtree.h"
# include "color.h"

typedef struct	s_vec2
{
	float		x;
	float		y;
}				t_vec2;

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
	t_vec2		size;
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
	t_vec3		x;
	t_vec3		z;
}				t_cone;

typedef struct	s_cylinder
{
	t_pt3		origin;
	t_vec3		x;
	t_vec3		n;
	t_vec3		z;
	float		radius;
	float		size;
}				t_cylinder;

typedef struct	s_csg
{
	t_pt3		origin;
	t_vec3		x;
	t_vec3		n;
	t_vec3		z;
	t_btree		*root;
}				t_csg;

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
** typedef t_color	(*f_texture)(t_texture*, float x, float y);
*/

typedef	struct s_texture	t_texture;
typedef	struct s_material	t_material;

struct			s_texture
{
	char		*name;
	char		*dir;
	t_color		(*f_texture)(t_material*, t_vec3);
	void		(*export) (int, void*);
	char		*pixels;
	int			width;
	int			height;
	char		bpp;
};

typedef struct	s_uv_mapping {
	t_vec2	offset;
	t_vec2	scale;
	bool	repeat;
}				t_uv_mapping;

struct			s_material
{
	char			*name;
	t_color			color_diffuse;
	t_color			color_specular;
	t_color			color_tex;
	float			spec_idx;
	float			spec_power;
	t_color			refraction_color;
	t_color			reflection_color;
	float			refraction_idx;
	t_texture		*tex;
	t_uv_mapping	uv_mapping;
};

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

typedef struct s_obj	t_obj;
typedef struct s_inter	t_inter;

struct			s_inter
{
	float		dist;
	float		dist_max;
	t_obj		*obj;
	t_ray		ray;
	t_pt3		point;
	t_vec3		n;
	t_ray		deflected;
};

# define INTER		1
# define INTER_STR	"INTER"
# define NOT		2
# define NOT_STR	"NOT"
# define UNION		3
# define UNION_STR	"UNION"

typedef struct	s_csg_op
{
	int			type;
	t_inter		left;
	t_inter		right;

}				t_csg_op;

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
	void		(*export) (int, void*);
};

typedef struct	s_shading {
	t_material	mat;
	t_light		light;
	t_vec3		light_dir;
	float		light_dist;
	t_vec3		hit_pos;
	t_vec3		normal;
	t_vec3		specular_dir;
	t_vec3		uv;
}				t_shading;

#endif
