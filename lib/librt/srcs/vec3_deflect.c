/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_deflect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 15:31:37 by sklepper          #+#    #+#             */
/*   Updated: 2019/03/01 21:29:47 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "librt.h"

void		vec3_deflect(t_inter *inter, t_ray *res)
{
	t_vec3	tmp;
	float	dot;

	dot = vec3_dot(&inter->n, &inter->ray.n);
	vec3_cpy(&tmp, &inter->n);
	vec3_scalar(&tmp, 2 * dot);
	vec3_sub(&res->n, &inter->ray.n, &tmp);
	vec3_normalize(&res->n);
}
