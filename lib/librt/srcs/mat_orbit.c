/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_orbit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 21:08:03 by sklepper          #+#    #+#             */
/*   Updated: 2019/06/12 00:57:41 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "librt.h"
#include "ftmath.h"
#include "ftmem.h"

// q0 = cos(r/2),  q1 = sin(r/2) a,  q2 = sin(r/2) b,  q3 = sin(r/2) c

// and construct from these values the rotation matrix:

//      (q0² + q1² - q2² - q3²)      2(q1q2 - q0q3)          2(q1q3 + q0q2)

// Q  =      2(q2q1 + q0q3)     (q0² - q1² + q2² - q3²)      2(q2q3 - q0q1)

//           2(q3q1 - q0q2)          2(q3q2 + q0q1)     (q0² - q1² - q2² + q3²)


t_matrix	mat_orbit(t_vec3 axis, float deg)
{
	t_matrix mat;
	float	q[4];

	deg *= M_PI / 180;
	q[0] = cosf(deg / 2);
	q[1] = sinf(deg / 2) * axis.x;
	q[2] = sinf(deg / 2) * axis.y;
	q[3] = sinf(deg / 2) * axis.z;
	mat.m[0][0] = q[0] * q[0] + q[1] * q[1] - q[2] * q[2] - q[3] * q[3];
	mat.m[0][1] = 2 * (q[1] * q[2] - q[0] * q[3]);
	mat.m[0][2] = 2 * (q[1] * q[3] + q[0] * q[2]);

	mat.m[1][0] = 2 * (q[2] * q[1] + q[0] * q[3]);
	mat.m[1][1] = q[0] * q[0] - q[1] * q[1] + q[2] * q[2] - q[3] * q[3];
	mat.m[1][2] = 2 * (q[2] * q[3] - q[0] * q[1]);

	mat.m[2][0] = 2 * (q[3] * q[1] - q[0] * q[2]);
	mat.m[2][1] = 2 * (q[3] * q[2] + q[0] * q[1]);
	mat.m[2][2] = q[0] * q[0] - q[1] * q[1] - q[2] * q[2] + q[3] * q[3];
	return (mat);
}


	// t_matrix mat;

	// deg *= M_PI / 180;
	// mat.m[0][0] = cosf(deg) + axis.x * axis.x *(1 - cosf(deg));
	// mat.m[0][1] = axis.x * axis.y * (1 - cosf(deg)) - axis.z * sinf(deg);
	// mat.m[0][2] = axis.x * axis.z * (1 - cosf(deg)) - axis.y * sinf(deg);
	// mat.m[1][0] = axis.y * axis.x * (1 - cosf(deg)) + axis.z * sinf(deg);
	// mat.m[1][1] = cosf(deg) + axis.y * axis.y * (1 - cosf(deg));
	// mat.m[1][2] = axis.y * axis.z * (1 - cosf(deg)) - axis.x * sinf(deg);
	// mat.m[2][0] = axis.z * axis.x * (1 - cosf(deg)) - axis.y * sinf(deg);
	// mat.m[2][1] = axis.z * axis.y * (1 - cosf(deg)) + axis.x * sinf(deg);
	// mat.m[2][2] = cosf(deg) + axis.z * axis.z * (1 - cosf(deg));
	// return (mat);
