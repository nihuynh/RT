/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 14:41:32 by sklepper          #+#    #+#             */
/*   Updated: 2019/04/16 14:44:49 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtstruct.h"

void	cpy_pos(t_pt3 src, float dest[3])
{
	dest[0] = src.x;
	dest[1] = src.y;
	dest[2] = src.z;
}

void	cpy_pos_rev(float src[3], t_pt3 *dest)
{
	dest->x = src[0];
	dest->y = src[1];
	dest->z = src[2];
}
