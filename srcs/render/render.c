/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 22:26:16 by sklepper          #+#    #+#             */
/*   Updated: 2019/05/20 13:17:35 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>
#include "librt.h"
#include "libft.h"

void
	cam_ray(t_data *app, t_ray *res, float x, float y)
{
	float	fovt;
	float	r;
	t_pt3	direction;

	r = app->sdl.img.width / (float)app->sdl.img.height;
	fovt = tanf((app->settings.fov * DEG_TO_RAD) / 2);
	direction.x = (2 * x / app->sdl.img.width - 1) * fovt * r;
	direction.y = (1 - 2 * y / app->sdl.img.height) * fovt;
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

t_shading
	get_shading_data(t_inter *inter)
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
	t_data	*app;
	t_ray	rene;
	t_color	color;

	app = arg;
	cam_ray(app, &rene, x + 0.5, y + 0.5);
	color = recursive_cast(app->scene, app->settings, rene, 0);
	if (app->settings.anti_a)
		color = anti_aliasing(color, app, x, y);
	color_clamp(&color, 0, 1);
	color_mult(&color, &app->settings.filter);
	if (app->sdl.sepia)
		color = sepia(color);
	if (app->sdl.grayscale)
		color = grayscale(color);
	return (colortoi(color));
}
