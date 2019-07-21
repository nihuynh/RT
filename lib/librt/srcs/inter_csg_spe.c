/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_csg_spe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 19:52:48 by sklepper          #+#    #+#             */
/*   Updated: 2019/07/21 17:06:48 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "librt.h"
#include "csg.h"
#include "libft.h"
#include <math.h>

void
	inter_find_spe(t_inter *primary, t_pt3 *value)
{
	float dist;

	dist = primary->hit_pts.x;
	value->x = primary->ray.origin.x + dist * primary->ray.dir.x;
	value->y = primary->ray.origin.y + dist * primary->ray.dir.y;
	value->z = primary->ray.origin.z + dist * primary->ray.dir.z;
}

bool
	is_inside_cone(t_inter *inter)
{
	t_cone	*cone;
	t_pt3	pc;
	float	var[2];
	t_vec3	orig2point;
	t_vec3	vec;

	cone = inter->obj->shape;
	inter_find_spe(inter, &inter->point);
	vec3_sub(&vec, &inter->point, &inter->ray.origin);
	vec3_normalize(&vec);
	orig2point = vec3_sub_(inter->point, cone->origin);
	var[0] = ((vec3_dot(&orig2point, &cone->n) < 0) * 180) - cone->theta;
	var[1] = vec3_mag(orig2point) / cosf(var[0] * DEG_TO_RAD);
	pc.x = cone->origin.x + var[1] * cone->n.x;
	pc.y = cone->origin.y + var[1] * cone->n.y;
	pc.z = cone->origin.z + var[1] * cone->n.z;
	vec3_sub(&inter->n, &inter->point, &pc);
	vec3_normalize(&inter->n);
	return (vec3_dot(&inter->n, &vec) > 0);
}

static inline float
	need_lines_for_norm(t_plane *plane, t_inter sub)
{
	t_vec3	postoplane;

	vec3_sub(&postoplane, &sub.ray.origin, &plane->origin);
	vec3_normalize(&postoplane);
	return (vec3_dot(&postoplane, &plane->n));
}

static inline t_inter
	need_more_lines_for_norm(t_inter core, t_inter sub)
{
	t_inter	no_inter;

	inter_set(&no_inter, sub.ray);
	if (core.obj && core.obj->type == 2 && is_inside_cone(&core))
	{
		if (sub.dist < core.dist ||
			(sub.dist > core.dist && sub.dist > core.hit_pts.y))
			return (sub);
		if (core.hit_pts.y > 0 && core.hit_pts.y != INFINITY)
		{
			core.dist = core.hit_pts.y;
			core.hit_pts.x = core.hit_pts.y;
			core.hit_pts.y = INFINITY;
			return (core);
		}
		else
			return (no_inter);
	}
	if (ft_btwf(sub.dist, core.hit_pts.x, core.hit_pts.y))
		return (sub);
	if (core.dist < sub.dist)
		return (no_inter);
	else
		return (core);
}

t_inter
	not_plane(t_inter core, t_inter sub)
{
	t_plane	*plane;
	t_inter	no_inter;
	float	var;

	inter_set(&no_inter, sub.ray);
	plane = sub.obj->shape;
	var = need_lines_for_norm(plane, sub);
	if (vec3_dot(&plane->n, &sub.ray.dir) > 0)
	{
		if (core.obj && core.obj->type == 2 && is_inside_cone(&core)
			&& sub.dist < core.dist)
			return (sub);
		if (var > 0)
			return (no_inter);
		if (core.dist < sub.dist || sub.dist < 0)
			return (core);
		if (ft_btwf(sub.dist, core.hit_pts.x, core.hit_pts.y))
			return (sub);
	}
	else if (var > 0)
		return (need_more_lines_for_norm(core, sub));
	if (sub.dist == INFINITY && var < 0)
		return (core);
	return (no_inter);
}
