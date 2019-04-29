/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_mult.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 03:24:03 by nihuynh           #+#    #+#             */
/*   Updated: 2019/04/24 15:42:32 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"

/*
** @brief	Multiply colors
**
**
** @param color
** @param mult
*/

void	color_mult(t_color *color, t_color *mult)
{
	color->r *= mult->r;
	color->g *= mult->g;
	color->b *= mult->b;
}

t_color	color_mult_(t_color color, t_color mult)
{
	color.r *= mult.r;
	color.g *= mult.g;
	color.b *= mult.b;
	return (color);
}
