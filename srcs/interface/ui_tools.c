/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 10:55:25 by sklepper          #+#    #+#             */
/*   Updated: 2019/06/23 13:59:15 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"
#include "rtstruct.h"
#include "librt.h"

void
	ui_sphere(void *app_v, void *res)
{
	t_sphere	*sphere;
	t_sphere	tmp;

	(void)app_v;
	sphere = res;
	tmp = *sphere;
	if (igInputFloat3("Origin (X Y Z)", &tmp.origin.x, "%g", 0))
		sphere->origin = tmp.origin;
	if (igInputFloat("Radius", &tmp.radius, 0, 0, "%g", 0))
		sphere->radius = tmp.radius;
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
	if (igInputFloat("X Limit", &tmp.size.x, 0, 0, "%g", 0))
		plane->size.x = tmp.size.x;
	if (igInputFloat("Y Limit", &tmp.size.y, 0, 0, "%g", 0))
		plane->size.y = tmp.size.y;
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

void
	ui_cube(void *app_v, void *res)
{
	t_cube	*cube;
	t_cube	tmp;

	(void)app_v;
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
}

void
	ui_tore(void *app_v, void *res)
{
	t_tore	*tore;
	t_tore	tmp;

	(void)app_v;
	tore = res;
	tmp = *tore;
	if (igInputFloat3("Origin (X Y Z)", &tmp.origin.x, "%g", 0))
		tore->origin = tmp.origin;
	if (igSliderFloat3("Normal (X Y Z)", &tmp.n.x, -1, 1, "%g", 1))
		tore->n = tmp.n;
	if (igSliderFloat3("X (X Y Z)", &tmp.x.x, -1, 1, "%g", 1))
		tore->x = tmp.x;
	if (igSliderFloat3("Z (X Y Z)", &tmp.z.x, -1, 1, "%g", 1))
		tore->z = tmp.z;
	if (igButton("Normalize", (ImVec2){0, 0}))
	{
		vec3_normalize(&tore->n);
		vec3_normalize(&tore->x);
		vec3_normalize(&tore->z);
	}
	if (igInputFloat("Size", &tmp.size, 0, 0, "%g", 0))
		tore->size = tmp.size;
	if (igInputFloat("Radius", &tmp.radius, 0, 0, "%g", 0))
		tore->radius = tmp.radius;
}
