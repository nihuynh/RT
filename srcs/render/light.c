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

static inline float
	facing_ratio(t_inter *inter_light, int no_facing)
{
	float	res;

	res = vec3_dot(&inter_light->ray.dir, &inter_light->n);
	if (no_facing == 1)
		return (1);
	return (res >= 0) ? res : 0;
}

static inline void
	shine(t_inter *inter, t_inter *inter_light)
{
	float	ratio;
	t_color	shine_color;

	ratio = fmaxf(0.f, vec3_dot(&inter->deflected.dir, &inter_light->ray.dir));
	ratio = powf(ratio, inter->obj->material.spec_power)
		* inter->obj->material.spec_idx;
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
		scale = cast_light_primary(data, &inter_light);
	if (scale > 0)
	{
		color_scalar(&tmp, scale);
		scale = facing_ratio(&inter_light, data->scene_set.no_facing);
		if (data->scene_set.no_shine == 0)
			shine(inter, &inter_light);
		color_scalar(&tmp, scale);
		color_add(color, &tmp);
	}
}

void
	cast_shadow(t_data *data, t_inter *inter)
{
	t_list	*lst;
	t_light	*light;
	t_color	color;

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
