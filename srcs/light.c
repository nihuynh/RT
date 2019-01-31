/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 14:41:41 by sklepper          #+#    #+#             */
/*   Updated: 2018/12/19 20:47:48 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "librt.h"
#include "libui.h"
#include "libft.h"

SIFLOAT	facing_ratio(t_inter *inter_light)
{
	float	res;

	res = vec3_dot(&inter_light->ray.n, &inter_light->n);
	if (NO_FACING)
		return (1);
	return (res >= 0) ? res : 0;
}

SIVOID	reflection(t_inter *inter, t_inter *inter_light)
{
	float	ratio;
	float	spec;
	t_color	shine_color;

	ratio = vec3_dot(&inter->reflected, &inter_light->ray.n);
	shine_color = inter_light->color;
	if (ratio >= inter->obj->diffuse)
	{
		spec = (1 - inter->obj->diffuse);
		ratio = ((ratio - inter->obj->diffuse) / spec) - spec;
		ratio = ft_clampf(ratio, 0, 1);
		color_scalar(&shine_color, ratio);
		color_max(&inter->color, &shine_color);
	}
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
		cast_primary(data, &inter_light);
	if (inter_light.obj == NULL)
	{
		scale = facing_ratio(&inter_light);
		if (!NO_SHINE)
			reflection(inter, &inter_light);
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
	if (!NO_SHINE)
		vec3_reflect(inter);
	while (lst != NULL)
	{
		light = lst->content;
		if (light != NULL)
			shadow(data, inter, light, &color);
		lst = lst->next;
	}
	color_mult(&inter->color, &color);
}
