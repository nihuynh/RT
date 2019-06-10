/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 22:26:16 by sklepper          #+#    #+#             */
/*   Updated: 2019/06/25 22:30:51 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_data.h"
#include "render.h"
#include "librt.h"
#include "ftmem.h"
#include <math.h>

void
	cam_ray(t_data *app, t_ray *res, float x, float y)
{
	float	fovt;
	float	r;
	t_pt3	direction;

	r = app->sdl->img.width / (float)app->sdl->img.height;
	fovt = tanf((app->settings.fov * DEG_TO_RAD) / 2);
	direction.x = (2 * x / app->sdl->img.width - 1) * fovt * r;
	direction.y = (1 - 2 * y / app->sdl->img.height) * fovt;
	direction.z = -1;
	vec3_normalize(&direction);
	apply_matrix(&direction, &app->cam.rotation);
	vec3_normalize(&direction);
	ray_new(res, &app->cam.pos, &direction);
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
	depth++;
	if (color_bool(inter->obj->material.reflection_color)
		|| color_bool(inter->obj->material.refraction_color))
		kr = fresnel(inter->ray.dir, inter->n, inter->obj->material.refraction_idx);
	if (settings.deflect && color_bool(inter->obj->material.reflection_color))
	{
		reflection = recursive_cast(scene, settings, inter->deflected, depth);
		color_mult(&reflection, &inter->obj->material.reflection_color);
		color_scalar(&reflection, kr);
	}
	if (settings.absorb && color_bool(inter->obj->material.refraction_color))
	{
		inter_setrefract(inter, &absorbed);
		refraction = recursive_cast(scene, settings, absorbed, depth);
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
		return (get_sky_color(scene, settings, ray));
	shading = get_shading_data(&inter);
	if (settings.normal_mapping == false)
		shading.shading_normal = shading.normal;
	if (settings.debug_normal)
		return (*(t_color*)&shading.shading_normal);
	lighting = get_lighting(shading, scene, &settings);
	if (depth < settings.depth_max)
		color_add(&lighting, cast_bounce(scene, settings, &inter, depth));
	return (lighting);
}

t_shading
	get_shading_data(t_inter *inter)
{
	t_shading s;

	ft_bzero(&s, sizeof(t_shading));
	inter_find(inter, &inter->point);
	inter->obj->find_normal(inter);
	s.uv = inter->obj->get_uv(inter);
	s.uv.z = 0;
	apply_uv_mapping(&s.uv, inter->obj->material.uv_mapping);
	s.hit_pos = inter->point;
	s.normal = inter->n;
	s.mat = inter->obj->material;
	s.shading_normal = compute_shading_normal(s.mat, s.uv, s.normal);
	inter_setdeflect(inter, s.shading_normal);
	s.specular_dir = inter->deflected.dir;
	return (s);
}

int __attribute__((hot))
	process_pixel(int x, int y, void *arg)
{
	t_data	*app;
	t_ray	rene;
	t_color	color;

	app = arg;
	cam_ray(app, &rene, x + 0.5, y + 0.5);
	color = recursive_cast(app->scene, app->settings, rene, 0);
	if (app->settings.anti_a && app->sdl->sub_sample == 1)
		color = anti_aliasing(color, app, x, y);
	color_clamp(&color, 0, 1);
	color_mult(&color, &app->settings.filter);
	if (app->sdl->sepia)
		color = sepia(color);
	if (app->sdl->grayscale)
		color = grayscale(color);
	if (app->sdl->cartoon)
		color = cartoon(color);
	if (app->sdl->negative)
		color = negative(color);
	return (colortoi(color));
}
