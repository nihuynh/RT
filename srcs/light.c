/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 14:41:41 by sklepper          #+#    #+#             */
/*   Updated: 2019/03/13 18:31:48 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "librt.h"
#include "libui.h"
#include "libft.h"
#include <math.h>

SIFLOAT	facing_ratio(t_inter *inter_light)
{
	float	res;

	res = vec3_dot(&inter_light->ray.n, &inter_light->n);
	if (NO_FACING)
		return (1);
	return (res >= 0) ? res : 0;
}

SIVOID	shine(t_inter *inter, t_inter *inter_light)
{
	float	ratio;
	t_color	shine_color;

	ratio = fmaxf(0.f, vec3_dot(&inter->deflected.n, &inter_light->ray.n));
	ratio = powf(ratio, inter->obj->material.spec_power)
		* inter->obj->material.spec_idx;
	shine_color = inter_light->color;
	color_scalar(&shine_color, ratio);
	color_mult(&shine_color, &inter->obj->material.color_specular);
	color_add(&inter->color, &shine_color);
}

SIVOID	shadow(t_data *data, t_inter *inter, t_light *light, t_color *color)
{
	t_inter	inter_light;
	t_color	tmp;
	float	scale;

	tmp = light->color;
	inter_setlight(inter, &inter_light, light);
	scale = inter_light.dist * inter_light.dist;
	if (!NO_I_LIGHT)
		color_scalar(&tmp, (light->intensity / scale));
	if (!NO_SHADOW)
		cast_light_primary(data, &inter_light);
	if (inter_light.obj == NULL)
	{
		scale = facing_ratio(&inter_light);
		if (!NO_SHINE)
			shine(inter, &inter_light);
		color_scalar(&tmp, scale);
		color_add(color, &tmp);
	}
}

void	cast_shadow(t_data *data, t_inter *inter)
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
