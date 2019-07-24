/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_normalize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 18:43:14 by nihuynh           #+#    #+#             */
/*   Updated: 2019/07/21 18:03:24 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "librt.h"

void		vec3_normalize(t_vec3 *v1)
{
	float k;

	if (!v1)
		return ;
	k = vec3_mag(*v1);
	if (k == 0)
		return ;
	k = 1.0f / k;
	v1->x *= k;
	v1->y *= k;
	v1->z *= k;
}

t_vec3		vec3_normalize_(t_vec3 v1)
{
	float k;

	k = vec3_mag(v1);
	if (k == 0)
		return (v1);
	k = 1.0f / k;
	v1.x *= k;
	v1.y *= k;
	v1.z *= k;
	return (v1);
}
