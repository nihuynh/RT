/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   csg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 07:22:42 by nihuynh           #+#    #+#             */
/*   Updated: 2019/05/21 16:22:38 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "librt.h"
#include "rtstruct.h"
#include "libft.h"

t_inter
	not_compare(t_inter left, t_inter right)
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

t_inter
	union_compare(t_inter left, t_inter right)
{
	if (left.dist < right.dist)
		return (left);
	return (right);
}

t_inter
	inter_compare(t_inter left, t_inter right)
{
	t_inter no_inter;

	if (ft_maxf(left.dist, right.dist) < ft_minf(left.dist_max, right.dist_max))
		return (union_compare(left, right));
	inter_set(&no_inter, left.ray);
	return (no_inter);
}

t_inter
	inter_from_csg_op(t_csg_op *csg_op)
{
	t_inter no_inter;

	inter_set(&no_inter, *csg_op->incoming);
	if (csg_op->type == INTER)
		return (inter_compare(csg_op->left, csg_op->right));
	if (csg_op->type == NOT)
		return (not_compare(csg_op->left, csg_op->right));
	if (csg_op->type == UNION)
		return (union_compare(csg_op->left, csg_op->right));
	ft_error(__func__, __LINE__);
	return (no_inter);
}

t_inter
	inter_from_csg_obj(t_obj *obj, t_ray *incoming)
{
	t_inter res;

	inter_set(&res, *incoming);
	obj->f_inter(&res, obj);
	return (res);
}

t_inter
	inter_from_btree(t_btree *node, t_ray *incoming)
{
	t_csg_op *csg_op;

	if (node->content_size == sizeof(t_obj))
		return (inter_from_csg_obj(node->content, incoming));
	csg_op = node->content;
	csg_op->incoming = incoming;
	csg_op->left = inter_from_btree(node->left, incoming);
	csg_op->right = inter_from_btree(node->right, incoming);
	return (inter_from_csg_op(csg_op));
}

static inline t_inter
	inter(t_ray *incoming, t_csg *csg)
{
	t_inter	res;

	res = inter_from_btree(csg->root, incoming);
	return (res);
}

void
	inter_csg(t_inter *top_inter, t_obj *node)
{
	t_inter	csg_inter;
	t_csg	*csg_shape;

	csg_shape = node->shape;
	csg_inter = inter(&top_inter->ray, csg_shape);
	if (csg_inter.dist >= top_inter->dist || csg_inter.dist < 0)
		return ;
	top_inter->dist = csg_inter.dist;
	top_inter->obj = csg_inter.obj;
}

/*
** Useless for csg because it's not the primitives :
*/

void
	normal_csg(t_inter *inter)
{
	// Do stuff
	(void)inter;
}

t_vec3
	get_csg_uv(t_inter *inter)
{
	t_vec3 tmp;

	tmp = inter->obj->get_uv(inter);
	return (tmp);
}
