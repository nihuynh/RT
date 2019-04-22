/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_normalize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 18:43:14 by nihuynh           #+#    #+#             */
/*   Updated: 2018/12/19 19:08:43 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "librt.h"

void		vec3_normalize(t_vec3 *v1)
{
	float k;

	if (!v1)
		return ;
	k = 1.0f / vec3_mag(*v1);
	v1->x *= k;
	v1->y *= k;
	v1->z *= k;
}

t_vec3		vec3_normalize_(t_vec3 v1)
{
	float k;

	k = 1.0f / vec3_mag(v1);
	v1.x *= k;
	v1.y *= k;
	v1.z *= k;
	return (v1);
}
