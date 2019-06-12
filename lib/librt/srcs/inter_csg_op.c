/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_csg_op.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 00:38:47 by nihuynh           #+#    #+#             */
/*   Updated: 2019/06/12 00:52:35 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "librt.h"
#include "rtstruct.h"
#include "libft.h"
#include <math.h>

static inline float
	ft_btwf(float value, float limit1, float limit2)
{
	return (value >= fminf(limit1, limit2) && value <= fmaxf(limit1, limit2));
}

static inline t_inter
	not_op(t_inter core, t_inter sub)
{
	t_inter no_inter;

	inter_set(&no_inter, sub.ray);
	if (core.dist == HUGEVAL || sub.dist == HUGEVAL)
		return (core);
	if ((core.dist < sub.hit_pts.x && core.dist < sub.hit_pts.y)
		|| (core.dist > sub.hit_pts.y && core.dist > sub.hit_pts.x))
		return (core);
	if (sub.dist < core.dist)
	{
		if (ft_btwf(sub.hit_pts.y, core.hit_pts.x, core.hit_pts.y))
		{
			sub.dist = sub.hit_pts.y;
			return (sub);
		}
		if (core.hit_pts.y < 0 && core.hit_pts.x > 0)
			return (sub);
	}
	if (core.dist < sub.dist && sub.hit_pts.y < 0
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
	if (left.dist == HUGEVAL || right.dist == HUGEVAL)
		return (no_inter);
	if (right.hit_pts.y > 0 && ft_btwf(right.dist, left.hit_pts.x, left.hit_pts.y))
		return (right);
	if (ft_btwf(left.dist, right.hit_pts.x, right.hit_pts.y))
		return (left);
	if (ft_btwf(right.dist, left.hit_pts.x, left.hit_pts.y))
		return (right);
	return (no_inter);
}

t_inter
	inter_from_csg_op(int type, t_inter left, t_inter right, t_ray incoming)
{
	t_inter no_inter;

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
