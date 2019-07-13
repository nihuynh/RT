/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 10:55:25 by sklepper          #+#    #+#             */
/*   Updated: 2019/07/03 03:54:35 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"
#include "rtstruct.h"
#include "librt.h"
#include "parse.h"
#include "config.h"

void
	ui_sphere(void *ap, void *res)
{
	t_sphere *sphere;
	t_sphere tmp;

	sphere = res;
	tmp = *sphere;
	if (igInputFloat3("Origin (X Y Z)", &tmp.origin.x, "%g", 0))
		sphere->origin = tmp.origin;
	if (igInputFloat("Radius", &tmp.radius, 0, 0, "%g", 0))
		sphere->radius = tmp.radius;
	if (igSliderFloat3("Y axis (X Y Z)", &tmp.y.x, -1, 1, "%g", 1))
		sphere->y = tmp.y;
	igSameLine(0, 0);
	if (igButton("Normalize", (ImVec2) {0, 0}))
	{
		vec3_normalize(&sphere->y);
		create_orthobasis_from_y_axis(sphere->y, &sphere->x, &sphere->z);
	}
	if (igButton("Spawn axes", (ImVec2) {0, 0}))
	{
		new_axis_debug((t_data*)ap, sphere->origin, sphere->x, itocolor(RED));
		new_axis_debug((t_data*)ap, sphere->origin, sphere->y, itocolor(GREEN));
		new_axis_debug((t_data*)ap, sphere->origin, sphere->z, itocolor(BLUE));
		((t_data*)ap)->sdl->needs_render = true;
		((t_data*)ap)->sdl->partial_render = false;
	}
}

static inline void
	ui_plane_limit(t_plane *plane)
{
	t_plane		tmp;

	tmp = *plane;
	if (plane->type == 0 && igDragFloat2("Limit (X Y)",
			&tmp.size.x, 1, 0, 1000000, "%g", 1))
		plane->size = tmp.size;
	if (plane->type == 1 && igDragFloat("Limit",
			&tmp.size.x, 1, 0, 1000000, "%g", 1))
		plane->size.x = tmp.size.x;
	if (plane->type == 2 && igInputFloat2("P1", &tmp.p1.x, "%g", 0))
		plane->p1 = tmp.p1;
	if (plane->type == 2 && igInputFloat2("P2", &tmp.p2.x, "%g", 0))
		plane->p2 = tmp.p2;
	if (igRadioButtonBool("Rectangle", plane->type == 0))
		plane->type = 0;
	igSameLine(0, 10);
	if (igRadioButtonBool("Disk", plane->type == 1))
		plane->type = 1;
	igSameLine(0, 10);
	if (igRadioButtonBool("Triangle", plane->type == 2))
		plane->type = 2;
}

void
	ui_plane(void *app_v, void *res)
{
	t_plane		*plane;
	t_plane		tmp;

	(void)app_v;
	plane = res;
	tmp = *plane;
	if (igInputFloat3("Origin (X Y Z)", &tmp.origin.x, "%g", 0))
		plane->origin = tmp.origin;
	if (igSliderFloat3("Normal (X Y Z)", &tmp.n.x, -1, 1, "%g", 1))
		plane->n = tmp.n;
	igSameLine(0, 0);
	if (igButton("Normalize", (ImVec2){0, 0}))
	{
		vec3_normalize(&plane->n);
		create_orthobasis_from_y_axis(plane->n, &plane->x, &plane->y);
	}
	ui_plane_limit(plane);
}

void
	ui_cylinder(void *app_v, void *res)
{
	t_cylinder	*cylinder;
	t_cylinder	tmp;

	(void)app_v;
	cylinder = res;
	tmp = *cylinder;
	if (igInputFloat3("Origin (X Y Z)", &tmp.origin.x, "%g", 0))
		cylinder->origin = tmp.origin;
	if (igSliderFloat3("Normal (X Y Z)", &tmp.n.x, -1, 1, "%g", 1))
		cylinder->n = tmp.n;
	igSameLine(0, 0);
	if (igButton("Normalize", (ImVec2){0, 0}))
	{
		vec3_normalize(&cylinder->n);
		create_orthobasis_from_y_axis(cylinder->n, &cylinder->x, &cylinder->z);
	}
	if (igInputFloat("Radius", &tmp.radius, 0, 0, "%g", 0))
		cylinder->radius = tmp.radius;
	if (igInputFloat("Size", &tmp.size, 0, 0, "%g", 0))
		cylinder->size = tmp.size;
}

void
	ui_cone(void *app_v, void *res)
{
	t_cone	*cone;
	t_cone	tmp;

	(void)app_v;
	cone = res;
	tmp = *cone;
	if (igInputFloat3("Origin (X Y Z)", &tmp.origin.x, "%g", 0))
		cone->origin = tmp.origin;
	if (igSliderFloat3("Normal (X Y Z)", &tmp.n.x, -1, 1, "%g", 1))
		cone->n = tmp.n;
	igSameLine(0, 0);
	if (igButton("Normalize", (ImVec2){0, 0}))
	{
		vec3_normalize(&cone->n);
		create_orthobasis_from_y_axis(cone->n, &cone->x, &cone->z);
	}
	if (igInputFloat("Theta", &tmp.theta, 0, 0, "%g", 0))
		cone->theta = tmp.theta;
	if (igInputFloat("Size", &tmp.size, 0, 0, "%g", 0))
		cone->size = tmp.size;
}
