/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 14:08:37 by sklepper          #+#    #+#             */
/*   Updated: 2019/04/29 16:20:42 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "librt.h"
#include "color.h"
#include "math.h"

t_color
	texture_checkers(t_texture *tex, float x, float y)
{
	bool	pattern;

	(void)tex;
	if (x < 0)
		x = fabsf(x - 5);
	if (y < 0)
		y = fabsf(y - 5);
	pattern = (fmodf(x, 10) < 5) ^ (fmodf(y, 10) < 5);
	return (itocolor(pattern * 0xFFFFFF));
}

t_color
	texture_strips(t_texture *tex, float x, float y)
{
	float	pattern;
	float	angle;

	(void)tex;
	angle = 45 * DEG_TO_RAD;
	pattern = x * cosf(angle) - y * sinf(angle);
	if (pattern < 0)
		pattern -= 5;
	pattern = fabsf(fmodf(pattern, 10)) < 5;
	return (itocolor((bool)pattern * 0xFFFFFF));
}
