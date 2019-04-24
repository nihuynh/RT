/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_scalar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 03:28:16 by nihuynh           #+#    #+#             */
/*   Updated: 2019/04/24 15:42:44 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "ftmath.h"

/*
** @brief Scale color by k then clamp it
**
** @param color
** @param k
*/

void	color_scalar(t_color *color, float k)
{
	color->r *= k;
	color->g *= k;
	color->b *= k;
}

t_color	color_scalar_(t_color color, float k)
{
	color.r *= k;
	color.g *= k;
	color.b *= k;
	return (color);
}
