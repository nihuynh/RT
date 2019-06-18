 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 20:20:11 by nihuynh           #+#    #+#             */
/*   Updated: 2019/06/05 03:53:58 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "librt.h"
#include "ftmath.h"
#include <math.h>

static inline float
	inter_finite(t_inter *inter, t_cylinder *cyl, float dist[2])
{
	t_pt3	inter_pt;
	t_vec3	ori_2_inter;
	float	scale;
	int		i;

	if (cyl->size == 0)
		return (inter->hit_pts.x);
	i = -1;
	while (++i < 2)
	{
		inter_pt.x = inter->ray.origin.x + dist[i] * inter->ray.dir.x;
		inter_pt.y = inter->ray.origin.y + dist[i] * inter->ray.dir.y;
		inter_pt.z = inter->ray.origin.z + dist[i] * inter->ray.dir.z;
		vec3_sub(&ori_2_inter, &inter_pt, &cyl->origin);
		scale = vec3_dot(&ori_2_inter, &cyl->n) / vec3_dot(&cyl->n, &cyl->n);
		if (scale < cyl->size && scale >= 0)
			return (inter->hit_pts.x);
	}
	return (INFINITY);
}

static inline t_vec2
	inter_vec2(t_ray *ray, t_cylinder *cyl)
{
	float	quad[3];
	t_vec2	res;
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
	{
		res.x = INFINITY;
		res.y = INFINITY;
		return (res);
	}
	res.x = (-BBBB + sqrt(det)) / (2 * AAAA);
	res.y = (-BBBB - sqrt(det)) / (2 * AAAA);
	return (res);
}

static inline float
	inter_local(t_inter *inter, t_ray *ray, t_cylinder *cyl)
{
	t_vec2	res_local;
	t_vec2	dist;
	float	limit[2];

	res_local = inter_vec2(ray, cyl);
	limit[0] = res_local.x;
	limit[1] = res_local.y;
	if (res_local.x > 0 && res_local.y > 0)
	{
		dist.x = fminf(res_local.x, res_local.y);
		dist.y = fmaxf(res_local.x, res_local.y);
	}
	else if (res_local.y > 0 || res_local.x > 0)
	{
		dist.x = fmaxf(res_local.x, res_local.y);
		dist.y = fminf(res_local.x, res_local.y);
	}
	else
	{
		dist.x = INFINITY;
		dist.y = INFINITY;
	}
	if (dist.x >= inter->dist || dist.x < 0)
		return (INFINITY);
	inter->hit_pts = dist;
	return (inter_finite(inter, cyl, limit));
}


void
	inter_cylinder(t_inter *data, t_obj *node)
{
	t_cylinder	*cylinder;
	float		dist;

	cylinder = node->shape;
	dist = inter_local(data, &data->ray, cylinder);
	if (dist >= data->dist || dist < 0)
		return ;
	data->dist = dist;
	data->obj = node;
}

t_vec3
	get_cylinder_uv(t_inter *inter)
{
	t_cylinder	*cylinder;
	t_vec3		origin_to_hitpoint;
	t_vec3		uv;
	t_vec3		x_projection;
	float		z_projection;

	cylinder = inter->obj->shape;
	origin_to_hitpoint = vec3_sub_(inter->point, cylinder->origin);
	uv.y = vec3_dot(&origin_to_hitpoint, &cylinder->n);
	if (cylinder->size > 0)
		uv.y = 1 - (uv.y / cylinder->size);
	z_projection = vec3_dot(&origin_to_hitpoint, &cylinder->z);
	z_projection /= cylinder->radius;
	z_projection = ft_clampf(z_projection, -0.99999f, 0.99999f);
	uv.x = acosf(z_projection) * (1.0f / M_PI_F) * 0.5f;
	x_projection = cylinder->x;
	vec3_scalar(&x_projection, vec3_dot(&origin_to_hitpoint, &cylinder->x));
	if (vec3_dot(&x_projection, &cylinder->x) < 0)
		uv.x = 1 - uv.x;
	return (uv);
}
