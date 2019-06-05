/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_scalar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 03:28:16 by nihuynh           #+#    #+#             */
/*   Updated: 2019/06/05 03:54:37 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "ftmath.h"

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
