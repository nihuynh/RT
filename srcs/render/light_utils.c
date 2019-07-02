/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 23:51:36 by nihuynh           #+#    #+#             */
/*   Updated: 2019/07/03 00:00:06 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "librt.h"

float
	get_distance_attenuation(float distance)
{
	return (1 / (distance * distance));
}

static inline float
	specular_factor(t_shading shading)
{
	float factor;

	factor = fmaxf(0.0f, vec3_dot(&shading.specular_dir, &shading.light_dir));
	factor = powf(factor, shading.mat.spec_power);
	if (shading.mat.spec_map->f_texture)
	{
		factor *= (1 - shading.mat.spec_map->f_texture(&shading.mat,
													shading.mat.tex,
													shading.uv).r);
	}
	factor *= shading.mat.spec_idx;
	return (factor);
}

void
	add_specular_light(t_color *specular, t_shading shading, bool no_specular)
{
	float spec_factor;

	if (no_specular)
		return ;
	spec_factor = specular_factor(shading);
	color_scalar(&shading.light.color, spec_factor);
	color_add(specular, shading.light.color);
}

static inline float
	facing_ratio(t_vec3 ray_dir, t_vec3 normal)
{
	float	res;

	res = vec3_dot(&ray_dir, &normal);
	return (res >= 0) ? res : 0;
}

void
	add_diffuse_light(t_color *diffuse, t_shading shading, bool no_diffuse)
{
	float diffuse_factor;

	if (no_diffuse)
		return ;
	diffuse_factor = facing_ratio(shading.light_dir, shading.shading_normal);
	color_scalar(&shading.light.color, diffuse_factor);
	color_add(diffuse, shading.light.color);
}
