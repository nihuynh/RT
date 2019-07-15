/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_csg_op.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 00:38:47 by nihuynh           #+#    #+#             */
/*   Updated: 2019/07/15 18:35:12 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "librt.h"
#include "csg.h"
#include "libft.h"
#include <math.h>

static inline t_inter
	not_op(t_inter core, t_inter sub)
{
	t_inter no_inter;

	inter_set(&no_inter, sub.ray);
	if (core.dist == INFINITY || sub.dist == INFINITY)
		return (core);
	if (core.dist < sub.hit_pts.x && core.dist < sub.hit_pts.y)
		return (core);
	if (sub.dist < core.dist)
	{
		if (core.hit_pts.y < 0 && core.hit_pts.x > 0)
			return (sub);
		if (ft_btwf(sub.hit_pts.y, core.hit_pts.x, core.hit_pts.y))
		{
			sub.dist = sub.hit_pts.y;
			return (sub);
		}
	}
	if (core.dist > sub.hit_pts.y && core.dist > sub.hit_pts.x)
		return (core);
	if (sub.obj->type == 1 && core.dist < sub.dist && sub.hit_pts.y < 0
		&& ft_btw(sub.hit_pts.x, core.hit_pts.x, core.hit_pts.y))
		return (sub);
	return (no_inter);
}

static inline t_inter
	union_op(t_inter left, t_inter right)
{
	if (left.dist <= right.dist)
		return (left);
	return (right);
}

static inline t_inter
	inter_op(t_inter left, t_inter right)
{
	t_inter no_inter;

	inter_set(&no_inter, left.ray);
	if (left.dist == INFINITY || right.dist == INFINITY)
		return (no_inter);
	if (right.hit_pts.y > 0 && ft_btwf(right.dist, left.dist, left.hit_pts.y))
		return (right);
	if (ft_btwf(left.dist, right.hit_pts.x, right.hit_pts.y))
		return (left);
	if (ft_btwf(right.dist, left.hit_pts.x, left.hit_pts.y))
		return (right);
	return (no_inter);
}

int
	is_inside_cone(t_inter *inter)
{
	t_cone	*cone;
	t_pt3	pc;
	float	var;
	t_vec3	orig2point;
	float	angle;

	cone = inter->obj->shape;
	inter_find(inter, &inter->point);
	orig2point = vec3_sub_(inter->point, cone->origin);
	angle = ((vec3_dot(&orig2point, &cone->n) < 0) * 180) - cone->theta;
	var = vec3_mag(orig2point) / cosf(angle * DEG_TO_RAD);
	pc.x = cone->origin.x + var * cone->n.x;
	pc.y = cone->origin.y + var * cone->n.y;
	pc.z = cone->origin.z + var * cone->n.z;
	vec3_sub(&inter->n, &inter->point, &pc);
	vec3_normalize(&inter->n);
	return (vec3_dot(&inter->n, &inter->ray.dir) > 0);
}

t_inter
	inter_from_csg_op(int type, t_inter left, t_inter right, t_ray incoming)
{
	t_inter no_inter;

	if (right.obj != NULL && right.obj->type == 2
		&& is_inside_cone(&right))
	{
		if (type == INTER)
			return (not_op(left, right));
		if (type == NOT)
			return (inter_op(left, right));
	}
	if (left.obj != NULL && left.obj->type == 2
		&& is_inside_cone(&left) && type == INTER)
		return (not_op(right, left));
	if (type == INTER)
		return (inter_op(left, right));
	if (type == NOT)
		return (not_op(left, right));
	if (type == UNION)
		return (union_op(left, right));
	ft_error(__func__, __LINE__);
	inter_set(&no_inter, incoming);
	return (no_inter);
}
