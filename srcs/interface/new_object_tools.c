/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_object_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 16:36:42 by sklepper          #+#    #+#             */
/*   Updated: 2019/07/18 16:17:29 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtstruct.h"
#include "librt.h"

void
	sphere_new(t_obj *obj, void *res)
{
	t_sphere	*sphere;

	sphere = res;
	sphere->origin = (t_pt3){0, 0, 0};
	sphere->radius = 10;
	sphere->x = (t_vec3){1, 0, 0};
	sphere->y = (t_vec3){0, 1, 0};
	sphere->z = (t_vec3){0, 0, 1};
	obj->pos = &sphere->origin;
	obj->x = &sphere->x;
	obj->n = &sphere->y;
	obj->z = &sphere->z;
}

void
	plane_new(t_obj *obj, void *res)
{
	t_plane		*plane;

	plane = res;
	plane->origin = (t_pt3){0, 0, 0};
	plane->n = (t_vec3){0, 0, 1};
	plane->size = (t_vec2){50, 50};
	plane->x = (t_vec3){1, 0, 0};
	plane->y = (t_vec3){0, 1, 0};
	obj->pos = &plane->origin;
	obj->x = &plane->x;
	obj->n = &plane->n;
	obj->z = &plane->y;
}

void
	cylinder_new(t_obj *obj, void *res)
{
	t_cylinder	*cylinder;

	cylinder = res;
	cylinder->origin = (t_pt3){0, 0, 0};
	cylinder->n = (t_vec3){0, 1, 0};
	cylinder->radius = 10;
	cylinder->size = 0;
	obj->pos = &cylinder->origin;
	obj->x = &cylinder->x;
	obj->n = &cylinder->n;
	obj->z = &cylinder->z;
}

void
	cone_new(t_obj *obj, void *res)
{
	t_cone	*cone;

	cone = res;
	cone->origin = (t_pt3){0, 0, 0};
	cone->n = (t_vec3){0, 1, 0};
	cone->theta = 25;
	cone->size = 0;
	obj->pos = &cone->origin;
	obj->x = &cone->x;
	obj->n = &cone->n;
	obj->z = &cone->z;
}

void
	cube_new(t_obj *obj, void *res)
{
	t_cube	*cube;

	cube = res;
	cube->origin = (t_pt3){0, 0, 0};
	cube->n = (t_vec3){0, 1, 0};
	cube->x = (t_vec3){1, 0, 0};
	cube->z = (t_vec3){0, 0, 1};
	cube->size = 10;
	obj->pos = &cube->origin;
	obj->x = &cube->x;
	obj->n = &cube->n;
	obj->z = &cube->z;
}
