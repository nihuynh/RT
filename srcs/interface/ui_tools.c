/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 10:55:25 by sklepper          #+#    #+#             */
/*   Updated: 2019/06/26 23:01:11 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"
#include "rtstruct.h"
#include "librt.h"
#include "parse.h"

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
	if (plane->type == 0 && igDragFloat2("Limit (X Y)",
			&tmp.size.x, 1, 0, 1000000, "%g", 1))
		plane->size = tmp.size;
	if (plane->type > 0 && igDragFloat("Limit",
			&tmp.size.x, 1, 0, 1000000, "%g", 1))
		plane->size.x = tmp.size.x;
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
	{
		cube->origin = tmp.origin;
		set_min_max_corner(cube);
	}
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
		set_min_max_corner(cube);
	}
	if (igInputFloat("Size", &tmp.size, 0, 0, "%g", 0))
	{
		cube->size = tmp.size;
		set_min_max_corner(cube);
	}
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
