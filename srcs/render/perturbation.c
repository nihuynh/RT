/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perturbation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 06:48:02 by nihuynh           #+#    #+#             */
/*   Updated: 2019/05/20 13:46:36 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftmath.h"
#include "ftio.h"
#include "rtstruct.h"
#include "librt.h"
#include "color.h"
#include <math.h>
#include <stdlib.h>

float
	pattern_checkers(float x, float y)
{
	int yi;
	int xi;

	xi = abs((int)x) + (x < 0);
	yi = abs((int)y) + (y < 0);
	return ((xi + yi) & 0x1);
}

float
	pattern_strips(float x, float y)
{
	float	pattern;
	float	angle;

	angle = 45 * DEG_TO_RAD;
	pattern = x * cosf(angle) - y * sinf(angle);
	if (pattern < 0)
		pattern -= 0.5f;
	pattern = fabsf(fmodf(pattern, 1)) < 0.5f;
	return (pattern);
}

t_color
	texture_strips(t_material *mat, t_vec3 uv)
{
	t_color res;

	res = color_linear_inter(mat->color_diffuse, mat->color_tex,
		pattern_strips(uv.x, uv.y));
	return (res);
}

t_color
	texture_checkers(t_material *mat, t_vec3 uv)
{
	t_color res;

	res = color_linear_inter(mat->color_diffuse, mat->color_tex,
		pattern_checkers(uv.x, uv.y));
	return (res);
}

t_color
	sample(t_material *mat, t_vec3 uv)
{
	unsigned char	*pixel_ptr;
	t_texture		*texture;
	t_color			pixel;
	int				x;
	int				y;

	texture = mat->tex;
	if (mat->uv_mapping.repeat)
	{
		uv.x = fmodf(uv.x, 1) + (uv.x < 0);
		uv.y = fmodf(uv.y, 1) + (uv.y < 0);
	}
	else
	{
		uv.x = ft_clampf(uv.x, 0, 0.99999f);
		uv.y = ft_clampf(uv.y, 0, 0.99999f);
	}
	x = uv.x * texture->width;
	y = uv.y * texture->height;
	pixel_ptr = (unsigned char*)texture->pixels;
	pixel_ptr += (y * texture->width * texture->bpp) + (x * texture->bpp);
	pixel.r = pixel_ptr[0] / 255.f;
	pixel.g = pixel_ptr[1] / 255.f;
	pixel.b = pixel_ptr[2] / 255.f;
	return (pixel);
}
