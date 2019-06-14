/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_cone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 20:21:46 by nihuynh           #+#    #+#             */
/*   Updated: 2019/06/14 05:46:19 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "librt.h"
#include "ftmath.h"
#include <math.h>

static inline float
	inter_finite(t_inter *inter, t_cone *cone, float dist[2])
{
	t_pt3	inter_pt;
	t_vec3	ori_2_inter;
	float	scale;
	int		i;
	float	dst_final;

	if (cone->size == 0)
		return (inter->hit_pts.x);
	i = -1;
	dst_final = HUGEVAL;
	while (++i < 2)
	{
		inter_pt.x = inter->ray.origin.x + dist[i] * inter->ray.dir.x;
		inter_pt.y = inter->ray.origin.y + dist[i] * inter->ray.dir.y;
		inter_pt.z = inter->ray.origin.z + dist[i] * inter->ray.dir.z;
		vec3_sub(&ori_2_inter, &inter_pt, &cone->origin);
		scale = vec3_dot(&ori_2_inter, &cone->n) / vec3_dot(&cone->n, &cone->n);
		if (scale < cone->size && scale >= 0)
			return (inter->hit_pts.x);
	}
	return (HUGEVAL);
}

static inline t_vec2
	inter_vec2(t_ray *ray, t_cone *cone)
{
	float	quad[3];
	t_vec2	res;
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
	inter_local(t_inter *inter, t_ray *ray, t_cone *cone)
{
	t_vec2	res_local;
	t_vec2	dist;
	float	limit[2];

	res_local = inter_vec2(ray, cone);
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
		dist.x = HUGEVAL;
		dist.y = HUGEVAL;
	}
	if (dist.x >= inter->dist || dist.x < 0)
		return (HUGEVAL);
	inter->hit_pts = dist;
	return (inter_finite(inter, cone, limit));
}

void
	inter_cone(t_inter *inter, t_obj *node)
{
	t_cone	*cone;
	float	dist;

	cone = node->shape;
	dist = inter_local(inter, &inter->ray, cone);
	if (dist >= inter->dist || dist < 0)
		return ;
	inter->dist = dist;
	inter->obj = node;
}

t_vec3
	get_cone_uv(t_inter *inter)
{
	t_cone		*cone;
	t_vec3		origin_to_hitpt;
	t_vec3		uv;
	t_vec3		x_projection;
	float		z_projection;

	cone = inter->obj->shape;
	origin_to_hitpt = vec3_sub_(inter->point, cone->origin);
	uv.y = vec3_dot(&origin_to_hitpt, &cone->n);
	if (cone->size > 0)
		uv.y = uv.y / cone->size;
	z_projection = vec3_dot(&origin_to_hitpt, &cone->z);
	z_projection /= sinf(cone->theta * DEG_TO_RAD) * vec3_mag(origin_to_hitpt);
	z_projection = ft_clampf(z_projection, -0.99999f, 0.99999f);
	uv.x = acosf(z_projection) * (1.0f / M_PI_F) * -0.5f;
	x_projection = cone->x;
	vec3_scalar(&x_projection, vec3_dot(&origin_to_hitpt, &cone->x));
	if (vec3_dot(&x_projection, &cone->x) < 0)
		uv.x = 1 - uv.x;
	return (uv);
}
