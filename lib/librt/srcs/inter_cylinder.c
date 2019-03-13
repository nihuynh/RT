/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 20:20:11 by nihuynh           #+#    #+#             */
/*   Updated: 2019/03/07 16:54:57 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "librt.h"
#include <math.h>

static inline float		inter(t_ray *ray, t_cylinder *cyl)
{
	float	toby[3];
	float	res[2];
	float	det;
	t_vec3	rene;

	vec3_sub(&rene, (t_vec3*)&ray->origin, (t_vec3*)&cyl->origin);
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

void					inter_cylinder(t_inter *data, t_obj *node)
{
	t_cylinder	*cylinder;
	float		dist;

	cylinder = node->shape;
	dist = inter(&data->ray, cylinder);
	if (dist >= data->dist || dist < 0)
		return ;
	color_cpy(&data->color, &node->material.color_ambient);
	data->dist = dist;
	data->obj = node;
	data->find_normal = &normal_cylinder;
}
