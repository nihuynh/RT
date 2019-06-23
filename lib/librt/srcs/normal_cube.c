/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_cube.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 14:09:43 by nihuynh           #+#    #+#             */
/*   Updated: 2019/06/23 14:10:39 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "librt.h"

void	normal_cube(t_inter *inter)
{
	t_cube	*cube;
	t_vec3	insider;
	int		is_inside;

	cube = inter->obj->shape;
	vec3_sub(&insider, &cube->origin, &inter->ray.origin);
	is_inside = (vec3_mag(insider) < cube->size) ? 1 : 0;
	inter->n.x = inter->point.x - cube->origin.x;
	inter->n.y = inter->point.y - cube->origin.y;
	inter->n.z = inter->point.z - cube->origin.z;
	if (is_inside || inter->hit_pts.y == inter->dist)
		vec3_scalar(&inter->n, -1);
	vec3_normalize(&inter->n);
}
