/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 14:41:41 by sklepper          #+#    #+#             */
/*   Updated: 2019/04/13 16:01:58 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "librt.h"
#include "libui.h"
#include "libft.h"
#include <math.h>

void add_diffuse_light(t_color *diffuse, t_color light_color, t_inter *inter, t_inter inter_light);
void add_specular_light(t_color *specular, t_color light_color, t_inter *inter, t_inter inter_light);

static inline float
	facing_ratio(t_vec3 ray_dir, t_vec3 normal, int no_facing)
{
	float	res;

	res = vec3_dot(&ray_dir, &normal);
	if (no_facing == 1)
		return (1);
	return (res >= 0) ? res : 0;
}

static inline float
	specular_factor(t_inter *inter, t_inter *inter_light, bool no_specular)
{
	float factor;

	if (no_specular)
		return (0);
	factor = fmaxf(0.f, vec3_dot(&inter->deflected.dir, &inter_light->ray.dir));
	factor = powf(factor, inter->obj->material.spec_power);
	factor *= inter->obj->material.spec_idx;
	return (factor);
}

static inline void
	shine(t_inter *inter, t_inter *inter_light, bool no_specular)
{
	float	ratio;
	t_color	shine_color;

	if (no_specular)
		return ;
	ratio = specular_factor(inter, inter_light, no_specular);
	shine_color = inter_light->color;
	color_scalar(&shine_color, ratio);
	color_mult(&shine_color, &inter->obj->material.color_specular);
	color_add(&inter->color, &shine_color);
}

static inline void
	shadow(t_data *data, t_inter *inter, t_light *light, t_color *color)
{
	t_inter	inter_light;
	t_color	tmp;
	float	scale;

	tmp = light->color;
	inter_setlight(inter, &inter_light, light);
	scale = inter_light.dist * inter_light.dist;
	if (data->scene_set.no_i_light == 0)
		color_scalar(&tmp, (light->intensity / scale));
	if (data->scene_set.no_shadow)
		scale = 1;
	else
		scale = cast_light_primary(data->lst_obj, &inter_light);
	if (scale > 0)
	{
		color_scalar(&tmp, scale);
		scale = facing_ratio(inter_light.ray.dir, inter_light.n, data->scene_set.no_facing);
		shine(inter, &inter_light, data->scene_set.no_shine);
		color_scalar(&tmp, scale);
		color_add(color, &tmp);
	}
}

float
	get_light_visibility(t_inter *inter_light, t_list *obj_list, t_scene *settings)
{
	if (settings->no_shadow)
		return (1);
	return (cast_light_primary(obj_list, inter_light));
}

float
	get_distance_attenuation(float distance, t_scene *settings)
{
	if (settings->no_i_light)
		return (1);
	return (1 / (distance * distance));
}

t_color
	get_lighting(t_list *obj, t_list *light_lst, t_inter *inter, t_scene *settings)
{
	t_list	*lst;
	t_light	light;
	t_color	diffuse_light_final;
	t_color	specular_light_final;

	lst = light_lst;
	inter_setdeflect(inter, &inter->deflected);
	diffuse_light_final = (t_color){0, 0, 0};
	specular_light_final = (t_color){0, 0, 0};
	while (lst != NULL)
	{
		light = *(t_light*)lst->content;
		float	visibility;
		float	attenuation;
		t_inter	inter_light;

		inter_setlight(inter, &inter_light, &light);
		visibility = get_light_visibility(&inter_light, obj, settings);
//		if (visibility == 0)
//			continue;
		attenuation = get_distance_attenuation(inter_light.dist, settings);
		color_scalar(&light.color, visibility * attenuation * light.intensity);
		if (settings->no_facing == false)
			add_diffuse_light(&diffuse_light_final, light.color, inter, inter_light);
		if (settings->no_shine == false)
			add_specular_light(&specular_light_final, light.color, inter, inter_light);
		lst = lst->next;
	}
	color_mult(&diffuse_light_final, &inter->obj->material.color_diffuse);
	color_mult(&specular_light_final, &inter->obj->material.color_specular);
	return (color_add_(diffuse_light_final, specular_light_final));
}

void add_specular_light(t_color *specular, t_color light_color, t_inter *inter, t_inter inter_light)
{
	float _specular_factor;

	_specular_factor = specular_factor(inter, &inter_light, false);
	color_scalar(&light_color, _specular_factor);
	color_add(specular, &light_color);
}

void add_diffuse_light(t_color *diffuse, t_color light_color, t_inter *inter, t_inter inter_light)
{
	float diffuse_factor;

	diffuse_factor = facing_ratio(inter_light.ray.dir, inter->n, false);
	color_scalar(&light_color, diffuse_factor);
	color_add(diffuse, &light_color);
}

void
cast_shadow(t_data *data, t_inter *inter)
{
	t_list  *lst;
	t_light *light;
	t_color color;

	lst = data->lst_light;
	ft_bzero(&color, sizeof(t_color));
	inter_setdeflect(inter, &inter->deflected);
	while (lst != NULL)
	{
		light = lst->content;
		if (light != NULL)
			shadow(data, inter, light, &color);
		lst = lst->next;
	}
	color_mult(&inter->color, &color);
}
