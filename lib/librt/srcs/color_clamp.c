/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_clamp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 16:47:24 by tdarchiv          #+#    #+#             */
/*   Updated: 2019/06/05 03:54:30 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "color.h"

void	color_clamp(t_color *color, float min, float max)
{
	color->r = fmaxf(min, fminf(color->r, max));
	color->g = fmaxf(min, fminf(color->g, max));
	color->b = fmaxf(min, fminf(color->b, max));
}
