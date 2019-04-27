/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_toolbox.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 15:51:11 by sklepper          #+#    #+#             */
/*   Updated: 2019/04/26 16:05:46 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

bool	bool_color(t_color color)
{
	if (color.r > 0 || color.g > 0 || color.b > 0)
		return (true);
	return (false);
}
