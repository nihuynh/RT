/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 14:41:41 by sklepper          #+#    #+#             */
/*   Updated: 2019/07/13 23:02:52 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "librt.h"
#include "ftlist.h"
#include "ftmem.h"
#include <math.h>

t_color
	get_light_visibility(t_shading s, t_list *obj_list, t_settings *settings)
{
	t_inter	inter_light;
	t_ray	ray;

	if (settings->shadow == false)
		return ((t_color){1, 1, 1});
	ray.origin = s.hit_pos;
	ray.dir = s.light_dir;
	ray_offset_origin(&ray, s.normal);
	ft_bzero(&inter_light, sizeof(t_inter));
	inter_light.ray = ray;
	inter_light.dist = s.light_dist;
	return (cast_light_primary(obj_list, &inter_light, s.light_dist));
}

void
	set_light_data(t_shading *shading, t_light *light)
{
	shading->light = *light;
	shading->light_dir = vec3_sub_(light->origin, shading->hit_pos);
	shading->light_dist = vec3_mag(shading->light_dir);
	vec3_normalize(&shading->light_dir);
}

void
	shade_1_light(t_color *light_accum, t_shading s, t_list *obj,
	t_settings *settings)
{
	t_color intensity;

	intensity = get_light_visibility(s, obj, settings);
	if (!(color_bool(intensity)))
		return ;
	color_scalar(&intensity, s.light.intensity);
	color_scalar(&intensity, get_distance_attenuation(s.light_dist));
	color_mult(&s.light.color, &intensity);
	add_diffuse_light(&light_accum[DIFFUSE], s, !settings->facing);
	add_specular_light(&light_accum[SPECULAR], s, !settings->shine);
}

t_color
	get_lighting(t_shading s, t_scene scene, t_settings *settings)
{
	t_list		*current_light;
	t_color		accum_light[2];
	t_color		diffuse_color;
	t_color		final_color;

	ft_bzero(&accum_light[0], sizeof(accum_light[0]));
	ft_bzero(&accum_light[1], sizeof(accum_light[1]));
	current_light = scene.lst_light;
	while (current_light != NULL)
	{
		set_light_data(&s, current_light->content);
		shade_1_light(accum_light, s, scene.lst_obj, settings);
		current_light = current_light->next;
	}
	if (s.mat.tex->f_texture)
		diffuse_color = s.mat.tex->f_texture(&s.mat, s.mat.tex, s.uv);
	else
		diffuse_color = s.mat.color_diffuse;
	final_color = color_mult_(settings->amb_light, diffuse_color);
	if (settings->light == false)
		return (diffuse_color);
	color_mult(&accum_light[DIFFUSE], &diffuse_color);
	color_mult(&accum_light[SPECULAR], &s.mat.color_specular);
	color_add(&final_color, accum_light[DIFFUSE]);
	color_add(&final_color, accum_light[SPECULAR]);
	return (final_color);
}
