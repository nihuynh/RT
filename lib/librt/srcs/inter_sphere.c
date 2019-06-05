/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 20:19:06 by nihuynh           #+#    #+#             */
/*   Updated: 2019/06/05 03:47:27 by nihuynh          ###   ########.fr       */
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
	t_vec2	res;

	res = inter_vec2(ray, sphere);
	if (res.x > 0 && res.y > 0)
	{
		inter->hit_pts.x = fminf(res.x, res.y);
		inter->hit_pts.y = fmaxf(res.x, res.y);
	}
	else if (res.y > 0 || res.x > 0)
	{
		inter->hit_pts.x = fmaxf(res.x, res.y);
		inter->hit_pts.y = fminf(res.x, res.y);
	}
	else
	{
		inter->hit_pts.x = HUGEVAL;
		inter->hit_pts.y = HUGEVAL;
	}
	return (inter->hit_pts.x);
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
