/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_shape.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 23:50:39 by nihuynh           #+#    #+#             */
/*   Updated: 2019/07/03 00:03:53 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "librt.h"
#include "parse.h"

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
	vec3_normalize(&pcube->n);
	vec3_normalize(&pcube->x);
	vec3_normalize(&pcube->z);
	obj->pos = &pcube->origin;
	obj->x = &pcube->x;
	obj->n = &pcube->n;
	obj->z = &pcube->z;
}
