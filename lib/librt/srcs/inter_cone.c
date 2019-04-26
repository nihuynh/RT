/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_cone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 20:21:46 by nihuynh           #+#    #+#             */
/*   Updated: 2019/04/25 18:18:31 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "librt.h"
#include <math.h>

static inline float
	inter_finite(t_inter *data, t_cone *cone, float dist[2])
{
	t_pt3	inter_pt;
	t_vec3	origin_to_inter;
	float	scale;
	int		i;
	float	dst_final;

	if (cone->size == 0)
		return ((dist[0] < dist[1]) ? dist[0] : dist[1]);
	i = -1;
	dst_final = HUGEVAL;
	while (++i < 2)
	{
		inter_pt.x = data->ray.origin.x + dist[i] * data->ray.dir.x;
		inter_pt.y = data->ray.origin.y + dist[i] * data->ray.dir.y;
		inter_pt.z = data->ray.origin.z + dist[i] * data->ray.dir.z;
		vec3_sub(&origin_to_inter, &inter_pt, &cone->origin);
		scale = vec3_dot(&origin_to_inter, &cone->n) / vec3_dot(&cone->n, &cone->n);
		if (scale < cone->size && scale >= 0)
			dst_final = (dst_final < dist[i]) ? dst_final : dist[i];
	}
	return (dst_final);
}

/*
**http://lousodrome.net/blog/light/2017/01/03/intersection-of-a-ray-and-a-cone/
**	cos_theta2 = cos(DEG_TO_RAD(cone->theta));
**	cos_theta2 *= cos_theta2;
**	AAAA = vec3_dot(&ray->n, &cone->n);
**	CCCC = vec3_dot(&rene, &cone->n);
**	BBBB = 2.0 * (vec3_dot(&ray->n, &rene) - (1 + tan_theta2) * AAAA * CCCC);
**	AAAA = vec3_mag(ray->n) - (1 + tan_theta2) * AAAA * AAAA;
**	CCCC = vec3_mag(rene) * vec3_mag(rene) - (1 + tan_theta2) * CCCC * CCCC;
*/

static inline float
	inter(t_inter *data, t_ray *ray, t_cone *cone)
{
	float	toby[3];
	float	res[2];
	double	cos_theta2;
	float	det;
	t_vec3	rene;

	cos_theta2 = cosf(cone->theta * DEG_TO_RAD);
	cos_theta2 *= cos_theta2;
	vec3_sub(&rene, &ray->origin, &cone->origin);
	AAAA = vec3_dot(&ray->dir, &cone->n);
	CCCC = vec3_dot(&rene, &cone->n);
	BBBB = 2 * (AAAA * CCCC - vec3_dot(&ray->dir, &rene) * cos_theta2);
	AAAA = AAAA * AAAA - cos_theta2;
	CCCC = CCCC * CCCC - vec3_dot(&rene, &rene) * cos_theta2;
	det = BBBB * BBBB - 4 * AAAA * CCCC;
	if (det < 0)
		return (HUGEVAL);
	res[0] = (-BBBB + sqrt(det)) / (2 * AAAA);
	res[0] = (res[0] > 0) ? res[0] : HUGEVAL;
	res[1] = (-BBBB - sqrt(det)) / (2 * AAAA);
	res[1] = (res[1] > 0) ? res[1] : HUGEVAL;
	return (inter_finite(data, cone, res));
}


void
	inter_cone(t_inter *data, t_obj *node)
{
	t_cone	*cone;
	float	dist;

	cone = node->shape;
	dist = inter(data, &data->ray, cone);
	if (dist >= data->dist || dist < 0)
		return ;
	data->dist = dist;
	data->obj = node;
}
