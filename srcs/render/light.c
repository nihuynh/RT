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
	t_vec3		hit_pos;
	t_vec3		normal;
	t_ray		cam_ray;
	t_vec3		specular_dir;
	t_color		diffuse_light_final;
	t_color		specular_light_final;
}				t_shading;

void add_specular_light(t_color *specular, t_shading shading, bool no_specular);
void add_diffuse_light(t_color *diffuse, t_shading shading, bool no_diffuse);
void shade_1_light(t_color *light_accum, t_shading s, t_list *obj, t_scene *settings);

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
	inter_light.dist = vec3_mag(vec3_sub_(s.light.origin, s.hit_pos));
	return (cast_light_primary(obj_list, &inter_light));
}

float
	get_distance_attenuation(float distance, t_scene *settings)
{
	if (settings->no_i_light)
		return (1);
	return (1 / (distance * distance));
}

#define DIFFUSE 0
#define SPECULAR 1

t_color
	get_lighting(t_list *obj, t_list *light_lst, t_inter *inter, t_scene *settings)
{
	t_list	*lst;
	t_light	light;
	t_color	accum_light[2];

	lst = light_lst;
	inter_setdeflect(inter, &inter->deflected);
	accum_light[DIFFUSE] = (t_color){0, 0, 0};
	accum_light[SPECULAR] = (t_color){0, 0, 0};
	while (lst != NULL)
	{
		
		light = *(t_light*)lst->content;
		t_shading shading;
		shading.light = *(t_light*)lst->content;
		shading.hit_pos = inter->point;
		shading.normal = inter->n;
		shading.mat = inter->obj->material;
		shading.cam_ray = inter->ray;
		shading.specular_dir = inter->deflected.dir;
		shading.light_dir = vec3_normalize_(vec3_sub_(light.origin, inter->point));
		shade_1_light(accum_light, shading, obj, settings);
		lst = lst->next;
	}
	color_mult(&accum_light[DIFFUSE], &inter->obj->material.color_diffuse);
	color_mult(&accum_light[SPECULAR], &inter->obj->material.color_specular);
	return (color_add_(accum_light[DIFFUSE], accum_light[SPECULAR]));
}

/**
	input: ray, hitpos, normal, light, obj, settings

	specular_ray = ray(hitpos, reflect(ray, normal))
 	foreach light {
		light_vec = lightpos - hitpos
 		if (settings)
 		{
 			light_ray = ray(hitpos, light_vec.normalize)
 			light_ray.origin += normal * 0.005;
 			visibility = get_light_visibility(obj_list, light_ray)
 			if (visibility == 0)
 				continue;
 		}
		if (settings)
			atten = get_distance_attenuation(light_ray)
		light_color *= visibility * atten * light.intensity
		if (settings)
			diffuse_light += light.color * get_diffuse(light_vec, normal)
		if (settings)
			specular_light += light.color * get_specular(light_vec, specular_ray)
 	}
**/


void shade_1_light(t_color *light_accum, t_shading s, t_list *obj, t_scene *settings)
{
	s.light.intensity *= get_light_visibility(s, obj, settings);
	if (s.light.intensity == 0)
		return;
	s.light.intensity *= get_distance_attenuation(vec3_mag(vec3_sub_(s.light.origin, s.hit_pos)), settings);
	color_scalar(&s.light.color, s.light.intensity);
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
