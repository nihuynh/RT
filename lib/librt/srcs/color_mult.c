/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_mult.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 03:24:03 by nihuynh           #+#    #+#             */
/*   Updated: 2019/06/05 03:54:43 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"

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
