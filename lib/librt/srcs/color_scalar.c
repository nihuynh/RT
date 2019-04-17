/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_scalar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 03:28:16 by nihuynh           #+#    #+#             */
/*   Updated: 2019/03/01 20:35:20 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "ftmath.h"

/**
** @brief Scale color by k then clamp it
**
** @param color
** @param k
*/

void	color_scalar(t_color *color, float k)
{
	color->r = color->r * k;
	color->g = color->g * k;
	color->b = color->b * k;
}