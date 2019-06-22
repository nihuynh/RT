/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perturbation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 06:48:02 by nihuynh           #+#    #+#             */
/*   Updated: 2019/06/22 18:38:55 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ftmath.h"
#include "rtstruct.h"
#include "librt.h"
#include "color.h"
#include <math.h>

t_color
	texture_strips(t_material *mat, t_texture *texture, t_vec3 uv)
{
	t_color res;
	float	pattern;
	float	pos_xy;

	(void)texture;
	pos_xy = uv.x + uv.y;
	pattern = ft_btwf(pos_xy, 0.0f, 0.5f) || ft_btwf(pos_xy, 1.0f, 1.5f);
	res = color_linear_inter(mat->color_diffuse, mat->color_tex, pattern);
	return (res);
}

t_color
	texture_checkers(t_material *mat, t_texture *texture, t_vec3 uv)
{
	t_color	res;
	float	pattern;
	int		yi;
	int		xi;

	(void)texture;
	xi = abs((int)uv.x) + (uv.x < 0.5);
	yi = abs((int)uv.y) + (uv.y < 0.5);
	pattern = (xi + yi) & 0x1;
	res = color_linear_inter(mat->color_diffuse, mat->color_tex, pattern);
	return (res);
}

t_color
	texture_wave(t_material *mat, t_texture *texture, t_vec3 uv)
{
	t_color res;

	(void)texture;
	res = color_linear_inter(mat->color_diffuse, mat->color_tex, sinf(uv.x));
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
