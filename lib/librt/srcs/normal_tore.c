/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_tore.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 14:09:51 by nihuynh           #+#    #+#             */
/*   Updated: 2019/06/23 14:10:34 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "librt.h"

void	normal_tore(t_inter *inter)
{
	t_tore	*tore;
	t_vec3	insider;
	int		is_inside;

	tore = inter->obj->shape;
	vec3_sub(&insider, &tore->origin, &inter->ray.origin);
	is_inside = (vec3_mag(insider) < tore->radius) ? 1 : 0;
	inter->n.x = inter->point.x - tore->origin.x;
	inter->n.y = inter->point.y - tore->origin.y;
	inter->n.z = inter->point.z - tore->origin.z;
	if (is_inside || inter->hit_pts.y == inter->dist)
		vec3_scalar(&inter->n, -1);
	vec3_normalize(&inter->n);
}
