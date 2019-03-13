/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_add.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 03:26:10 by nihuynh           #+#    #+#             */
/*   Updated: 2019/03/01 20:31:55 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "ftmath.h"

/**
** @brief	Add color & clamp it between 0-255
**
** @param color
** @param add
*/

void	color_add(t_color *color, t_color *add)
{
	color->r = (uint8_t)ft_clamp(color->r + add->r, 0, 255);
	color->g = (uint8_t)ft_clamp(color->g + add->g, 0, 255);
	color->b = (uint8_t)ft_clamp(color->b + add->b, 0, 255);
}
