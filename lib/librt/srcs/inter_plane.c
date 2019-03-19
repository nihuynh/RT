
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 20:19:47 by nihuynh           #+#    #+#             */
/*   Updated: 2019/03/07 16:55:04 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "librt.h"
#include <math.h>

static inline float
	inter(t_ray *ray, t_plane *plane)
{
	float	dn;
	float	nom;
	t_vec3	sub;

	dn = vec3_dot(&ray->n, &plane->n);
	if (dn > -EPSILON && dn < EPSILON)
		return (HUGEVAL);
	vec3_sub(&sub, &ray->origin, &plane->origin);
	nom = -vec3_dot(&sub, &plane->n);
	if ((dn > 0 && nom < 0) || (dn < 0 && nom > 0))
		return (HUGEVAL);
	return (nom / dn);
}

static inline int
	inter_finite(t_inter *data, t_plane *plane, float dist)
{
	t_pt3	inter_pt;
	t_vec3	origin_to_inter;
	float	scale;

	inter_pt.x = data->ray.origin.x + dist * data->ray.n.x;
	inter_pt.y = data->ray.origin.y + dist * data->ray.n.y;
	inter_pt.z = data->ray.origin.z + dist * data->ray.n.z;
	vec3_sub(&origin_to_inter, &inter_pt, &plane->origin);
	if (plane->size_x)
	{
		scale  = vec3_dot(&origin_to_inter, &plane->x) / vec3_dot(&plane->x, &plane->x);
		if (scale  > plane->size_x || scale < -plane->size_x)
			return (0);
	}
	if (plane->size_y)
	{
		scale  = vec3_dot(&origin_to_inter, &plane->y) / vec3_dot(&plane->y, &plane->y);
		if (scale  > plane->size_y || scale < -plane->size_y)
			return (0);
	}
	return (1);
}

void
	inter_plane(t_inter *data, t_obj *node)
{
	t_plane	*plane;
	float	dist;

	plane = node->shape;
	dist = inter(&data->ray, plane);
	if (dist >= data->dist || dist < 0)
		return ;
	if (plane->size_x > 0 || plane->size_y > 0)
		if (!(inter_finite(data, plane, dist)))
			return ;
	color_cpy(&data->color, &node->material.color_ambient);
	data->dist = dist;
	data->obj = node;
	data->find_normal = &normal_plane;
}
