/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_cone.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 01:01:47 by nihuynh           #+#    #+#             */
/*   Updated: 2018/12/19 19:18:28 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "librt.h"
#include <math.h>

void	normal_cone(t_inter *inter)
{
	t_cone	*cone;
	t_pt3	pc;
	float	var;
	t_vec3	normal;

	cone = inter->obj->shape;
	vec3_sub(&normal, &inter->point, &cone->origin);
	var = vec3_mag(normal);
	var /= (vec3_dot(&normal, &cone->n) > 0) ? cosf(cone->theta * DEG_TO_RAD)
		: cosf((180 - cone->theta) * DEG_TO_RAD);
	pc.x = cone->origin.x + var * cone->n.x;
	pc.y = cone->origin.y + var * cone->n.y;
	pc.z = cone->origin.z + var * cone->n.z;
	vec3_sub(&normal, &inter->point, &pc);
	vec3_normalize(&normal);
	if (vec3_dot(&normal, &inter->ray.dir) > 0)
		vec3_scalar(&normal, -1);
	vec3_cpy(&inter->n, &normal);
}
