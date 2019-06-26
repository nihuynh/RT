/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 02:44:31 by nihuynh           #+#    #+#             */
/*   Updated: 2019/06/26 22:50:02 by sklepper         ###   ########.fr       */
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
	psphere->radius = parse_fval("radius(", scene_file);
	obj->pos = &psphere->origin;
	obj->x = NULL;
	obj->n = NULL;
	obj->z = NULL;
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
	pplane->size = parse_vec2("limit(", scene_file);
	pplane->type = parse_int("type", scene_file);
	vec3_normalize(&pplane->n);
	create_orthobasis_from_y_axis(pplane->n, &pplane->x, &pplane->y);
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
	pcylinder->radius = parse_fval("radius(", scene_file);
	pcylinder->size = parse_fval("size(", scene_file);
	vec3_normalize(&pcylinder->n);
	create_orthobasis_from_y_axis(pcylinder->n, &pcylinder->x, &pcylinder->z);
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
	pcone->theta = parse_fval("theta(", scene_file);
	pcone->size = parse_fval("size(", scene_file);
	vec3_normalize(&pcone->n);
	create_orthobasis_from_y_axis(pcone->n, &pcone->x, &pcone->z);
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

void
	set_min_max_corner(t_cube *cube)
{
	float size;

	size = cube->size;
	cube->min_corner.x = fminf(cube->origin.x - size, cube->origin.x + size);
	cube->min_corner.y = fminf(cube->origin.y - size, cube->origin.y + size);
	cube->min_corner.z = fminf(cube->origin.z - size, cube->origin.z + size);
	cube->max_corner.x = fmaxf(cube->origin.x - size, cube->origin.x + size);
	cube->max_corner.y = fmaxf(cube->origin.y - size, cube->origin.y + size);
	cube->max_corner.z = fmaxf(cube->origin.z - size, cube->origin.z + size);
}

void
	cube_set(t_obj *obj, void *cube, t_parse_txt *scene_file)
{
	t_cube		*pcube;

	if (cube == NULL)
	{
		err_set(scene_file, __func__, __LINE__, __FILE__);
		err_exit(ERR_PARSE_SET_PL, scene_file);
	}
	pcube = cube;
	pcube->origin = parse_vector("origin(", scene_file);
	pcube->n = parse_vector("normal(", scene_file);
	pcube->x = parse_vector("x(", scene_file);
	pcube->z = parse_vector("z(", scene_file);
	pcube->size = parse_fval("size(", scene_file);
	set_min_max_corner(pcube);
	vec3_normalize(&pcube->n);
	vec3_normalize(&pcube->x);
	vec3_normalize(&pcube->z);
	obj->pos = &pcube->origin;
	obj->x = &pcube->x;
	obj->n = &pcube->n;
	obj->z = &pcube->z;
}

void
	tore_set(t_obj *obj, void *tore, t_parse_txt *scene_file)
{
	t_tore		*ptore;

	if (tore == NULL)
	{
		err_set(scene_file, __func__, __LINE__, __FILE__);
		err_exit(ERR_PARSE_SET_PL, scene_file);
	}
	ptore = tore;
	ptore->origin = parse_vector("origin(", scene_file);
	ptore->n = parse_vector("normal(", scene_file);
	ptore->x = parse_vector("x(", scene_file);
	ptore->z = parse_vector("z(", scene_file);
	ptore->size = parse_fval("size(", scene_file);
	ptore->radius = parse_fval("radius(", scene_file);
	vec3_normalize(&ptore->n);
	vec3_normalize(&ptore->x);
	vec3_normalize(&ptore->z);
	obj->pos = &ptore->origin;
	obj->x = &ptore->x;
	obj->n = &ptore->n;
	obj->z = &ptore->z;
}
