/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_sub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 03:29:41 by nihuynh           #+#    #+#             */
/*   Updated: 2018/12/04 03:34:12 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "libft.h"

void	color_sub(t_color *color, t_color *sub)
{
	color->r = (uint8_t)ft_clamp(color->r - sub->r, 0, 255);
	color->g = (uint8_t)ft_clamp(color->r - sub->g, 0, 255);
	color->b = (uint8_t)ft_clamp(color->r - sub->b, 0, 255);
}
