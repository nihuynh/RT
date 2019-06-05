/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_max.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 15:20:56 by sklepper          #+#    #+#             */
/*   Updated: 2019/06/05 03:54:24 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "color.h"

void	color_max(t_color *col1, t_color *col2)
{
	col1->r = fmaxf(col1->r, col2->r);
	col1->g = fmaxf(col1->g, col2->g);
	col1->b = fmaxf(col1->b, col2->b);
}
