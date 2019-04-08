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
	parse_vector(&psphere->origin, greed[i + 1], i + 1, "origin(");
	parse_fval(&psphere->radius, greed[i + 2], i + 2, "radius(");
}

void
	plane_set(void *plane, char **greed, int i)
{
	t_plane		*pplane;
	t_matrix	rotation;

	if (plane == NULL)
		ft_error_wmsg(ERR_PARSE_SET_PL, i, greed[i]);
	pplane = plane;
	parse_vector(&pplane->origin, greed[i + 1], i + 1, "origin(");
	parse_vector(&pplane->n, greed[i + 2], i + 2, "normal(");
	parse_limit(&pplane->size_x, &pplane->size_y, greed[i + 3], i + 3);
	vec3_normalize(&pplane->n);
	vec3_new(&pplane->x, 1, 0, 0);
	vec3_new(&pplane->y, 0, 1, 0);
	rotation = create_rotation_from_direction(pplane->n);
	apply_matrix(&pplane->x, &rotation);
	apply_matrix(&pplane->y, &rotation);
	parse_texture(pplane, greed[i + 4], i + 4);
}

void
	cylinder_set(void *cylinder, char **greed, int i)
{
	t_cylinder	*pcylinder;

	if (cylinder == NULL)
		ft_error_wmsg(ERR_PARSE_SET_CY, i, greed[i]);
	pcylinder = cylinder;
	parse_vector(&pcylinder->origin, greed[i + 1], i + 1, "origin(");
	parse_vector(&pcylinder->n, greed[i + 2], i + 2, "normal(");
	vec3_normalize(&pcylinder->n);
	parse_fval(&pcylinder->radius, greed[i + 3], i + 3, "radius(");
	parse_fval(&pcylinder->size, greed[i + 4], i + 4, "size(");
}

void
	cone_set(void *cone, char **greed, int i)
{
	t_cone	*pcone;

	if (cone == NULL)
		ft_error_wmsg(ERR_PARSE_SET_CO, i, greed[i]);
	pcone = cone;
	parse_vector(&pcone->origin, greed[i + 1], i + 1, "origin(");
	parse_vector(&pcone->n, greed[i + 2], i + 2, "normal(");
	vec3_normalize(&pcone->n);
	parse_fval(&pcone->theta, greed[i + 3], i + 3, "theta(");
	parse_fval(&pcone->size, greed[i + 4], i + 4, "size(");
}

void
	light_set(t_light *light, char **greed, int i)
{
	if (light == NULL)
		ft_error_wmsg(ERR_PARSE_SET_LI, i, greed[i]);
	parse_color(&light->color, greed[i + 1], i + 1, "color(");
	parse_vector(&light->origin, greed[i + 2], i + 2, "origin(");
	parse_fval(&light->intensity, greed[i + 3], i + 3, "intensity(");
	light->intensity *= light->intensity;
}
