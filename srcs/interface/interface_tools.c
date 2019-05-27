/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 10:55:25 by sklepper          #+#    #+#             */
/*   Updated: 2019/05/27 12:56:10 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"
#include "rtstruct.h"
#include "librt.h"

void	ui_sphere(void *app_v, void *res)
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

void	ui_plane(void *app_v, void *res)
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
	if (igInputFloat("X Limit", &tmp.size_x, 0, 0, "%g", 0))
		plane->size_x = tmp.size_x;
	if (igInputFloat("Y Limit", &tmp.size_y, 0, 0, "%g", 0))
		plane->size_y = tmp.size_y;
}

void	ui_cylinder(void *app_v, void *res)
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

void	ui_cone(void *app_v, void *res)
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

void			ui_csg(void *app_v, void *shape)
{
	t_btree *root;
	t_data	*app;

	app = app_v;
	root = shape;
	if (root->content_size == sizeof(t_obj))
	{
		object(app, root->content);
		return ;
	}
	node_type_list((t_csg_op*)root->content);
	if (igTreeNodeStr("Left"))
	{
		ui_csg(app, root->left);
		igTreePop();
	}
	if (igTreeNodeStr("Right"))
	{
		ui_csg((void*)app, (void*)root->right);
		igTreePop();
	}
}
