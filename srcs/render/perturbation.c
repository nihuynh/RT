/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perturbation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 06:48:02 by nihuynh           #+#    #+#             */
/*   Updated: 2019/05/12 07:56:09 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftmath.h>
#include "rt.h"
#include "librt.h"
#include "color.h"
#include <math.h>

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

typedef struct tmp {
	unsigned char a, b, c;
} tmp;

t_color sample(t_material *mat, t_vec3 uv)
{
	t_texture	*texture;
	int			x_;
	int			y_;

	texture = mat->tex;
//	printf("x: %f  y:  %f\n", x, y);
	if (mat->uv_mapping.repeat)
	{
		x_ = fabsf(fmodf(uv.x, 1) * (texture->width - 1));
		y_ = fabsf(fmodf(uv.y, 1) * (texture->height - 1));
	}
	else
	{
		x_ = (ft_clampf(uv.x, 0, 1) * (texture->width - 1));
		y_ = (ft_clampf(uv.y, 0, 1) * (texture->height - 1));
	}
//	printf("x: %d  y:  %d\n\n", x_, y_);
//	int x_ = ft_clamp(x, 0, texture->width);
//	int y_ = ft_clamp(y, 0, texture->height);
//	int y_ = (ft_clampf(y, 0, 0.9) * (texture->height - 1));
	t_color result;
	tmp *ptr = (tmp *) texture->pixels;
	ptr += (y_ * (texture->width) + (x_));
	result.r = ptr->a / 255.f;
	result.g = ptr->b / 255.f;
	result.b = ptr->c / 255.f;
//	vec3_print((t_vec3 *) (&result));
	return (result);
}
