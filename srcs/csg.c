/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   csg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 07:22:42 by nihuynh           #+#    #+#             */
/*   Updated: 2019/05/21 05:25:15 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "librt.h"

#include "ftbtree.h"
#include "ftmath.h"
#include "rtstruct.h"

t_inter			not_compare(t_inter left, t_inter right)
{
	t_inter no_inter;

	if (left.dist <= right.dist)
		return (left);
	if (left.dist_max <= right.dist_max)
	{
		inter_set(&no_inter, left.ray);
		return (no_inter);
	}
	else if (left.dist <= right.dist_max)
	{
		right.dist = right.dist_max;
		return (right);

	}
	return (left);

}

t_inter			union_compare(t_inter left, t_inter right)
{
	if (left.dist <= right.dist)
		return (left);
	return (right);
}

t_inter			inter_compare(t_inter left, t_inter right)
{
	t_inter no_inter;

	if (ft_maxf(left.dist, right.dist) < ft_minf(left.dist_max, right.dist_max))
		return (union_compare(left, right));
	inter_set(&no_inter, left.ray);
	return (no_inter);
}


void			inter_csg(t_inter *data, t_obj *node)
{
	// go into the tree

	(void)data;
	(void)node;
}

/*
** Useless for csg because it's not the primitives :
*/

void			normal_csg(t_inter *inter)
{
	// Do stuff
	(void)inter;
}

t_vec3			get_csg_uv(t_inter *inter)
{
	t_vec3 tmp;

	tmp = inter->obj->get_uv(inter);
	return (tmp);
}
