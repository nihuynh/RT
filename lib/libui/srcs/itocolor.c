/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itocolor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 20:28:46 by sklepper          #+#    #+#             */
/*   Updated: 2019/04/13 00:32:58 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

void	itocolor(t_color *res, int color)
{
	res->r = ((color & MASK_RED) >> 16);
	res->g = ((color & MASK_GREEN) >> 8);
	res->b = (color & MASK_BLUE);
}
