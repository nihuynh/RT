/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 22:26:16 by sklepper          #+#    #+#             */
/*   Updated: 2019/04/25 15:25:48 by sklepper         ###   ########.fr       */
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
	fovt = tanf((data->settings.fov * DEG_TO_RAD) / 2);
	direction.x = (2 * x / data->sdl.img.width - 1) * fovt * r;
	direction.y = (1 - 2 * y / data->sdl.img.height) * fovt;
	direction.z = -1;
	vec3_normalize(&direction);
	apply_matrix(&direction, &data->cam.rotation);
	vec3_normalize(&direction);
	ray_new(res, &data->cam.pos, &direction);
}

static inline void
	cast_bounce(t_color *color, t_data *data, t_inter *inter, int depth)
{
	t_ray	absorbed;
	t_color	refraction;
	t_color	reflection;
	float	kr;

	kr = 1;
	if (inter->obj->material.deflect_idx || inter->obj->material.absorb_idx)
		kr = fresnel(inter->ray.dir, inter->n, 1.5);
	if (data->settings.deflect && inter->obj->material.deflect_idx)
	{
		reflection = recursive_cast(data, inter->deflected, depth + 1);
		color_scalar(&reflection, inter->obj->material.deflect_idx);
		color_scalar(&reflection, kr);
		color_add(color, &reflection);
	}
	if (data->settings.absorb && inter->obj->material.absorb_idx)
	{
		inter_setrefract(inter, &absorbed);
		refraction = recursive_cast(data, absorbed, depth + 1);
		color_scalar(&refraction, inter->obj->material.absorb_idx);
		color_scalar(&refraction, 1 - kr);
		color_add(color, &refraction);
	}
}

t_color
	recursive_cast(t_data *data, t_ray ray, int depth)
{
	t_inter	inter;
	t_color	ambient;
	t_color	lighting;

	inter_set(&inter, ray);
	cast_primary(data, &inter);
	if (inter.obj == NULL)
		return (data->settings.back_color);
	ambient = inter.obj->material.color_diffuse;
	if (data->scene.lst_light == NULL || !data->settings.light)
		return (ambient);
	color_mult(&ambient, &data->settings.amb_light);
	inter_find(&inter, &inter.point);
	inter.obj->find_normal(&inter);
	lighting = get_lighting(data->scene.lst_obj, data->scene.lst_light, &inter, &data->settings);
	color_add(&lighting, &ambient);
	if (depth < data->settings.depth_max)
		cast_bounce(&lighting, data, &inter, depth);
	return (lighting);
}

int __attribute__((hot))
	process_pixel(int x, int y, void *arg)
{
	t_data	*data;
	t_ray	rene;
	t_color	color;

	data = arg;
	cam_ray(data, &rene, x + 0.5, y + 0.5);
	color = recursive_cast(data, rene, 0);
	color_clamp(&color, 0, 1);
	return (colortoi(color));
}
