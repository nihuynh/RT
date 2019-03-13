/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_find.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 16:12:10 by nihuynh           #+#    #+#             */
/*   Updated: 2018/12/19 19:14:00 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtstruct.h"

void	vec3_find(t_pt3 *origin, t_pt3 *dest, t_vec3 *value)
{
	if (!origin || !dest || !value)
		return ;
	value->x = dest->x - origin->x;
	value->y = dest->y - origin->y;
	value->z = dest->z - origin->z;
}
