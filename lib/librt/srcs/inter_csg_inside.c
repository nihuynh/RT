/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_csg_inside.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 19:52:48 by sklepper          #+#    #+#             */
/*   Updated: 2019/07/17 20:53:13 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "librt.h"
#include "csg.h"
#include "libft.h"
#include <math.h>

void
	inter_find_spe(t_inter *primary, t_pt3 *value)
{
	float dist;

	dist = primary->hit_pts.x;
	value->x = primary->ray.origin.x + dist * primary->ray.dir.x;
	value->y = primary->ray.origin.y + dist * primary->ray.dir.y;
	value->z = primary->ray.origin.z + dist * primary->ray.dir.z;
}

bool
	is_inside_cone(t_inter *inter)
{
	t_cone	*cone;
	t_pt3	pc;
	float	var[2];
	t_vec3	orig2point;
	t_vec3	vec;

	vec3_sub(&vec, &inter->point, &inter->ray.origin);
	vec3_normalize(&vec);
	cone = inter->obj->shape;
	inter_find_spe(inter, &inter->point);
	orig2point = vec3_sub_(inter->point, cone->origin);
	var[0] = ((vec3_dot(&orig2point, &cone->n) < 0) * 180) - cone->theta;
	var[1] = vec3_mag(orig2point) / cosf(var[0] * DEG_TO_RAD);
	pc.x = cone->origin.x + var[1] * cone->n.x;
	pc.y = cone->origin.y + var[1] * cone->n.y;
	pc.z = cone->origin.z + var[1] * cone->n.z;
	vec3_sub(&inter->n, &inter->point, &pc);
	vec3_normalize(&inter->n);
	return (vec3_dot(&inter->n, &vec) > 0);
}
