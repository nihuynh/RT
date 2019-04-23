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

typedef struct	s_shading {
	t_material	mat;
	t_light		light;
	t_vec3		light_dir;
	float		light_dist;
	t_vec3		hit_pos;
	t_vec3		normal;
	t_vec3		specular_dir;
}				t_shading;

void add_specular_light(t_color *specular, t_shading shading, bool no_specular);
void add_diffuse_light(t_color *diffuse, t_shading shading, bool no_diffuse);
void shade_1_light(t_color *light_accum, t_shading s, t_list *obj, t_scene *settings);

static inline float
	facing_ratio(t_vec3 ray_dir, t_vec3 normal, int no_facing)
{
	float	res;

	if (no_facing == 1)
		return (1);
	res = vec3_dot(&ray_dir, &normal);
	return (res >= 0) ? res : 0;
}

static inline float
	specular_factor_(t_shading shading)
{
	float factor;

	factor = fmaxf(0.f, vec3_dot(&shading.specular_dir, &shading.light_dir));
	factor = powf(factor, shading.mat.spec_power);
	factor *= shading.mat.spec_idx;
	return (factor);
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
	get_light_visibility(t_shading s, t_list *obj_list, t_scene *settings)
{
	t_inter	inter_light;
	t_ray	ray;

	if (settings->no_shadow)
		return (1);
	ray.origin = s.hit_pos;
	ray.dir = s.light_dir;
	ray_offset_origin(&ray, s.normal);
	ft_bzero(&inter_light, sizeof(t_inter));
	inter_light.ray = ray;
	inter_light.dist = s.light_dist;
	return (cast_light_primary(obj_list, &inter_light));
}

float
	get_distance_attenuation(float distance)
{
	return (1 / (distance * distance));
}

#define DIFFUSE 0
#define SPECULAR 1

t_shading set_shading_data(const t_inter *inter, t_light *light)
{
	t_shading shading;

	shading.light = *light;
	shading.light_dir = vec3_sub_(light->origin, inter->point);
	shading.light_dist = vec3_mag(shading.light_dir);
	shading.hit_pos = inter->point;
	shading.normal = inter->n;
	shading.mat = inter->obj->material;
	shading.specular_dir = inter->deflected.dir;
	vec3_normalize(&shading.light_dir);
	return (shading);
}

t_color
	get_lighting(t_list *obj, t_list *light_lst, t_inter *inter, t_scene *settings)
{
	t_shading	shading;
	t_list		*lst;
	t_color		accum_light[2];

	lst = light_lst;
	inter_setdeflect(inter, &inter->deflected);
	accum_light[DIFFUSE] = (t_color){0, 0, 0};
	accum_light[SPECULAR] = (t_color){0, 0, 0};
	while (lst != NULL)
	{
		shading = set_shading_data(inter, (t_light*)lst->content);
		shade_1_light(accum_light, shading, obj, settings);
		lst = lst->next;
	}
	color_mult(&accum_light[DIFFUSE], &inter->obj->material.color_diffuse);
	color_mult(&accum_light[SPECULAR], &inter->obj->material.color_specular);
	return (color_add_(accum_light[DIFFUSE], accum_light[SPECULAR]));
}

void shade_1_light(t_color *light_accum, t_shading s, t_list *obj, t_scene *settings)
{
	float intensity;

	intensity = get_light_visibility(s, obj, settings);
	if (intensity == 0)
		return;
	intensity *= s.light.intensity * get_distance_attenuation(s.light_dist);
	color_scalar(&s.light.color, intensity);
	add_diffuse_light(&light_accum[DIFFUSE], s, settings->no_facing);
	add_specular_light(&light_accum[SPECULAR], s, settings->no_shine);
}

void add_specular_light(t_color *specular, t_shading shading, bool no_specular)
{
	float _specular_factor;

	if (no_specular)
		return ;
	_specular_factor = specular_factor_(shading);
	color_scalar(&shading.light.color, _specular_factor);
	color_add(specular, &shading.light.color);
}

void add_diffuse_light(t_color *diffuse, t_shading shading, bool no_diffuse)
{
	float diffuse_factor;

	if (no_diffuse)
		return ;
	diffuse_factor = facing_ratio(shading.light_dir, shading.normal, false);
	color_scalar(&shading.light.color, diffuse_factor);
	color_add(diffuse, &shading.light.color);
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
