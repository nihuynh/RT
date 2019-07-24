/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_cube.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 21:11:42 by sklepper          #+#    #+#             */
/*   Updated: 2019/07/20 21:34:09 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "interface.h"
#include "config.h"
#include "librt.h"

void
	ui_cube(void *ap, void *res)
{
	t_cube			*cube;
	t_cube			tmp;

	(void)ap;
	cube = res;
	tmp = *cube;
	if (igInputFloat3("Origin (X Y Z)", &tmp.origin.x, "%g", 0))
		cube->origin = tmp.origin;
	if (igSliderFloat3("Normal (X Y Z)", &tmp.n.x, -1, 1, "%g", 1))
		cube->n = tmp.n;
	igSameLine(0, 10);
	if (igButton("Normalize", (ImVec2){0, 0}))
	{
		vec3_normalize(&cube->n);
		create_orthobasis_from_y_axis(cube->n, &cube->x, &cube->z);
	}
	ui_apply_rotation(&cube->x, &cube->n, &cube->z);
	if (igInputFloat("Size", &tmp.size, 0, 0, "%g", 0))
		cube->size = tmp.size;
}
