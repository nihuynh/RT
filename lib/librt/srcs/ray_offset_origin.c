/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_offset_origin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdarchiv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 15:38:24 by tdarchiv          #+#    #+#             */
/*   Updated: 2019/04/15 15:38:26 by tdarchiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <librt.h>

void	ray_offset_origin(t_ray *ray, t_vec3 normal)
{
	float	offset_factor;

	if (vec3_dot(&ray->dir, &normal) > 0)
		offset_factor = SHADOW_BIAS;
	else
		offset_factor = -SHADOW_BIAS;
	vec3_scalar(&normal, offset_factor);
	vec3_add(&ray->origin, &ray->origin, &normal);
}
