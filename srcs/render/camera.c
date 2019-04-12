/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 15:30:35 by nihuynh           #+#    #+#             */
/*   Updated: 2019/03/18 16:18:33 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "rtstruct.h"
#include "librt.h"
#include "rt.h"

static t_vec3
	get_delta_vector(t_cam *cam, t_vec3 forward, t_vec3 upward, t_vec3 strafe)
{
	t_vec3	delta;

	delta = (t_vec3){0, 0, 0};
	if (cam->move_forward)
		vec3_sub(&delta, &delta, &forward);
	if (cam->move_backward)
		vec3_add(&delta, &delta, &forward);
	if (cam->strafe_right)
		vec3_add(&delta, &delta, &strafe);
	if (cam->strafe_left)
		vec3_sub(&delta, &delta, &strafe);
	if (cam->move_upward)
		vec3_add(&delta, &delta, &upward);
	if (cam->move_downward)
		vec3_sub(&delta, &delta, &upward);
	return (delta);
}

static bool
	update_angles(t_cam *cam)
{
	bool has_changed;

	has_changed = false;
	if (cam->rotate_right && (has_changed = 1))
		cam->y_angle += A_STEP;
	if (cam->rotate_left && (has_changed = 1))
		cam->y_angle += -A_STEP;
	if (cam->rotate_up && (has_changed = 1))
		cam->x_angle += -A_STEP;
	if (cam->rotate_down && (has_changed = 1))
		cam->x_angle += A_STEP;
	return (has_changed);
}

void
	update_camera(t_cam *cam, bool *needs_render)
{
	t_vec3	forward;
	t_vec3	upward;
	t_vec3	strafe;
	t_vec3	delta;

	if (update_angles(cam))
		*needs_render = true;
	cam->rotation = set_rotation(cam->x_angle, cam->y_angle);
	strafe = get_column(cam->rotation, 0);
	upward = get_column(cam->rotation, 1);
	forward = get_column(cam->rotation, 2);
	delta = get_delta_vector(cam, forward, upward, strafe);
	vec3_scalar(&delta, T_STEP);
	if (delta.x != 0 || delta.y != 0 || delta.z != 0)
		*needs_render = true;
	vec3_add(&cam->pos, &cam->pos, &delta);
}

void
	set_direction(t_cam *cam, t_vec3 direction)
{
	float azimuth;
	float polar;

	vec3_cartesian_to_spherical(direction, &azimuth, &polar);
	cam->x_angle = polar - (M_PI_F / 2);
	cam->y_angle = -azimuth - M_PI_F;
	cam->rotation = set_rotation(cam->x_angle, cam->y_angle);
}
