/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colortoi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 23:51:14 by nihuynh           #+#    #+#             */
/*   Updated: 2019/04/13 00:03:04 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"

int	colortoi(t_color color)
{
	return ((color.r << SHIFT_RED)
		+ (color.g << SHIFT_GREEN)
		+ (color.b << SHIFT_BLUE));
}
