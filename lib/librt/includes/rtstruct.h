/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtstruct.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 00:44:05 by nihuynh           #+#    #+#             */
/*   Updated: 2019/03/07 17:46:49 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTSTRUCT_H
# define RTSTRUCT_H

# include "color.h"

typedef struct	s_vec3
{
	float		x;
	float		y;
	float		z;
}				t_vec3;

typedef struct	s_pt3
{
	float		x;
	float		y;
	float		z;
}				t_pt3;

typedef struct	s_ray
{
	t_pt3		origin;
	t_vec3		n;
}				t_ray;

typedef struct	s_plane
{
	t_pt3		origin;
	t_vec3		n;
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
}				t_cone;

typedef struct	s_cylinder
{
	t_pt3		origin;
	t_vec3		n;
	float		radius;
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
}				t_cam;

typedef struct	s_matrix
{
	float		m[3][3];
}				t_matrix;

/**
** @brief Struct for material caracteristics
** reflect_idx : depend on the material
** transmit_k 	: at 0 for dialectrics
** http://www.lama.univ-savoie.fr/pagesmembres/lachaud/Cours/INFO805/Tests/html/Material_8h_source.html
*/

typedef struct	s_material
{
	char*		name;
	t_color		color_ambient;
	t_color		color_diffuse;
	t_color		color_specular;
	t_color		self_light;
	float		spec_idx;	// La "brillance" du material (utilisé pour la réfléxion et couplé avec la couleur Specular).
	float		spec_power;	// La puissance de brillance (coefficient couplé avec la valeur précédente).
	float		absorb_idx;	// Le coefficient de  transmission (utilisé pour la réfraction).
	float		deflect_idx;// Le coefficient de réfléxion (utilisé pour la réfléxion).
}				t_material;

typedef struct s_obj	t_obj;
typedef struct s_inter	t_inter;

/**
** @brief Struct that hold the intersection.
** dist 		: minimal distant at the inter
** obj 			: object touch by the ray
** ray 			: Ray information
** n 			: Normal of the object at the inter
** color		: final color of the pixel
** reflected	: Vector director of the ray after the inter
** find_normal	: Methode to find the normal of the object hit
*/

struct			s_inter
{
	float		dist;
	t_obj		*obj;
	t_ray		ray;
	t_vec3		n;
	t_color		color;
	t_ray		deflected;
	void		(*find_normal) (t_inter*);
};

/**
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
};

#endif