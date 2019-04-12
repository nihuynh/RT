/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 22:26:16 by sklepper          #+#    #+#             */
/*   Updated: 2019/04/12 16:13:05 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>
#include "librt.h"
#include "libft.h"

static inline void
	cam_ray(t_data *data, t_ray *res, float x, float y)
{
	float	fovt;
	float	r;
	t_pt3	direction;

	r = data->sdl.img.width / (float)data->sdl.img.height;
	fovt = tanf((FOV * DEG_TO_RAD) / 2);
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

	if (data->scene_settings.no_deflect == 0
	&& inter->obj->material.deflect_idx && !(inter->obj->material.absorb_idx))
	{
		itocolor(&primary, recursive_cast(data, &inter->deflected, depth + 1));
		color_scalar(&primary, inter->obj->material.deflect_idx);
		color_add(&inter->color, &primary);
	}
	else if (data->scene_settings.no_absorb == 0
		&& inter->obj->material.absorb_idx != 0)
	{
		fresnel(inter, 1.2);
		itocolor(&primary, recursive_cast(data, &inter->deflected, depth + 1));
		color_scalar(&primary, inter->kr * inter->obj->material.deflect_idx);
		color_add(&inter->color, &primary);
		inter_setrefract(inter, &absorbed);
		itocolor(&primary, recursive_cast(data, &absorbed, depth + 1));
		color_scalar(&primary, inter->obj->material.absorb_idx);
		color_add(&inter->color, &primary);
	}
}

int
	recursive_cast(t_data *data, t_ray *rene, int depth)
{
	t_inter	inter;
	t_color	primary;

	inter_set(&inter, rene);
	cast_primary(data, &inter);
	if (inter.obj == NULL)
		return (data->scene_settings.back_color);
	color_cpy(&primary, &inter.color);
	color_scalar(&primary, data->scene_settings.amb_light);
	if (data->lst_light == NULL || data->scene_settings.no_light == 1)
		return (colortoi(&inter.color));
	inter.find_normal(&inter);
	cast_shadow(data, &inter);
	color_scalar(&inter.color, 1.0f - data->scene_settings.amb_light);
	color_add(&inter.color, &primary);
	if (depth < data->scene_settings.depth_max)
		deflect_cast(data, &inter, depth);
	return (colortoi(&inter.color));
}

int __attribute__((hot))
	process_pixel(int x, int y, void *arg)
{
	t_data	*data;
	t_ray	rene;

	data = arg;
	cam_ray(data, &rene, x + 0.5, y + 0.5);
	return (recursive_cast(data, &rene, 0));
}
