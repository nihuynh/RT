/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perturbation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 06:48:02 by nihuynh           #+#    #+#             */
/*   Updated: 2019/06/19 01:13:46 by nihuynh          ###   ########.fr       */
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

	xi = abs((int)x) + (x < 0.5);
	yi = abs((int)y) + (y < 0.5);
	return ((xi + yi) & 0x1);
}

float
	pattern_strips(float x, float y)
{
	float	pattern;
	float	pos_xy;

	pos_xy = x + y;
	pattern = ft_btwf(pos_xy, 0.0f, 0.5f) || ft_btwf(pos_xy, 1.0f, 1.5f);
	return (pattern);

}

t_color
	texture_strips(t_material *mat, t_texture *texture, t_vec3 uv)
{
	t_color res;

	res = color_linear_inter(mat->color_diffuse, mat->color_tex,
		pattern_strips(uv.x, uv.y));
	(void)texture;
	return (res);
}

t_color
	texture_checkers(t_material *mat, t_texture *texture, t_vec3 uv)
{
	t_color res;

	res = color_linear_inter(mat->color_diffuse, mat->color_tex,
		pattern_checkers(uv.x, uv.y));
	(void)texture;
	return (res);
}

t_color
	sample(t_material *mat, t_texture *texture, t_vec3 uv)
{
	unsigned char	*pixel_ptr;
	t_color			pixel;
	int				x;
	int				y;

	(void)mat;
	x = uv.x * (texture->width - 1);
	y = uv.y * (texture->height - 1);
	pixel_ptr = (unsigned char*)texture->pixels;
	pixel_ptr += (y * texture->width * texture->bpp) + (x * texture->bpp);
	pixel.r = pixel_ptr[0] / 255.f;
	pixel.g = pixel_ptr[1] / 255.f;
	pixel.b = pixel_ptr[2] / 255.f;
	return (pixel);
}
