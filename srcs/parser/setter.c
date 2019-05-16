/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 02:44:31 by nihuynh           #+#    #+#             */
/*   Updated: 2019/03/19 15:59:05 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "parse.h"

void
	sphere_set(void *sphere, char **greed, int i)
{
	t_sphere	*psphere;

	if (sphere == NULL)
		ft_error_wmsg(ERR_PARSE_SET_SP, i, greed[i]);
	psphere = sphere;
	parse_vector(&psphere->origin, greed, ++i, "origin(");
	parse_fval(&psphere->radius, greed, ++i, "radius(");
}

void
	plane_set(void *plane, char **greed, int i)
{
	t_plane		*pplane;

	if (plane == NULL)
		ft_error_wmsg(ERR_PARSE_SET_PL, i, greed[i]);
	pplane = plane;
	parse_vector(&pplane->origin, greed, ++i, "origin(");
	parse_vector(&pplane->n, greed, ++i, "normal(");
	parse_limit(&pplane->size_x, &pplane->size_y, greed, ++i);
	vec3_normalize(&pplane->n);
	create_orthobasis_from_y_axis(pplane->n, &pplane->x, &pplane->y);
}

void
	cylinder_set(void *cylinder, char **greed, int i)
{
	t_cylinder	*pcylinder;

	if (cylinder == NULL)
		ft_error_wmsg(ERR_PARSE_SET_CY, i, greed[i]);
	pcylinder = cylinder;
	parse_vector(&pcylinder->origin, greed, ++i, "origin(");
	parse_vector(&pcylinder->n, greed, ++i, "normal(");
	vec3_normalize(&pcylinder->n);
	create_orthobasis_from_y_axis(pcylinder->n, &pcylinder->x, &pcylinder->z);
	parse_fval(&pcylinder->radius, greed, ++i, "radius(");
	parse_fval(&pcylinder->size, greed, ++i, "size(");
}

void
	cone_set(void *cone, char **greed, int i)
{
	t_cone		*pcone;

	if (cone == NULL)
		ft_error_wmsg(ERR_PARSE_SET_CO, i, greed[i]);
	pcone = cone;
	parse_vector(&pcone->origin, greed, ++i, "origin(");
	parse_vector(&pcone->n, greed, ++i, "normal(");
	vec3_normalize(&pcone->n);
	create_orthobasis_from_y_axis(pcone->n, &pcone->x, &pcone->z);
	parse_fval(&pcone->theta, greed, ++i, "theta(");
	parse_fval(&pcone->size, greed, ++i, "size(");
}

void
	light_set(t_light *light, char **greed, int i)
{
	if (light == NULL)
		ft_error_wmsg(ERR_PARSE_SET_LI, i, greed[i]);
	parse_color(&light->color, greed, ++i, "color(");
	parse_vector(&light->origin, greed, ++i, "origin(");
	parse_fval(&light->intensity, greed, ++i, "intensity(");
}
