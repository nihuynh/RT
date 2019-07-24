/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 02:44:31 by nihuynh           #+#    #+#             */
/*   Updated: 2019/07/03 00:03:47 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "librt.h"
#include "parse.h"

void
	sphere_set(t_obj *obj, void *sphere, t_parse_txt *scene_file)
{
	t_sphere	*psphere;

	if (sphere == NULL)
	{
		err_set(scene_file, __func__, __LINE__, __FILE__);
		err_exit(ERR_PARSE_SET_SP, scene_file);
	}
	psphere = sphere;
	psphere->origin = parse_vector("origin(", scene_file);
	psphere->x = parse_vector("x(", scene_file);
	psphere->y = parse_vector("y(", scene_file);
	psphere->z = parse_vector("z(", scene_file);
	psphere->radius = parse_fval("radius(", scene_file);
	obj->pos = &psphere->origin;
	obj->x = &psphere->x;
	obj->n = &psphere->y;
	obj->z = &psphere->z;
}

void
	plane_set(t_obj *obj, void *plane, t_parse_txt *scene_file)
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
	pplane->x = parse_vector("x(", scene_file);
	pplane->y = parse_vector("y(", scene_file);
	pplane->size = parse_vec2("limit(", scene_file);
	pplane->type = parse_int("type(", scene_file);
	if (pplane->type == 2)
		pplane->p1 = parse_vec2("p1(", scene_file);
	if (pplane->type == 2)
		pplane->p2 = parse_vec2("p2(", scene_file);
	vec3_normalize(&pplane->x);
	vec3_normalize(&pplane->n);
	vec3_normalize(&pplane->y);
	obj->pos = &pplane->origin;
	obj->x = &pplane->x;
	obj->n = &pplane->n;
	obj->z = &pplane->y;
}

void
	cylinder_set(t_obj *obj, void *cylinder, t_parse_txt *scene_file)
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
	pcylinder->x = parse_vector("x(", scene_file);
	pcylinder->z = parse_vector("z(", scene_file);
	pcylinder->radius = parse_fval("radius(", scene_file);
	pcylinder->size = parse_fval("size(", scene_file);
	vec3_normalize(&pcylinder->x);
	vec3_normalize(&pcylinder->n);
	vec3_normalize(&pcylinder->z);
	obj->pos = &pcylinder->origin;
	obj->x = &pcylinder->x;
	obj->n = &pcylinder->n;
	obj->z = &pcylinder->z;
}

void
	cone_set(t_obj *obj, void *cone, t_parse_txt *scene_file)
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
	pcone->x = parse_vector("x(", scene_file);
	pcone->z = parse_vector("z(", scene_file);
	pcone->theta = parse_fval("theta(", scene_file);
	pcone->size = parse_fval("size(", scene_file);
	vec3_normalize(&pcone->x);
	vec3_normalize(&pcone->n);
	vec3_normalize(&pcone->z);
	obj->pos = &pcone->origin;
	obj->x = &pcone->x;
	obj->n = &pcone->n;
	obj->z = &pcone->z;
}

void
	light_set(t_light *light, t_parse_txt *scene_file)
{
	if (light == NULL)
	{
		err_set(scene_file, __func__, __LINE__, __FILE__);
		err_exit(ERR_PARSE_SET_LI, scene_file);
	}
	light->anim = NULL;
	light->color = parse_color("color(", scene_file);
	light->origin = parse_vector("origin(", scene_file);
	light->intensity = parse_fval("intensity(", scene_file);
}
