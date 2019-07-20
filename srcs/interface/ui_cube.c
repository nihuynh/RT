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

static inline void
	ui_cube_extend(void *ap, t_cube *cube)
{
	t_data *app;

	app = ap;
	new_axis_debug(app, cube->origin, cube->x, itocolor(RED));
	new_axis_debug(app, cube->origin, cube->n, itocolor(GREEN));
	new_axis_debug(app, cube->origin, cube->z, itocolor(BLUE));
	app->sdl->needs_render = true;
	app->sdl->partial_render = false;
}

void
	ui_cube(void *ap, void *res)
{
	t_cube	*cube;
	t_cube	tmp;

	cube = res;
	tmp = *cube;
	if (igInputFloat3("Origin (X Y Z)", &tmp.origin.x, "%g", 0))
		cube->origin = tmp.origin;
	if (igSliderFloat3("Normal (X Y Z)", &tmp.n.x, -1, 1, "%g", 1))
		cube->n = tmp.n;
	if (igSliderFloat3("X (X Y Z)", &tmp.x.x, -1, 1, "%g", 1))
		cube->x = tmp.x;
	if (igSliderFloat3("Z (X Y Z)", &tmp.z.x, -1, 1, "%g", 1))
		cube->z = tmp.z;
	if (igButton("Normalize", (ImVec2){0, 0}))
	{
		vec3_normalize(&cube->n);
		vec3_normalize(&cube->x);
		vec3_normalize(&cube->z);
	}
	if (igInputFloat("Size", &tmp.size, 0, 0, "%g", 0))
		cube->size = tmp.size;
	if (igButton("Spawn axes", (ImVec2) {0, 0}))
		ui_cube_extend(ap, cube);
}
