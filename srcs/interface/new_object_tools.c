/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_object_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 16:36:42 by sklepper          #+#    #+#             */
/*   Updated: 2019/05/07 19:55:16 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void
	sphere_new(void *res, char **greed, int i)
{
	t_sphere	*sphere;

	(void)greed;
	(void)i;
	sphere = res;
	sphere->origin = (t_pt3){0, 0, 0};
	sphere->radius = 10;
}

void
	plane_new(void *res, char **greed, int i)
{
	t_plane		*plane;

	(void)greed;
	(void)i;
	plane = res;
	plane->origin = (t_pt3){0, 0, 0};
	plane->n = (t_vec3){0, 0, 1};
	plane->size_x = 0;
	plane->size_y = 0;
	plane->x = (t_vec3){1, 0, 0};
	plane->y = (t_vec3){0, 1, 0};
}

void
	cylinder_new(void *res, char **greed, int i)
{
	t_cylinder	*cylinder;

	(void)greed;
	(void)i;
	cylinder = res;
	cylinder->origin = (t_pt3){0, 0, 0};
	cylinder->n = (t_vec3){0, 1, 0};
	cylinder->radius = 10;
	cylinder->size = 0;
}

void
	cone_new(void *res, char **greed, int i)
{
	t_cone	*cone;

	(void)greed;
	(void)i;
	cone = res;
	cone->origin = (t_pt3){0, 0, 0};
	cone->n = (t_vec3){0, 1, 0};
	cone->theta = 25;
	cone->size = 0;
}
