/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 14:08:37 by sklepper          #+#    #+#             */
/*   Updated: 2019/03/19 16:26:06 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math.h"
#include "libui.h"
#include "libft.h"

void	texture_checkers(t_color *color, float x, float y)
{
	float	pattern;

	if (x < 0)
		x = fabsf((float)(x - 5));
	if (y < 0)
		y = fabsf((float)(y - 5));
	pattern = (fmodf(x, 10) < 5) ^ (fmodf(y, 10) < 5);
	ft_bzero(color, sizeof(color));
	if (pattern)
		itocolor(color, 0xFFFFFF);
}

void	texture_strips(t_color *color, float x, float y)
{
	float	pattern;
	float	angle;
	(void)y;

	angle = 45 * M_PI / 180;
	pattern = x * cosf(angle) - y * sinf(angle);
	if (pattern < 0)
		pattern -= 5;
	pattern = fabsf(fmodf(pattern, 10)) < 5;
	ft_bzero(color, sizeof(color));
	if (pattern)
		itocolor(color, 0xFFFFFF);
}
