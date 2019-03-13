/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_cos.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 18:43:04 by nihuynh           #+#    #+#             */
/*   Updated: 2018/12/19 19:15:43 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "librt.h"
#include <math.h>

float	vec3_cos(t_vec3 *v1, t_vec3 *v2)
{
	float mag;

	if (!v1 || !v2)
		return (0);
	mag = sqrt(vec3_dot(v1, v1) + vec3_dot(v2, v2));
	return (vec3_dot(v1, v2) / mag);
}
