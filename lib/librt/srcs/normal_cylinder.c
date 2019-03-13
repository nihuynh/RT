/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_cylinder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 15:45:24 by nihuynh           #+#    #+#             */
/*   Updated: 2018/12/19 19:11:20 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "librt.h"

void	normal_cylinder(t_inter *inter)
{
	t_cylinder	*cylinder;
	t_pt3		pi;
	t_pt3		pc;
	float		var;
	t_vec3		toby;

	cylinder = inter->obj->shape;
	inter_find(inter, &pi);
	vec3_sub(&toby, (t_vec3*)&pi, (t_vec3*)&cylinder->origin);
	var = vec3_dot(&cylinder->n, &toby);
	pc.x = cylinder->origin.x + var * cylinder->n.x;
	pc.y = cylinder->origin.y + var * cylinder->n.y;
	pc.z = cylinder->origin.z + var * cylinder->n.z;
	vec3_sub(&toby, (t_vec3*)&pi, (t_vec3*)&pc);
	vec3_normalize(&toby);
	vec3_cpy(&inter->n, &toby);
}
