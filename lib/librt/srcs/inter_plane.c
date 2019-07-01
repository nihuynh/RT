/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 20:19:47 by nihuynh           #+#    #+#             */
/*   Updated: 2019/07/01 22:00:33 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "librt.h"
#include <math.h>

static inline float
	inter_dist(t_ray *ray, t_plane *plane)
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

static inline float
	inter_local(t_inter *inter, t_ray *ray, t_plane *plane)
{
	t_vec2	dist;
	float	angle;

	angle = vec3_dot(&ray->dir, &plane->n);
	dist.x = inter_dist(ray, plane);
	dist.y = (angle > 0 || dist.x == INFINITY) ? INFINITY : -INFINITY;
	if (dist.x >= inter->dist || dist.x < 0)
		return (INFINITY);
	if ((plane->size.x > 0 || plane->size.y > 0 || plane->type == 2)
		&& !(inter_plane_finite(inter, plane, dist.x)))
		return (INFINITY);
	inter->hit_pts = dist;
	return (dist.x);
}

void
	inter_plane(t_inter *inter, t_obj *node)
{
	t_plane	*plane;
	float	dist;

	plane = node->shape;
	dist = inter_local(inter, &inter->ray, plane);
	if (dist >= inter->dist || dist < 0)
		return ;
	inter->dist = dist;
	inter->obj = node;
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
