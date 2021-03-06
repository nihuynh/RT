/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_sub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 03:29:41 by nihuynh           #+#    #+#             */
/*   Updated: 2019/05/12 06:18:44 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "libft.h"

t_color	color_sub(t_color color, t_color sub)
{
	t_color res;

	res.r = color.r - sub.r;
	res.g = color.g - sub.g;
	res.b = color.b - sub.b;
	return (res);
}
