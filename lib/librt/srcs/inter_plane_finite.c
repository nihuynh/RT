/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_plane_finite.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 22:23:42 by sklepper          #+#    #+#             */
/*   Updated: 2019/06/27 00:40:23 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "librt.h"
#include <math.h>

static inline bool
	inter_finite_rectangle(t_inter *data, t_plane *plane, float dist)
{
	t_pt3	inter_pt;
	t_vec3	orig_to_inter;
	float	scale_x;
	float	scale_y;

	inter_pt.x = data->ray.origin.x + dist * data->ray.dir.x;
	inter_pt.y = data->ray.origin.y + dist * data->ray.dir.y;
	inter_pt.z = data->ray.origin.z + dist * data->ray.dir.z;
	vec3_sub(&orig_to_inter, &inter_pt, &plane->origin);
	scale_x = vec3_dot(&orig_to_inter, &plane->x) / vec3_dot(&plane->x, &plane->x);
	if (plane->size.x && fabsf(scale_x) > plane->size.x)
		return (0);
	scale_y = vec3_dot(&orig_to_inter, &plane->y) / vec3_dot(&plane->y, &plane->y);
	if (plane->size.y && fabsf(scale_y) > plane->size.y)
		return (0);
	return (1);
}

static inline bool
	inter_finite_disk(t_inter *data, t_plane *plane, float dist)
{
	t_pt3	inter_pt;
	t_vec3	orig_to_inter;
	float	scale;

	inter_pt.x = data->ray.origin.x + dist * data->ray.dir.x;
	inter_pt.y = data->ray.origin.y + dist * data->ray.dir.y;
	inter_pt.z = data->ray.origin.z + dist * data->ray.dir.z;
	vec3_sub(&orig_to_inter, &inter_pt, &plane->origin);
	scale = vec3_mag(orig_to_inter);
	if (fabsf(scale) > plane->size.x)
		return (0);
	return (1);
}

static inline float
	sign(t_vec2 p1, t_vec2 p2, t_vec2 p3)
{
	return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
}

static inline bool
	inter_finite_triangle(t_inter *data, t_plane *plane, float dist)
{
	t_vec3	d;
	t_pt3	inter_pt;
	t_vec2	pt;
	t_vec3	orig_to_inter;

	inter_pt.x = data->ray.origin.x + dist * data->ray.dir.x;
	inter_pt.y = data->ray.origin.y + dist * data->ray.dir.y;
	inter_pt.z = data->ray.origin.z + dist * data->ray.dir.z;
	vec3_sub(&orig_to_inter, &inter_pt, &plane->origin);
	pt.x = vec3_dot(&orig_to_inter, &plane->x) / vec3_dot(&plane->x, &plane->x);
	pt.y = vec3_dot(&orig_to_inter, &plane->y) / vec3_dot(&plane->y, &plane->y);
	d.x = sign(pt, (t_vec2){0, 0}, plane->p1);
	d.y = sign(pt, plane->p1, plane->p2);
	d.z = sign(pt, plane->p2, (t_vec2){0, 0});
	return !(((d.x < 0) || (d.y < 0) || (d.z < 0))
		&& ((d.x > 0) || (d.y > 0) || (d.z > 0)));
}
bool
	inter_plane_finite(t_inter *data, t_plane *plane, float dist)
{
	if (plane->type == 0)
		return (inter_finite_rectangle(data, plane, dist));
	else if (plane->type == 1)
		return (inter_finite_disk(data, plane, dist));
	else if (plane->type == 2)
		return (inter_finite_triangle(data, plane, dist));
	return (1);
}
