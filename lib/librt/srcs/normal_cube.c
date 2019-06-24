/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_cube.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 14:09:43 by nihuynh           #+#    #+#             */
/*   Updated: 2019/06/24 21:09:58 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "librt.h"
#include "ftmath.h"
#include <math.h>
#include "ftio.h"

void	normal_cube(t_inter *inter)
{
	t_cube	*cube;
	t_vec3	insider;
	t_vec3	sub;
	bool	is_inside;

	cube = inter->obj->shape;
	sub = vec3_sub_(inter->point, cube->origin);
	insider = vec3_sub_(inter->ray.origin, cube->origin);
	is_inside = (vec3_mag(insider) < vec3_mag(sub));
	vec3_scalar(&sub, 1.0f / cube->size + EPSILON);
	inter->n.x = (int)sub.x;
	inter->n.y = (int)sub.y;
	inter->n.z = (int)sub.z;
	if (is_inside || inter->hit_pts.y == inter->dist)
		vec3_scalar(&inter->n, -1);
	vec3_normalize(&inter->n);
}
