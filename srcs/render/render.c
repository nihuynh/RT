/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 22:26:16 by sklepper          #+#    #+#             */
/*   Updated: 2019/05/06 16:27:31 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>
#include "librt.h"
#include "libft.h"

t_shading get_shading_data(t_inter *inter);

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
	if (color_bool(inter->obj->material.reflection_color)
		|| color_bool(inter->obj->material.refraction_color))
		kr = fresnel(inter->ray.dir, inter->n, inter->obj->material.refraction_idx);
	if (settings.deflect && color_bool(inter->obj->material.reflection_color))
	{
		reflection = recursive_cast(scene, settings, inter->deflected, depth + 1);
		color_mult(&reflection, &inter->obj->material.reflection_color);
		color_scalar(&reflection, kr);
	}
	if (settings.absorb && color_bool(inter->obj->material.refraction_color))
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
	t_shading	shading;
	t_inter		inter;
	t_color		lighting;

	inter_set(&inter, ray);
	cast_primary(scene.lst_obj, &inter);
	if (inter.obj == NULL)
		return (settings.back_color);
	shading = get_shading_data(&inter);
	lighting = get_lighting(shading, scene, &settings);
	if (depth < settings.depth_max)
		color_add(&lighting, cast_bounce(scene, settings, &inter, depth));
	return (lighting);
}

t_shading get_shading_data(t_inter *inter)
{
	t_shading shading;

	ft_bzero(&shading, sizeof(t_shading));
	inter_find(inter, &inter->point);
	inter->obj->find_normal(inter);
	inter_setdeflect(inter, &inter->deflected);
	shading.uv = inter->obj->get_uv(inter);
	shading.hit_pos = inter->point;
	shading.normal = inter->n;
	shading.mat = inter->obj->material;
	shading.specular_dir = inter->deflected.dir;
	return (shading);
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
	if (data->settings.anti_a)
		color = anti_aliasing(color, data, x, y);
	color_clamp(&color, 0, 1);
	color_mult(&color, &data->settings.filter);
	color = sepia(color);
	// color = grayscale(color);
	return (colortoi(color));
}
