/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 20:19:47 by nihuynh           #+#    #+#             */
/*   Updated: 2019/06/18 23:48:37 by nihuynh          ###   ########.fr       */
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
		return (INFINITY);
	vec3_sub(&sub, &ray->origin, &plane->origin);
	nom = -vec3_dot(&sub, &plane->n);
	if ((dn > 0 && nom < 0) || (dn < 0 && nom > 0))
		return (INFINITY);
	return (nom / dn);
}

static inline int
	inter_finite(t_inter *data, t_plane *plan, float dist)
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
	if (plan->size.x && fabsf(scale_x) > plan->size.x)
		return (0);
	scale_y = vec3_dot(&orig_to_inter, &plan->y) / vec3_dot(&plan->y, &plan->y);
	if (plan->size.y && fabsf(scale_y) > plan->size.y)
		return (0);
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
	if (plane->size.x > 0 || plane->size.y > 0)
		if (!(inter_finite(data, plane, dist)))
			return ;
	data->dist = dist;
	data->obj = node;
}

t_vec3
	get_plane_uv(t_inter *inter)
{
	t_plane			*plan;
	t_vec3			orig_to_inter;
	t_vec3			uv;

	plan = (t_plane *)inter->obj->shape;
	orig_to_inter = vec3_sub_(inter->point, plan->origin);
	uv.x = vec3_dot(&orig_to_inter, &plan->x);
	uv.y = vec3_dot(&orig_to_inter, &plan->y);
	if (plan->size.x > 0)
		uv.x = remap_to_0_to_1(uv.x / plan->size.x);
	if (plan->size.y > 0)
		uv.y = remap_to_0_to_1(uv.y / plan->size.y);
	return (uv);
}
