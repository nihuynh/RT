/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_colors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 20:44:11 by sklepper          #+#    #+#             */
/*   Updated: 2019/04/16 14:05:41 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"

void	icolortogui(int src, float dest[3])
{
	t_color color;

	color = itocolor(src);
	dest[0] = color.r / 255.f;
	dest[1] = color.g / 255.f;
	dest[2] = color.b / 255.f;
}

void	guicolortoi(float src[3], int *dest)
{
	t_color color;

	color.r = src[0] * 255;
	color.g = src[1] * 255;
	color.b = src[2] * 255;
	*dest = colortoi(color);
}

void	colortogui(t_color src, float dest[3])
{
	dest[0] = src.r;
	dest[1] = src.g;
	dest[2] = src.b;
}

void	guitocolor(float src[3], t_color *dest)
{
	dest->r = src[0];
	dest->g = src[1];
	dest->b = src[2];
}
