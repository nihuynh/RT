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

#include "rt.h"
#include "librt.h"
#include "color.h"
#include <math.h>

float
	pattern_checkers(float x, float y)
{
	float	pattern;

	if (x < 0)
		x = fabsf(x - 5);
	if (y < 0)
		y = fabsf(y - 5);
	pattern = (fmodf(x, 10) < 5) ^ (fmodf(y, 10) < 5);
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
