/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 20:19:06 by nihuynh           #+#    #+#             */
/*   Updated: 2019/06/14 05:35:41 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "librt.h"
#include <math.h>

static inline t_vec2
	inter_vec2(t_ray *ray, t_sphere *sphere)
{
	float	quad[3];
	t_vec2	res;
	float	det;
	t_vec3	rene;

	vec3_sub(&rene, &ray->origin, &sphere->origin);
	AAAA = vec3_mag(ray->dir);
	BBBB = 2.0 * vec3_dot(&ray->dir, &rene);
	CCCC = vec3_dot(&rene, &rene) - sphere->radius * sphere->radius;
	det = BBBB * BBBB - 4 * AAAA * CCCC;
	if (det < 0)
	{
		res.x = HUGEVAL;
		res.y = HUGEVAL;
		return (res);
	}
	res.x = (-BBBB + sqrt(det)) / (2 * AAAA);
	res.y = (-BBBB - sqrt(det)) / (2 * AAAA);
	return (res);
}

static inline float
	inter_local(t_inter *inter, t_ray *ray, t_sphere *sphere)
{
	t_vec2	res_local;
	t_vec2	dist;

	res_local = inter_vec2(ray, sphere);
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
		dist.x = HUGEVAL;
		dist.y = HUGEVAL;
	}
	if (dist.x >= inter->dist || dist.x < 0)
		return (HUGEVAL);
	inter->hit_pts = dist;
	return (dist.x);
}

void
	inter_sphere(t_inter *inter, t_obj *node)
{
	t_sphere	*sphere;
	float		dist;

	sphere = node->shape;
	dist = inter_local(inter, &inter->ray, sphere);
	if (dist >= inter->dist || dist < 0)
		return ;
	inter->dist = dist;
	inter->obj = node;
}

t_vec3
	get_sphere_uv(t_inter *inter)
{
	t_vec3			uv;

	vec3_cartesian_to_spherical(inter->n, &uv.x, &uv.y);
	uv.x = remap_to_0_to_1(uv.x * M_INV_PI_F);
	uv.y *= M_INV_PI_F;
	return (uv);
}
