/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_cone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 20:21:46 by nihuynh           #+#    #+#             */
/*   Updated: 2019/06/05 03:53:40 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "librt.h"
#include "ftmath.h"
#include <math.h>

static inline float
	inter_finite(t_inter *data, t_cone *cone, float dist[2])
{
	t_pt3	inter_pt;
	t_vec3	ori_2_inter;
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
		vec3_sub(&ori_2_inter, &inter_pt, &cone->origin);
		scale = vec3_dot(&ori_2_inter, &cone->n) / vec3_dot(&cone->n, &cone->n);
		if (scale < cone->size && scale >= 0)
			dst_final = (dst_final < dist[i]) ? dst_final : dist[i];
	}
	return (dst_final);
}

static inline float
	inter(t_inter *data, t_ray *ray, t_cone *cone)
{
	float	quad[3];
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
