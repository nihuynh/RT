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

static inline float	inter(t_ray *ray, t_plane *plane)
{
	float	dn;
	float	nom;
	t_vec3	sub;

	dn = vec3_dot(&ray->n, &plane->n);
	if (dn > -EPSILON && dn < EPSILON)
		return (HUGEVAL);
	vec3_sub(&sub, &ray->origin, &plane->origin);
	nom = -vec3_dot(&sub, &plane->n);
	if ((dn > 0 && nom < 0) || (dn < 0 && nom > 0))
		return (HUGEVAL);
	return (nom / dn);
}

void				inter_plane(t_inter *data, t_obj *node)
{
	t_plane	*plane;
	float	dist;

	plane = node->shape;
	dist = inter(&data->ray, plane);
	if (dist >= data->dist || dist < 0)
		return ;
	color_cpy(&data->color, &node->material.color_ambient);
	data->dist = dist;
	data->obj = node;
	data->find_normal = &normal_plane;
}
