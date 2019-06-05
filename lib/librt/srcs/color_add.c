/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_add.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 03:26:10 by nihuynh           #+#    #+#             */
/*   Updated: 2019/06/05 03:54:16 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "ftmath.h"

void	color_add(t_color *color, t_color add)
{
	color->r += add.r;
	color->g += add.g;
	color->b += add.b;
}

t_color	color_add_(t_color color, t_color add)
{
	color.r += add.r;
	color.g += add.g;
	color.b += add.b;
	return (color);
}
