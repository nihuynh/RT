/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 02:44:31 by nihuynh           #+#    #+#             */
/*   Updated: 2019/06/05 01:29:37 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "librt.h"
#include "parse.h"

void
	sphere_set(void *sphere, t_parse_txt *scene_file)
{
	t_sphere	*psphere;

	if (sphere == NULL)
	{
		err_set(scene_file, __func__, __LINE__, __FILE__);
		err_exit(ERR_PARSE_SET_SP, scene_file);
	}
	psphere = sphere;
	psphere->origin = parse_vector("origin(", scene_file);
	psphere->radius = parse_fval("radius(", scene_file);
}

void
	plane_set(void *plane, t_parse_txt *scene_file)
{
	t_plane		*pplane;

	if (plane == NULL)
	{
		err_set(scene_file, __func__, __LINE__, __FILE__);
		err_exit(ERR_PARSE_SET_PL, scene_file);
	}
	pplane = plane;
	pplane->origin = parse_vector("origin(", scene_file);
	pplane->n = parse_vector("normal(", scene_file);
	pplane->size = parse_vec2("limit(", scene_file);
	vec3_normalize(&pplane->n);
	create_orthobasis_from_y_axis(pplane->n, &pplane->x, &pplane->y);
}

void
	cylinder_set(void *cylinder, t_parse_txt *scene_file)
{
	t_cylinder	*pcylinder;

	if (cylinder == NULL)
	{
		err_set(scene_file, __func__, __LINE__, __FILE__);
		err_exit(ERR_PARSE_SET_CY, scene_file);
	}
	pcylinder = cylinder;
	pcylinder->origin = parse_vector("origin(", scene_file);
	pcylinder->n = parse_vector("normal(", scene_file);
	pcylinder->radius = parse_fval("radius(", scene_file);
	pcylinder->size = parse_fval("size(", scene_file);
	vec3_normalize(&pcylinder->n);
	create_orthobasis_from_y_axis(pcylinder->n, &pcylinder->x, &pcylinder->z);
}

void
	cone_set(void *cone, t_parse_txt *scene_file)
{
	t_cone		*pcone;

	if (cone == NULL)
	{
		err_set(scene_file, __func__, __LINE__, __FILE__);
		err_exit(ERR_PARSE_SET_CO, scene_file);
	}
	pcone = cone;
	pcone->origin = parse_vector("origin(", scene_file);
	pcone->n = parse_vector("normal(", scene_file);
	pcone->theta = parse_fval("theta(", scene_file);
	pcone->size = parse_fval("size(", scene_file);
	vec3_normalize(&pcone->n);
	create_orthobasis_from_y_axis(pcone->n, &pcone->x, &pcone->z);
}

void
	light_set(t_light *light, t_parse_txt *scene_file)
{
	if (light == NULL)
	{
		err_set(scene_file, __func__, __LINE__, __FILE__);
		err_exit(ERR_PARSE_SET_LI, scene_file);
	}
	light->color = parse_color("color(", scene_file);
	light->origin = parse_vector("origin(", scene_file);
	light->intensity = parse_fval("intensity(", scene_file);
}
