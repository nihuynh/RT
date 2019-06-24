/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 14:46:27 by nihuynh           #+#    #+#             */
/*   Updated: 2019/06/24 16:41:10 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "render.h"

t_color
	texture_perlin(t_material *mat, t_texture *texture, t_vec3 uv)
{
	t_color res;
	float	pattern;

	(void)texture;
	pattern = perlin(uv, 5, 3);
	pattern = (pattern + 1) / 2;
	res = color_linear_inter(mat->color_diffuse, mat->color_tex, pattern);
	return (res);
}

t_color
	texture_wood(t_material *mat, t_texture *texture, t_vec3 uv)
{
	t_color res;
	float	pattern;

	(void)texture;
	pattern = 20 * perlin(uv, 5, 3);
	pattern = (pattern + 1) / 2;
	pattern -= (int)pattern;
	res = color_linear_inter(mat->color_diffuse, mat->color_tex, pattern);
	return (res);
}

t_color
	texture_marble(t_material *mat, t_texture *texture, t_vec3 uv)
{
	t_color res;
	float	pattern;

	(void)texture;
	pattern = cosf((uv.x + perlin(uv, 5, 3)));
	res = color_linear_inter(mat->color_diffuse, mat->color_tex, pattern);
	return (res);
}

t_color
	texture_cloud(t_material *mat, t_texture *texture, t_vec3 uv)
{
	t_color res;
	float	pattern;

	(void)texture;
	pattern = perlin(uv, 3, 2);
	res = color_linear_inter(mat->color_diffuse, mat->color_tex, pattern);
	return (res);
}
