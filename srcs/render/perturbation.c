/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perturbation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 06:48:02 by nihuynh           #+#    #+#             */
/*   Updated: 2019/05/20 12:52:53 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftmath.h"
#include "ftio.h"
#include "rtstruct.h"
#include "librt.h"
#include "color.h"
#include <math.h>

float
	pattern_checkers(float x, float y)
{
	float	pattern;

	pattern = (fmodf(x, 1.f) < 0.5f) ^ (fmodf(y, 1) < 0.5f);
	return (pattern);
}

float
	pattern_strips(float x, float y)
{
	float	pattern;
	float	angle;

	angle = 45 * DEG_TO_RAD;
	pattern = x * cosf(angle) - y * sinf(angle);
	if (pattern < 0)
		pattern -= 5;
	pattern = fabsf(fmodf(pattern, 10)) < 5;
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
	t_texture *tex;

	tex = mat->tex;
	if (!(tex->pixels))
	{
		ft_printf("Texture is not load.");
		ft_error(__func__, __LINE__);
	}
//	printf("x: %f  y:  %f\n", x, y);
	int x_ = (ft_clampf(uv.x, 0, 1) * (tex->width - 1));
	int y_ = (ft_clampf(uv.y, 0, 1) * (tex->height - 1));
//	printf("x: %d  y:  %d\n\n", x_, y_);
//	int x_ = ft_clamp(x, 0, texture->width);
//	int y_ = ft_clamp(y, 0, texture->height);
//	int y_ = (ft_clampf(y, 0, 0.9) * (texture->height - 1));
	t_color result;
	tmp *ptr = (tmp *) tex->pixels;
	ptr += (y_ * (tex->width) + (x_));
	result.r = ptr->a / 255.f;
	result.g = ptr->b / 255.f;
	result.b = ptr->c / 255.f;
//	vec3_print((t_vec3 *) (&result));
	return (result);
}
