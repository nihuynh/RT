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
	parse_origin(&psphere->origin, greed[i + 1], i + 1);
	parse_fval(&psphere->radius, greed[i + 2], i + 2, "radius(");
}

void
	plane_set(void *plane, char **greed, int i)
{
	t_plane		*pplane;
//	t_matrix	mat[2];
	t_vec3		vi;

	if (plane == NULL)
		ft_error_wmsg(ERR_PARSE_SET_PL, i, greed[i]);
	pplane = plane;
	parse_origin(&pplane->origin, greed[i + 1], i + 1);
	parse_normal(&pplane->n, greed[i + 2], i + 2);
	parse_limit(&pplane->size_x, &pplane->size_y, greed[i + 3], i + 3);
	vec3_normalize(&pplane->n);
	vec3_new(&pplane->x, 1, 0, 0);
	vec3_new(&pplane->y, 0, 1, 0);
	vec3_new(&vi, 0, 0, -1);
//	mat3_rot(&mat[0], &mat[1], &vi, &pplane->n);
//	vec3_matrix_apply(&pplane->x, &mat[0], &mat[1]);
//	vec3_matrix_apply(&pplane->y, &mat[0], &mat[1]);
	parse_texture(pplane, greed[i + 4], i + 4);
}

void
	cylinder_set(void *cylinder, char **greed, int i)
{
	t_cylinder	*pcylinder;

	if (cylinder == NULL)
		ft_error_wmsg(ERR_PARSE_SET_CY, i, greed[i]);
	pcylinder = cylinder;
	parse_origin(&pcylinder->origin, greed[i + 1], i + 1);
	parse_normal(&pcylinder->n, greed[i + 2], i + 2);
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
	parse_origin(&pcone->origin, greed[i + 1], i + 1);
	parse_normal(&pcone->n, greed[i + 2], i + 2);
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
	parse_origin(&light->origin, greed[i + 2], i + 2);
	parse_fval(&light->intensity, greed[i + 3], i + 3, "intensity(");
	light->intensity *= light->intensity;
}
