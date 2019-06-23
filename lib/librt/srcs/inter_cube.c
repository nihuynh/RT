/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_cube.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 13:52:10 by nihuynh           #+#    #+#             */
/*   Updated: 2019/06/23 13:52:11 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "librt.h"
#include <math.h>

static inline t_vec2
	inter_vec2(t_ray *ray, t_cube *cube)
{
	float	quad[3];
	t_vec2	res;
	float	det;
	t_vec3	rene;

	vec3_sub(&rene, &ray->origin, &cube->origin);
	AAAA = vec3_mag(ray->dir);
	BBBB = 2.0 * vec3_dot(&ray->dir, &rene);
	CCCC = vec3_dot(&rene, &rene) - cube->size * cube->size;
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
	inter_local(t_inter *inter, t_ray *ray, t_cube *cube)
{
	t_vec2	res_local;
	t_vec2	dist;

	res_local = inter_vec2(ray, cube);
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
	return (dist.x);
}

void
	inter_cube(t_inter *inter, t_obj *node)
{
	t_cube	*cube;
	float		dist;

	cube = node->shape;
	dist = inter_local(inter, &inter->ray, cube);
	if (dist >= inter->dist || dist < 0)
		return ;
	inter->dist = dist;
	inter->obj = node;
}

t_vec3
	get_cube_uv(t_inter *inter)
{
	t_vec3			uv;

	vec3_cartesian_to_spherical(inter->n, &uv.x, &uv.y);
	uv.x = remap_to_0_to_1(uv.x * M_INV_PI_F);
	uv.y *= M_INV_PI_F;
	return (uv);
}
