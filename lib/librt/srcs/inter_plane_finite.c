/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_plane_finite.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 22:23:42 by sklepper          #+#    #+#             */
/*   Updated: 2019/06/26 22:37:18 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "librt.h"
#include <math.h>

static inline bool
	inter_finite_rectangle(t_inter *data, t_plane *plan, float dist)
{
	t_pt3	inter_pt;
	t_vec3	orig_to_inter;
	float	scale_x;
	float	scale_y;

	inter_pt.x = data->ray.origin.x + dist * data->ray.dir.x;
	inter_pt.y = data->ray.origin.y + dist * data->ray.dir.y;
	inter_pt.z = data->ray.origin.z + dist * data->ray.dir.z;
	vec3_sub(&orig_to_inter, &inter_pt, &plan->origin);
	scale_x = vec3_dot(&orig_to_inter, &plan->x) / vec3_dot(&plan->x, &plan->x);
	if (plan->size.x && fabsf(scale_x) > plan->size.x)
		return (0);
	scale_y = vec3_dot(&orig_to_inter, &plan->y) / vec3_dot(&plan->y, &plan->y);
	if (plan->size.y && fabsf(scale_y) > plan->size.y)
		return (0);
	return (1);
}

static inline bool
	inter_finite_disk(t_inter *data, t_plane *plan, float dist)
{
	t_pt3	inter_pt;
	t_vec3	orig_to_inter;
	float	scale;

	inter_pt.x = data->ray.origin.x + dist * data->ray.dir.x;
	inter_pt.y = data->ray.origin.y + dist * data->ray.dir.y;
	inter_pt.z = data->ray.origin.z + dist * data->ray.dir.z;
	vec3_sub(&orig_to_inter, &inter_pt, &plan->origin);
	scale = vec3_mag(orig_to_inter);
	if (fabsf(scale) > plan->size.x)
		return (0);
	return (1);
}

bool
	inter_plane_finite(t_inter *data, t_plane *plane, float dist)
{
	if (plane->type == 0)
		return (inter_finite_rectangle(data, plane, dist));
	else if (plane->type == 1)
		return (inter_finite_disk(data, plane, dist));
	// else if (plane->type == 2)
	// 	return (inter_finite_triangle(data, plane, dist))
	return (1);
}
