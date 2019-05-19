/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 02:44:31 by nihuynh           #+#    #+#             */
/*   Updated: 2019/05/19 02:14:42 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "parse.h"

void
	sphere_set(void *sphere, t_parse_txt *scene_file)
{
	t_sphere	*psphere;

	if (sphere == NULL)
	{
		scene_file->err_set(scene_file, __func__, __LINE__, __FILE__);
		scene_file->err_exit(ERR_PARSE_SET_SP, scene_file);
	}
	psphere = sphere;
	parse_vector(&psphere->origin, scene_file->greed, scene_file->line_idx++, "origin(");
	parse_fval(&psphere->radius, scene_file->greed, scene_file->line_idx++, "radius(");
}

void
	plane_set(void *plane, t_parse_txt *scene_file)
{
	t_plane		*pplane;

	if (plane == NULL)
	{
		scene_file->err_set(scene_file, __func__, __LINE__, __FILE__);
		scene_file->err_exit(ERR_PARSE_SET_PL, scene_file);
	}
	pplane = plane;
	parse_vector(&pplane->origin, scene_file->greed, scene_file->line_idx++, "origin(");
	parse_vector(&pplane->n, scene_file->greed, scene_file->line_idx++, "normal(");
	parse_limit(&pplane->size_x, &pplane->size_y, scene_file->greed, scene_file->line_idx++);
	vec3_normalize(&pplane->n);
	create_orthobasis_from_y_axis(pplane->n, &pplane->x, &pplane->y);
}

void
	cylinder_set(void *cylinder, t_parse_txt *scene_file)
{
	t_cylinder	*pcylinder;

	if (cylinder == NULL)
	{
		scene_file->err_set(scene_file, __func__, __LINE__, __FILE__);
		scene_file->err_exit(ERR_PARSE_SET_CY, scene_file);
	}
	pcylinder = cylinder;
	parse_vector(&pcylinder->origin, scene_file->greed, scene_file->line_idx++, "origin(");
	parse_vector(&pcylinder->n, scene_file->greed, scene_file->line_idx++, "normal(");
	vec3_normalize(&pcylinder->n);
	create_orthobasis_from_y_axis(pcylinder->n, &pcylinder->x, &pcylinder->z);
	parse_fval(&pcylinder->radius, scene_file->greed, scene_file->line_idx++, "radius(");
	parse_fval(&pcylinder->size, scene_file->greed, scene_file->line_idx++, "size(");
}

void
	cone_set(void *cone, t_parse_txt *scene_file)
{
	t_cone		*pcone;

	if (cone == NULL)
	{
		scene_file->err_set(scene_file, __func__, __LINE__, __FILE__);
		scene_file->err_exit(ERR_PARSE_SET_CO, scene_file);
	}
	pcone = cone;
	parse_vector(&pcone->origin, scene_file->greed, scene_file->line_idx++, "origin(");
	parse_vector(&pcone->n, scene_file->greed, scene_file->line_idx++, "normal(");
	vec3_normalize(&pcone->n);
	create_orthobasis_from_y_axis(pcone->n, &pcone->x, &pcone->z);
	parse_fval(&pcone->theta, scene_file->greed, scene_file->line_idx++, "theta(");
	parse_fval(&pcone->size, scene_file->greed, scene_file->line_idx++, "size(");
}

void
	light_set(t_light *light, t_parse_txt *scene_file)
{
	if (light == NULL)
	{
		scene_file->err_set(scene_file, __func__, __LINE__, __FILE__);
		scene_file->err_exit(ERR_PARSE_SET_LI, scene_file);
	}
	parse_color(&light->color, scene_file->greed, scene_file->line_idx++, "color(");
	parse_vector(&light->origin, scene_file->greed, scene_file->line_idx++, "origin(");
	parse_fval(&light->intensity, scene_file->greed, scene_file->line_idx++, "intensity(");
}
