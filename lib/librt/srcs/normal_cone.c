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
	t_pt3	pi;
	t_pt3	pc;
	float	var;
	t_vec3	toby;

	cone = inter->obj->shape;
	inter_find(inter, &pi);
	vec3_sub(&toby, (t_vec3*)&pi, (t_vec3*)&cone->origin);
	var = vec3_mag(&toby);
	var /= (vec3_dot(&toby, &cone->n) > 0) ? cos(cone->theta * M_PI / 180.0)
		: cos((180 - cone->theta) * M_PI / 180.0);
	pc.x = cone->origin.x + var * cone->n.x;
	pc.y = cone->origin.y + var * cone->n.y;
	pc.z = cone->origin.z + var * cone->n.z;
	vec3_sub(&toby, (t_vec3*)&pi, (t_vec3*)&pc);
	vec3_normalize(&toby);
	vec3_cpy(&inter->n, &toby);
}
