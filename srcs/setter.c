/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 02:44:31 by nihuynh           #+#    #+#             */
/*   Updated: 2018/12/19 17:24:21 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "parse.h"

void	sphere_set(void *sphere, char **greed, int i)
{
	t_sphere	*psphere;

	if (sphere == NULL)
		ft_error_wmsg(ERR_PARSE_SET_SP, i, greed[i]);
	psphere = sphere;
	parse_color(&psphere->color, greed[i + 1], i + 1);
	parse_origin(&psphere->origin, greed[i + 2], i + 2);
	parse_fval(&psphere->radius, greed[i + 3], i + 3, "radius(");
}

void	plane_set(void *plane, char **greed, int i)
{
	t_plane	*pplane;

	if (plane == NULL)
		ft_error_wmsg(ERR_PARSE_SET_PL, i, greed[i]);
	pplane = plane;
	parse_color(&pplane->color, greed[i + 1], i + 1);
	parse_origin(&pplane->origin, greed[i + 2], i + 2);
	parse_normal(&pplane->n, greed[i + 3], i + 3);
	vec3_normalize(&pplane->n);
}

void	cylinder_set(void *cylinder, char **greed, int i)
{
	t_cylinder	*pcylinder;

	if (cylinder == NULL)
		ft_error_wmsg(ERR_PARSE_SET_CY, i, greed[i]);
	pcylinder = cylinder;
	parse_color(&pcylinder->color, greed[i + 1], i + 1);
	parse_origin(&pcylinder->origin, greed[i + 2], i + 2);
	parse_normal(&pcylinder->n, greed[i + 3], i + 3);
	vec3_normalize(&pcylinder->n);
	parse_fval(&pcylinder->radius, greed[i + 4], i + 4, "radius(");
}

void	cone_set(void *cone, char **greed, int i)
{
	t_cone	*pcone;

	if (cone == NULL)
		ft_error_wmsg(ERR_PARSE_SET_CO, i, greed[i]);
	pcone = cone;
	parse_color(&pcone->color, greed[i + 1], i + 1);
	parse_origin(&pcone->origin, greed[i + 2], i + 2);
	parse_normal(&pcone->n, greed[i + 3], i + 3);
	vec3_normalize(&pcone->n);
	parse_fval(&pcone->theta, greed[i + 4], i + 4, "theta(");
}

void	light_set(t_light *light, char **greed, int i)
{
	if (light == NULL)
		ft_error_wmsg(ERR_PARSE_SET_LI, i, greed[i]);
	parse_color(&light->color, greed[i + 1], i + 1);
	parse_origin(&light->origin, greed[i + 2], i + 2);
	parse_fval(&light->intensity, greed[i + 3], i + 3, "intensity(");
	light->intensity *= light->intensity;
}
