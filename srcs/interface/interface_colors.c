/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_colors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 20:44:11 by sklepper          #+#    #+#             */
/*   Updated: 2019/04/12 21:10:01 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"

void	icolortogui(int src, float dest[3])
{
	dest[0] = (src & MASK_RED);
	dest[1] = ((src & MASK_GREEN) >> 8);
	dest[2] = ((src & MASK_BLUE) >> 16);
}

void	guicolortoi(float src[3], int *dest)
{
	int tmp[3];

	tmp[0] = src[0];
	tmp[1] = src[1];
	tmp[2] = src[2];
	*dest = tmp[0] + (tmp[1] << 8) + (tmp[2] << 16);
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
