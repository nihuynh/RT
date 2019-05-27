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
	t_vec3	orig2point;
	float	angle;

	cone = inter->obj->shape;
	vec3_sub(&orig2point, &inter->point, &cone->origin);
	angle = ((vec3_dot(&orig2point, &cone->n) < 0) * 180) - cone->theta;
	var = vec3_mag(orig2point) / cosf(angle * DEG_TO_RAD);
	pc.x = cone->origin.x + var * cone->n.x;
	pc.y = cone->origin.y + var * cone->n.y;
	pc.z = cone->origin.z + var * cone->n.z;
	vec3_sub(&inter->n, &inter->point, &pc);
	vec3_normalize(&inter->n);
	if (vec3_dot(&inter->n, &inter->ray.dir) > 0)
		vec3_scalar(&inter->n, -1);
}
