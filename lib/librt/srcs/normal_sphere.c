/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 00:20:07 by nihuynh           #+#    #+#             */
/*   Updated: 2018/12/20 03:42:41 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "librt.h"

void	normal_sphere(t_inter *inter)
{
	t_sphere	*sphere;
	t_pt3		pt;
	t_vec3		insider;
	int			is_inside;

	sphere = inter->obj->shape;
	vec3_sub(&insider, (t_vec3*)&sphere->origin, (t_vec3*)&inter->ray.origin);
	is_inside = (vec3_mag(&insider) < sphere->radius) ? 1 : 0;
	inter_find(inter, &pt);
	inter->n.x = pt.x - sphere->origin.x;
	inter->n.y = pt.y - sphere->origin.y;
	inter->n.z = pt.z - sphere->origin.z;
	if (is_inside)
		vec3_scalar(&inter->n, -1);
	vec3_normalize(&inter->n);
}
