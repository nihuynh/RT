/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 22:26:16 by sklepper          #+#    #+#             */
/*   Updated: 2019/04/24 18:05:24 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>
#include "librt.h"
#include "libft.h"

void
	cam_ray(t_data *data, t_ray *res, float x, float y)
{
	float	fovt;
	float	r;
	t_pt3	direction;

	r = data->sdl.img.width / (float)data->sdl.img.height;
	fovt = tanf((data->scene_set.fov * DEG_TO_RAD) / 2);
	direction.x = (2 * x / data->sdl.img.width - 1) * fovt * r;
	direction.y = (1 - 2 * y / data->sdl.img.height) * fovt;
	direction.z = -1;
	vec3_normalize(&direction);
	apply_matrix(&direction, &data->cam.rotation);
	vec3_normalize(&direction);
	ray_new(res, &data->cam.pos, &direction);
}

static inline void
	deflect_cast(t_data *data, t_inter *inter, int depth)
{
	t_color	primary;
	t_ray	absorbed;

	if (data->scene_set.deflect == 1
	&& inter->obj->material.deflect_idx && !(inter->obj->material.absorb_idx))
	{
		primary = recursive_cast(data, &inter->deflected, depth + 1);
		color_scalar(&primary, inter->obj->material.deflect_idx);
		color_add(&inter->color, &primary);
	}
	else if (data->scene_set.absorb == 1
		&& inter->obj->material.absorb_idx != 0)
	{
		fresnel(inter, 1.5);
		primary = recursive_cast(data, &inter->deflected, depth + 1);
		color_scalar(&primary, inter->kr * inter->obj->material.deflect_idx);
		color_add(&inter->color, &primary);
		inter_setrefract(inter, &absorbed);
		primary = recursive_cast(data, &absorbed, depth + 1);
		color_scalar(&primary, inter->obj->material.absorb_idx);
		color_add(&inter->color, &primary);
	}
}

t_color
	recursive_cast(t_data *data, t_ray *ray, int depth)
{
	t_inter	inter;
	t_color	ambient;

	inter_set(&inter, ray);
	cast_primary(data, &inter);
	if (inter.obj == NULL)
		return (data->scene_set.back_color);
	ambient = inter.obj->material.color_ambient;
	if (data->lst_light == NULL || !data->scene_set.light)
		return (ambient);
	color_scalar(&ambient, data->scene_set.amb_light);
	inter_find(&inter, &inter.point);
	inter.find_normal(&inter);
	cast_shadow(data, &inter);
	color_scalar(&inter.color, 1.0f - data->scene_set.amb_light);
	color_add(&inter.color, &ambient);
	if (depth < data->scene_set.depth_max)
		deflect_cast(data, &inter, depth);
	return (inter.color);
}

int __attribute__((hot))
	process_pixel(int x, int y, void *arg)
{
	t_data	*data;
	t_ray	rene;
	t_color	color;

	data = arg;
	cam_ray(data, &rene, x + 0.5, y + 0.5);
	color = recursive_cast(data, &rene, 0);
	color_clamp(&color, 0, 1);
	return (colortoi(color));
}
