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
	inter_finite(t_inter *data, t_cylinder *cyl, float dist[2])
{
	t_pt3	inter_pt;
	t_vec3	ori_2_inter;
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
		vec3_sub(&ori_2_inter, &inter_pt, &cyl->origin);
		scale = vec3_dot(&ori_2_inter, &cyl->n) / vec3_dot(&cyl->n, &cyl->n);
		if (scale < cyl->size && scale >= 0)
			dst_final = (dst_final < dist[i]) ? dst_final : dist[i];
	}
	return (dst_final);
}

static inline float
	inter(t_inter *data, t_ray *ray, t_cylinder *cyl)
{
	float	quad[3];
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
