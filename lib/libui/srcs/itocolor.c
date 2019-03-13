/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itocolor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 20:28:46 by sklepper          #+#    #+#             */
/*   Updated: 2019/03/01 20:30:16 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

void	itocolor(t_color *res, int color)
{
	res->r = ((color & MASK_RED) >> 16);
	res->g = ((color & MASK_GREEN) >> 8);
	res->b = (color & MASK_BLUE);
}
