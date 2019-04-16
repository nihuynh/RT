/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_max.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 15:20:56 by sklepper          #+#    #+#             */
/*   Updated: 2019/03/01 20:32:06 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "ftmath.h"

/**
** @brief	Return the max color in RGB between 2 t_color
**
** @param col1
** @param col2
*/

void	color_max(t_color *col1, t_color *col2)
{
	col1->r = ft_max(col1->r, col2->r);
	col1->g = ft_max(col1->g, col2->g);
	col1->b = ft_max(col1->b, col2->b);
}
