/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_apply_rotation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdarchiv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 18:09:06 by tdarchiv          #+#    #+#             */
/*   Updated: 2019/07/24 18:09:12 by tdarchiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "librt.h"
#include "interface.h"

void
	ui_apply_rotation(t_vec3 *x, t_vec3 *y, t_vec3 *z)
{
	static t_rotate	quat;
	t_matrix		mat;

	quat.axis = *y;
	igDragFloat("Rotation", &quat.deg, 1, -360, 360, "%g", 1);
	igSameLine(0, 10);
	if (igButton("Apply", (ImVec2){0, 0}) && fabsf(quat.deg) > 0.1f)
	{
		mat = mat_orbit(quat.axis, quat.deg);
		apply_matrix(x, &mat);
		apply_matrix(y, &mat);
		apply_matrix(z, &mat);
		vec3_normalize(y);
		vec3_normalize(x);
		vec3_normalize(z);
		quat.deg = 0;
	}
}
