/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 02:44:31 by nihuynh           #+#    #+#             */
/*   Updated: 2019/05/20 17:13:02 by nihuynh          ###   ########.fr       */
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
	parse_vector(&psphere->origin, "origin(", scene_file);
	parse_fval(&psphere->radius, "radius(", scene_file);
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
	parse_vector(&pplane->origin, "origin(", scene_file);
	parse_vector(&pplane->n, "normal(", scene_file);
	parse_limit(&pplane->size_x, &pplane->size_y, scene_file);
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
	parse_vector(&pcylinder->origin, "origin(", scene_file);
	parse_vector(&pcylinder->n, "normal(", scene_file);
	vec3_normalize(&pcylinder->n);
	create_orthobasis_from_y_axis(pcylinder->n, &pcylinder->x, &pcylinder->z);
	parse_fval(&pcylinder->radius, "radius(", scene_file);
	parse_fval(&pcylinder->size, "size(", scene_file);
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
	parse_vector(&pcone->origin, "origin(", scene_file);
	parse_vector(&pcone->n, "normal(", scene_file);
	vec3_normalize(&pcone->n);
	create_orthobasis_from_y_axis(pcone->n, &pcone->x, &pcone->z);
	parse_fval(&pcone->theta, "theta(", scene_file);
	parse_fval(&pcone->size, "size(", scene_file);
}

void
	light_set(t_light *light, t_parse_txt *scene_file)
{
	if (light == NULL)
	{
		err_set(scene_file, __func__, __LINE__, __FILE__);
		err_exit(ERR_PARSE_SET_LI, scene_file);
	}
	parse_color(&light->color, "color(", scene_file);
	parse_vector(&light->origin, "origin(", scene_file);
	parse_fval(&light->intensity, "intensity(", scene_file);
}
