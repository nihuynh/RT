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

#include "rt.h"
#include "librt.h"
#include "ftmem.h"
#include <math.h>

void
	camera_pan(t_data *data, float agl)
{
	float	tmp;
	t_vec3	vi;

	agl *= M_PI / 180;
	vec3_new(&vi, 0, 0, -1);
	tmp = data->cam.dir.x;
	data->cam.dir.x = data->cam.dir.x * cos(agl) - data->cam.dir.z * sin(agl);
	data->cam.dir.z = tmp * sin(agl) + data->cam.dir.z * cos(agl);
	vec3_normalize(&data->cam.dir);
	mat3_rot(&data->matrix_camera[0], &data->matrix_camera[1], &vi, &data->cam.dir);
	data->sdl.isrender = 0;
}

void
	camera_pitch(t_data *data, float angle)
{
	t_vec3	vi;

	angle *= M_PI / 180;
	vec3_new(&vi, 0, 0, -1);
	data->cam.dir.y += (angle > 0) ? 0.1 : -0.1;
	vec3_normalize(&data->cam.dir);
	mat3_rot(&data->matrix_camera[0], &data->matrix_camera[1], &vi, &data->cam.dir);
	data->sdl.isrender = 0;
}

void
	camera_zoom(t_data *data, float value)
{
	float mag;

	mag = 1 / vec3_mag(&data->cam.dir);
	data->cam.pos.x += data->cam.dir.x * mag * value;
	data->cam.pos.y += data->cam.dir.y * mag * value;
	data->cam.pos.z += data->cam.dir.z * mag * value;
	data->sdl.isrender = 0;
}

void
	camera_height(t_data *data, float value)
{
	data->cam.pos.y += value;
	data->sdl.isrender = 0;
}

void
	camera_side(t_data *data, float value)
{
	t_vec3	side;
	t_vec3	up;

	vec3_new(&up, 0, 1, 0);
	vec3_cross(&data->cam.dir, &up, &side);
	vec3_normalize(&side);
	data->cam.pos.x += side.x * value;
	data->cam.pos.y += side.y * value;
	data->cam.pos.z += side.z * value;
	data->sdl.isrender = 0;
}
