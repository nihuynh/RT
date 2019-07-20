/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_cube.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 14:09:43 by nihuynh           #+#    #+#             */
/*   Updated: 2019/06/24 21:09:58 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "librt.h"
#include "ftmath.h"
#include "ftio.h"
#include <math.h>

/*
** Returns a vector with only the major axis of the input vector
** Eg (0.5, -16, 3) -> (0, -1, 0)
*/

t_vec3	get_major_axis(t_vec3 v)
{
	float	largest_comp;
	t_vec3	normal;

	largest_comp = fmaxf(fabsf(v.x), fmaxf(fabsf(v.y), fabsf(v.z)));
	normal.x = (largest_comp == fabsf(v.x)) * copysignf(1, v.x);
	normal.y = (largest_comp == fabsf(v.y)) * copysignf(1, v.y);
	normal.z = (largest_comp == fabsf(v.z)) * copysignf(1, v.z);
	return (normal);
}

/*
** 1. Computes the vector from cube center to hitpoint
** 2. Transform into the cube local space with the cube matrix
** 3. Extract the major axis of the vector, this is the normal
** 4. Retransform it back to world space with the inverse of the cube matrix
** If the secondary point of intersection is behind the ray origin, we are
** inside the cube so we invert the normal
*/

void	normal_cube(t_inter *inter)
{
	t_cube		*cube;
	t_vec3		orig_to_hitpt;
	t_matrix	local_matrix;

	cube = inter->obj->shape;
	orig_to_hitpt = vec3_sub_(inter->point, cube->origin);
	local_matrix = mat_set_axes(cube->x, cube->n, cube->z);
	apply_matrix(&orig_to_hitpt, &local_matrix);
	inter->n = get_major_axis(orig_to_hitpt);
	mat_transpose(&local_matrix);
	apply_matrix(&inter->n, &local_matrix);
	if (inter->hit_pts.y < 0)
		vec3_scalar(&inter->n, -1);
}
