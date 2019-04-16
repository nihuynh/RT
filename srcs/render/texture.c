/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 14:08:37 by sklepper          #+#    #+#             */
/*   Updated: 2019/04/08 21:14:38 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "librt.h"
#include "color.h"
#include "math.h"
#include "libft.h"

void	texture_checkers(t_color *color, float x, float y)
{
	float	pattern;

	if (x < 0)
		x = fabsf(x - 5);
	if (y < 0)
		y = fabsf(y - 5);
	pattern = (fmodf(x, 10) < 5) ^ (fmodf(y, 10) < 5);
	ft_bzero(color, sizeof(color));
	if (pattern)
		*color = itocolor(0xFFFFFF);
}

void	texture_strips(t_color *color, float x, float y)
{
	float	pattern;
	float	angle;

	angle = 45 * DEG_TO_RAD;
	pattern = x * cosf(angle) - y * sinf(angle);
	if (pattern < 0)
		pattern -= 5;
	pattern = fabsf(fmodf(pattern, 10)) < 5;
	ft_bzero(color, sizeof(color));
	if (pattern)
		*color = itocolor(0xFFFFFF);
}
