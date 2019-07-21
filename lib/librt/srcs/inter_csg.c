/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_csg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 07:22:42 by nihuynh           #+#    #+#             */
/*   Updated: 2019/07/18 17:33:24 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "librt.h"
#include "csg.h"
#include "libft.h"
#include <math.h>

static inline t_inter
	inter_from_csg_obj(t_obj *obj, t_ray incoming)
{
	t_inter res;

	inter_set(&res, incoming);
	obj->f_inter(&res, obj);
	if (res.obj == NULL && (obj->type == 2 || obj->type == 0))
		res.obj = obj;
	return (res);
}

static inline t_inter
	inter_from_btree(t_btree *node, t_ray incoming)
{
	t_csg_op	*csg_op;
	t_inter		left;
	t_inter		right;

	if (node->content_size == sizeof(t_obj))
		return (inter_from_csg_obj(node->content, incoming));
	csg_op = node->content;
	left = inter_from_btree(node->left, incoming);
	right = inter_from_btree(node->right, incoming);
	return (inter_from_csg_op(csg_op->type, left, right, incoming));
}

void
	inter_csg(t_inter *top_inter, t_obj *node)
{
	t_inter		csg_inter;
	t_csg		*csg_shape;
	t_matrix	local_matrix;
	t_ray		local_ray;

	csg_shape = node->shape;
	local_matrix = mat_set_axes(csg_shape->x, csg_shape->n, csg_shape->z);
	local_ray = ray_transform(top_inter->ray, local_matrix);
	vec3_normalize(&local_ray.dir);
	csg_inter = inter_from_btree(csg_shape->root, local_ray);
	if (csg_inter.dist <= EPSILON || csg_inter.dist >= INFINITY)
		return ;
	if (csg_inter.dist >= top_inter->dist)
		return ;
	ft_memcpy(top_inter, &csg_inter, sizeof(t_inter));
}
