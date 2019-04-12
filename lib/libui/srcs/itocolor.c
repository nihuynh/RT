/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itocolor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 20:28:46 by sklepper          #+#    #+#             */
/*   Updated: 2019/04/12 16:54:22 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

void	itocolor(t_color *res, int color)
{
	res->r = (color & MASK_RED);
	res->g = ((color & MASK_GREEN) >> 8);
	res->b = ((color & MASK_BLUE) >> 16);
}
