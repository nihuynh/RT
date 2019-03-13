/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_find.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 15:55:45 by nihuynh           #+#    #+#             */
/*   Updated: 2018/12/19 19:18:08 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtstruct.h"

void	inter_find(t_inter *primary, t_pt3 *value)
{
	float dist;

	dist = primary->dist;
	value->x = primary->ray.origin.x + dist * primary->ray.n.x;
	value->y = primary->ray.origin.y + dist * primary->ray.n.y;
	value->z = primary->ray.origin.z + dist * primary->ray.n.z;
}
