/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_clamp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 16:47:24 by tdarchiv          #+#    #+#             */
/*   Updated: 2019/04/24 15:42:28 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "color.h"

/*
** @brief	Clamp each color channel between min and max
**
** @param color
** @param min
** @param max
*/

void	color_clamp(t_color *color, float min, float max)
{
	color->r = fmaxf(min, fminf(color->r, max));
	color->g = fmaxf(min, fminf(color->g, max));
	color->b = fmaxf(min, fminf(color->b, max));
}
