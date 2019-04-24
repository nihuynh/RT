/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_add.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 03:26:10 by nihuynh           #+#    #+#             */
/*   Updated: 2019/04/24 15:42:24 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "ftmath.h"

/*
** @brief	Add color & clamp it between 0-255
**
** @param color
** @param add
*/

void	color_add(t_color *color, t_color *add)
{
	color->r += add->r;
	color->g += add->g;
	color->b += add->b;
}
