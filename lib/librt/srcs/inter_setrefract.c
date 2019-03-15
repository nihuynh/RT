/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_setrefract.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 16:26:41 by sklepper          #+#    #+#             */
/*   Updated: 2019/03/14 14:27:47 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "librt.h"

void	inter_setrefract(t_inter *inter, t_ray *res)
{
	float	rene;
	t_vec3	toby;

	inter_find(inter, &res->origin);
	rene = vec3_dot(&inter->ray.n, &inter->n);
	vec3_cpy(&toby, &inter->n);
	vec3_scalar(&toby, SHADOW_BIAS);
	(rene < 0) ? vec3_sub(&res->origin, &res->origin, &toby)
		: vec3_add(&res->origin, &res->origin, &toby);
	vec3_refract(inter, &res->n, 1.5);
}
