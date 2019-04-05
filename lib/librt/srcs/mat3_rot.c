/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat3_rot.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 04:51:01 by nihuynh           #+#    #+#             */
/*   Updated: 2019/03/18 15:32:46 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "librt.h"
#include "ftmath.h"
#include "ftmem.h"

static inline void
	mat_unitaire(t_matrix *mat)
{
	mat->m[0][0] = 1;
	mat->m[0][1] = 0;
	mat->m[0][2] = 0;
	mat->m[1][0] = 0;
	mat->m[1][1] = 1;
	mat->m[1][2] = 0;
	mat->m[2][0] = 0;
	mat->m[2][1] = 0;
	mat->m[2][2] = 1;
}

static void
	set_x_rotation(t_matrix *m, float angle)
{
	m->m[1][1] = cosf(angle);
	m->m[2][1] = -sinf(angle);
	m->m[1][2] = sinf(angle);
	m->m[2][2] = cosf(angle);
}

static void
	set_y_rotation(t_matrix *m, float angle)
{
	m->m[0][0] = cosf(angle);
	m->m[2][0] = sinf(angle);
	m->m[0][2] = -sinf(angle);
	m->m[2][2] = cosf(angle);
}

t_matrix
	set_rotation(float x_angle, float y_angle)
{
	t_matrix x_rotation;
	t_matrix y_rotation;

	mat_unitaire(&x_rotation);
	mat_unitaire(&y_rotation);
	set_x_rotation(&x_rotation, x_angle);
	set_y_rotation(&y_rotation, y_angle);
	return (matrix_mult(&y_rotation, &x_rotation));
}

t_matrix
	create_rotation_from_direction(t_vec3 direction)
{
	float x_angle;
	float y_angle;

	vec3_cartesian_to_spherical(direction, &y_angle, &x_angle);
	x_angle = x_angle - (M_PI_F / 2);
	y_angle = -y_angle - M_PI_F;
	return (set_rotation(x_angle, y_angle));
}
