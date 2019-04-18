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
	color->r -= sub->r;
	color->g -= sub->g;
	color->b -= sub->b;
}
