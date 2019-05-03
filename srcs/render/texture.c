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

#include <ftmath.h>
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

typedef struct tmp {
	unsigned char a, b, c;
} tmp;

t_color sample(t_texture *texture, float x, float y)
{
//	printf("x: %f  y:  %f\n", x, y);
	int x_ = (ft_clampf(x, 0, 1) * (texture->width - 1));
	int y_ = (ft_clampf(1-y, 0, 1) * (texture->height - 1));
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
