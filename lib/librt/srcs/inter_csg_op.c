/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_csg_op.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 00:38:47 by nihuynh           #+#    #+#             */
/*   Updated: 2019/06/05 00:39:03 by nihuynh          ###   ########.fr       */
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
	not_compare(t_inter left, t_inter right)
{
	t_inter no_inter;

	inter_set(&no_inter, right.ray);
	if (left.dist == HUGEVAL || right.dist == HUGEVAL)
		return (left);
	if (left.dist < right.hit_pts.x && left.dist < right.hit_pts.y)
		return (left);
	if (left.dist > right.hit_pts.y && left.dist > right.hit_pts.x)
		return (left);
	if (ft_btwf(left.hit_pts.x, right.hit_pts.y, right.hit_pts.x)
		&& ft_btwf(left.hit_pts.y, right.hit_pts.y, right.hit_pts.x))
		return (no_inter);
	right.dist = right.hit_pts.y;
	return (right);
}

static inline t_inter
	union_compare(t_inter left, t_inter right)
{
	if (left.dist <= right.dist)
		return (left);
	return (right);
}

static inline t_inter
	inter_compare(t_inter left, t_inter right)
{
	t_inter no_inter;

	inter_set(&no_inter, left.ray);
	if (left.dist == HUGEVAL || right.dist == HUGEVAL)
		return (no_inter);
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
		return (inter_compare(left, right));
	if (type == NOT)
		return (not_compare(left, right));
	if (type == UNION)
		return (union_compare(left, right));
	ft_error(__func__, __LINE__);
	inter_set(&no_inter, incoming);
	return (no_inter);
}
