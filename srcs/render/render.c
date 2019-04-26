/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 22:26:16 by sklepper          #+#    #+#             */
/*   Updated: 2019/04/26 23:32:53 by sklepper         ###   ########.fr       */
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

static inline t_color
	cast_bounce(t_scene scene, t_settings settings, t_inter *inter, int depth)
{
	t_ray	absorbed;
	t_color	reflection;
	t_color	refraction;
	float	kr;

	reflection = (t_color){0, 0, 0};
	refraction = (t_color){0, 0, 0};
	kr = 1;
	if (bool_color(inter->obj->material.reflection_color)
		|| bool_color(inter->obj->material.refraction_color))
		kr = fresnel(inter->ray.dir, inter->n, inter->obj->material.refraction_idx);
	if (settings.deflect && bool_color(inter->obj->material.reflection_color))
	{
		reflection = recursive_cast(scene, settings, inter->deflected, depth + 1);
		color_mult(&reflection, &inter->obj->material.reflection_color);
		color_scalar(&reflection, kr);
	}
	if (settings.absorb && bool_color(inter->obj->material.refraction_color))
	{
		inter_setrefract(inter, &absorbed);
		refraction = recursive_cast(scene, settings, absorbed, depth + 1);
		color_mult(&refraction, &inter->obj->material.refraction_color);
		color_scalar(&refraction, 1 - kr);
	}
	return (color_add_(reflection, refraction));
}

t_color
	recursive_cast(t_scene scene, t_settings settings, t_ray ray, int depth)
{
	t_inter	inter;
	t_color	ambient;
	t_color	lighting;

	inter_set(&inter, ray);
	cast_primary(scene.lst_obj, &inter);
	if (inter.obj == NULL)
		return (settings.back_color);
	ambient = inter.obj->material.color_diffuse;
	if (scene.lst_light == NULL || !settings.light)
		return (ambient);
	color_mult(&ambient, &settings.amb_light);
	inter_find(&inter, &inter.point);
	inter.obj->find_normal(&inter);
	lighting = get_lighting(scene, &inter, &settings);
	color_add(&lighting, ambient);
	if (depth < settings.depth_max)
		color_add(&lighting, cast_bounce(scene, settings, &inter, depth));
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
	color = recursive_cast(data->scene, data->settings, rene, 0);
	color_clamp(&color, 0, 1);
	return (colortoi(color));
}
