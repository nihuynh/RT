/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_cone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 20:21:46 by nihuynh           #+#    #+#             */
/*   Updated: 2019/04/08 18:31:11 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "librt.h"
#include <math.h>

/*
**http://lousodrome.net/blog/light/2017/01/03/intersection-of-a-ray-and-a-cone/
**	cos_theta2 = cos(DEG_TO_RAD(cone->theta));
**	cos_theta2 *= cos_theta2;
**	AAAA = vec3_dot(&ray->n, &cone->n);
**	CCCC = vec3_dot(&rene, &cone->n);
**	BBBB = 2.0 * (vec3_dot(&ray->n, &rene) - (1 + tan_theta2) * AAAA * CCCC);
**	AAAA = vec3_mag(&ray->n) - (1 + tan_theta2) * AAAA * AAAA;
**	CCCC = vec3_mag(&rene) * vec3_mag(&rene) - (1 + tan_theta2) * CCCC * CCCC;
*/

static inline float
	inter(t_ray *ray, t_cone *cone)
{
	float	toby[3];
	float	res[2];
	double	cos_theta2;
	float	det;
	t_vec3	rene;

	cos_theta2 = cos(DEG_TO_RAD(cone->theta));
	cos_theta2 *= cos_theta2;
	vec3_sub(&rene, &ray->origin, &cone->origin);
	AAAA = vec3_dot(&ray->n, &cone->n);
	CCCC = vec3_dot(&rene, &cone->n);
	BBBB = 2 * (AAAA * CCCC - vec3_dot(&ray->n, &rene) * cos_theta2);
	AAAA = AAAA * AAAA - cos_theta2;
	CCCC = CCCC * CCCC - vec3_dot(&rene, &rene) * cos_theta2;
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
	inter_finite(t_inter *data, t_cone *cone, float dist)
{
	t_pt3	inter_pt;
	t_vec3	origin_to_inter;
	float	scale;

	inter_pt.x = data->ray.origin.x + dist * data->ray.n.x;
	inter_pt.y = data->ray.origin.y + dist * data->ray.n.y;
	inter_pt.z = data->ray.origin.z + dist * data->ray.n.z;
	vec3_sub(&origin_to_inter, &inter_pt, &cone->origin);
	scale  = vec3_dot(&origin_to_inter, &cone->n) / vec3_dot(&cone->n, &cone->n);
	if (scale  > cone->size || scale <= 0)
		return (0);
	return (1);
}

void
	inter_cone(t_inter *data, t_obj *node)
{
	t_cone	*cone;
	float	dist;

	cone = node->shape;
	dist = inter(&data->ray, cone);
	if (dist >= data->dist || dist < 0)
		return ;
	if (cone->size > 0)
		if (!(inter_finite(data, cone, dist)))
			return ;
	color_cpy(&data->color, &node->material.color_ambient);
	data->dist = dist;
	data->obj = node;
	data->find_normal = &normal_cone;
}
