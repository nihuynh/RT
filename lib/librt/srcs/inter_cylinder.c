/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 20:20:11 by nihuynh           #+#    #+#             */
/*   Updated: 2019/04/08 20:08:38 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "librt.h"
#include <math.h>

static inline float
	inter(t_ray *ray, t_cylinder *cyl)
{
	float	toby[3];
	float	res[2];
	float	det;
	t_vec3	rene;

	vec3_sub(&rene, &ray->origin, &cyl->origin);
	AAAA = vec3_dot(&ray->n, &cyl->n);
	CCCC = vec3_dot(&rene, &cyl->n);
	BBBB = 2 * (vec3_dot(&ray->n, &rene) - AAAA * CCCC);
	det = vec3_mag(&ray->n);
	AAAA = det * det - AAAA * AAAA;
	det = vec3_mag(&rene);
	CCCC = det * det - CCCC * CCCC - cyl->radius * cyl->radius;
	det = BBBB * BBBB - 4 * AAAA * CCCC;
	if (det < 0)
		return (HUGEVAL);
	res[0] = (-BBBB + sqrt(det)) / (2 * AAAA);
	res[0] = (res[0] > 0) ? res[0] : HUGEVAL;
	res[1] = (-BBBB - sqrt(det)) / (2 * AAAA);
	res[1] = (res[1] > 0) ? res[1] : HUGEVAL;
	return ((res[0] < res[1]) ? res[0] : res[1]);
}

static inline int
	inter_finite(t_inter *data, t_cylinder *cylinder, float dist)
{
	t_pt3	inter_pt;
	t_vec3	origin_to_inter;
	float	scale;

	inter_pt.x = data->ray.origin.x + dist * data->ray.n.x;
	inter_pt.y = data->ray.origin.y + dist * data->ray.n.y;
	inter_pt.z = data->ray.origin.z + dist * data->ray.n.z;
	vec3_sub(&origin_to_inter, &inter_pt, &cylinder->origin);
	scale = vec3_dot(&origin_to_inter, &cylinder->n)
			/ vec3_dot(&cylinder->n, &cylinder->n);
	if (scale > cylinder->size || scale <= 0)
		return (0);
	return (1);
}

void
	inter_cylinder(t_inter *data, t_obj *node)
{
	t_cylinder	*cylinder;
	float		dist;

	cylinder = node->shape;
	dist = inter(&data->ray, cylinder);
	if (dist >= data->dist || dist < 0)
		return ;
	if (cylinder->size > 0)
		if (!(inter_finite(data, cylinder, dist)))
			return ;
	color_cpy(&data->color, &node->material.color_ambient);
	data->dist = dist;
	data->obj = node;
	data->find_normal = &normal_cylinder;
}
