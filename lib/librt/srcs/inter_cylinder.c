/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 20:20:11 by nihuynh           #+#    #+#             */
/*   Updated: 2019/04/25 18:41:12 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "librt.h"
#include <math.h>

static inline float
	inter_finite(t_inter *data, t_cylinder *cyl, float dist[2])
{
	t_pt3	inter_pt;
	t_vec3	origin_to_inter;
	float	scale;
	int		i;
	float	dst_final;

	if (cyl->size == 0)
		return ((dist[0] < dist[1]) ? dist[0] : dist[1]);
	i = -1;
	dst_final = HUGEVAL;
	while (++i < 2)
	{
		inter_pt.x = data->ray.origin.x + dist[i] * data->ray.dir.x;
		inter_pt.y = data->ray.origin.y + dist[i] * data->ray.dir.y;
		inter_pt.z = data->ray.origin.z + dist[i] * data->ray.dir.z;
		vec3_sub(&origin_to_inter, &inter_pt, &cyl->origin);
		scale = vec3_dot(&origin_to_inter, &cyl->n) / vec3_dot(&cyl->n, &cyl->n);
		if (scale < cyl->size && scale >= 0)
			dst_final = (dst_final < dist[i]) ? dst_final : dist[i];
	}
	return (dst_final);
}

static inline float
	inter(t_inter *data, t_ray *ray, t_cylinder *cyl)
{
	float	toby[3];
	float	res[2];
	float	det;
	t_vec3	rene;

	vec3_sub(&rene, &ray->origin, &cyl->origin);
	AAAA = vec3_dot(&ray->dir, &cyl->n);
	CCCC = vec3_dot(&rene, &cyl->n);
	BBBB = 2 * (vec3_dot(&ray->dir, &rene) - AAAA * CCCC);
	det = vec3_mag(ray->dir);
	AAAA = det * det - AAAA * AAAA;
	det = vec3_mag(rene);
	CCCC = det * det - CCCC * CCCC - cyl->radius * cyl->radius;
	det = BBBB * BBBB - 4 * AAAA * CCCC;
	if (det < 0)
		return (HUGEVAL);
	res[0] = (-BBBB + sqrt(det)) / (2 * AAAA);
	res[0] = (res[0] > 0) ? res[0] : HUGEVAL;
	res[1] = (-BBBB - sqrt(det)) / (2 * AAAA);
	res[1] = (res[1] > 0) ? res[1] : HUGEVAL;
	return (inter_finite(data, cyl, res));
}

void
	inter_cylinder(t_inter *data, t_obj *node)
{
	t_cylinder	*cylinder;
	float		dist;

	cylinder = node->shape;
	dist = inter(data, &data->ray, cylinder);
	if (dist >= data->dist || dist < 0)
		return ;
	data->dist = dist;
	data->obj = node;
}

t_vec3
	get_cylinder_uv(t_inter *inter)
{
	t_cylinder	*cylinder;
	t_vec3		hitpoint_to_origin;
	t_vec3		uv;
	float		height;

	cylinder = inter->obj->shape;
	vec3_cartesian_to_spherical(inter->n, &uv.x, &uv.y);
	hitpoint_to_origin = vec3_sub_(cylinder->origin, inter->point);
	height = vec3_dot(&hitpoint_to_origin, &cylinder->n);
	vec3_scalar(&uv, 50);
	uv.y = height;
	return (uv);
}
