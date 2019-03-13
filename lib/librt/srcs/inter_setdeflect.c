/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_setdeflect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 14:26:16 by sklepper          #+#    #+#             */
/*   Updated: 2019/03/05 14:26:41 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "librt.h"

void	inter_setdeflect(t_inter *inter, t_ray *res)
{
	float	rene;
	t_vec3	toby;

	inter_find(inter, &res->origin);
	rene = vec3_dot(&inter->ray.n, &inter->n);
	vec3_cpy(&toby, &inter->n);
	vec3_scalar(&toby, SHADOW_BIAS);
	(rene > 0) ? vec3_sub((t_vec3*)&res->origin, (t_vec3*)&res->origin, &toby)
		: vec3_add((t_vec3*)&res->origin, (t_vec3*)&res->origin, &toby);
	vec3_deflect(inter, res);
}
