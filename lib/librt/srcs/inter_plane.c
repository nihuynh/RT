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

	dn = vec3_dot(&ray->dir, &plane->n);
	if (dn > -EPSILON && dn < EPSILON)
		return (HUGEVAL);
	vec3_sub(&sub, &ray->origin, &plane->origin);
	nom = -vec3_dot(&sub, &plane->n);
	if ((dn > 0 && nom < 0) || (dn < 0 && nom > 0))
		return (HUGEVAL);
	return (nom / dn);
}

static inline int
	inter_finite(t_inter *data, t_plane *plan, float dist,
			void (*f_texture)(t_color*, float, float))
{
	t_pt3	inter_pt;
	t_vec3	orig_to_inter;
	float	scale_x;
	float	scale_y;

	inter_pt.x = data->ray.origin.x + dist * data->ray.dir.x;
	inter_pt.y = data->ray.origin.y + dist * data->ray.dir.y;
	inter_pt.z = data->ray.origin.z + dist * data->ray.dir.z;
	vec3_sub(&orig_to_inter, &inter_pt, &plan->origin);
	scale_x = vec3_dot(&orig_to_inter, &plan->x) / vec3_dot(&plan->x, &plan->x);
	if (plan->size_x)
		if (scale_x > plan->size_x || scale_x < -plan->size_x)
			return (0);
	scale_y = vec3_dot(&orig_to_inter, &plan->y) / vec3_dot(&plan->y, &plan->y);
	if (plan->size_y)
		if (scale_y > plan->size_y || scale_y < -plan->size_y)
			return (0);
	if (f_texture)
		f_texture(&data->color, scale_x, scale_y);
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
	if (plane->size_x > 0 || plane->size_y > 0 || plane->f_texture)
		if (!(inter_finite(data, plane, dist, plane->f_texture)))
			return ;
	if (!plane->f_texture)
		color_cpy(&data->color, &node->material.color_ambient);
	data->dist = dist;
	data->obj = node;
	data->find_normal = &normal_plane;
}
