/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 18:16:47 by nihuynh           #+#    #+#             */
/*   Updated: 2019/05/17 18:22:04 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "rt.h"
// #include "config.h"
#include "libft.h"
#include "parse.h"

void 	csg_set(void *cone, char **greed, int i);
void 	csg_export(int fd, void *shape);
void 	inter_csg(t_inter *data, t_obj *node);
void 	ui_csg(void *res);
void 	normal_csg(t_inter *inter);
t_vec3 get_csg_uv(t_inter *inter);

/*
** @brief		Setting config for the type of object we want to parse
**
** @param type		The type of object we want to parse
** @param config 	The struct that is gonna hold the config
*/

void
	init_parse_cfg(int type, t_parse *config)
{
	const t_parse index_config[] = {
		{"plane", sizeof(t_plane), &plane_set, &plane_export, 6},
		{"sphere", sizeof(t_sphere), &sphere_set, &sphere_export, 5},
		{"cone", sizeof(t_cone), &cone_set, &cone_export, 7},
		{"cylinder", sizeof(t_cylinder), &cylinder_set, &cylinder_export, 7},
		{"csg", sizeof(t_btree), &csg_set, &csg_export, 3}
	};

	config = ft_memcpy(config, &index_config[type], sizeof(t_parse));
}

void
	init_obj_cfg(int type, t_objset *config)
{
	const t_objset obj_func[] = {
		{&inter_plane, &ui_plane, &normal_plane, &get_plane_uv},
		{&inter_sphere, &ui_sphere, &normal_sphere, &get_sphere_uv},
		{&inter_cone, &ui_cone, &normal_cone, &get_cone_uv},
		{&inter_cylinder, &ui_cylinder, &normal_cylinder, &get_cylinder_uv},
		{&inter_csg, &ui_csg, &normal_csg, &get_csg_uv}
	};

	config = ft_memcpy(config, &obj_func[type], sizeof(t_objset));
}

/*
** @brief	Setting the obj struct for the shape
**
** @param obj	Struct that we want to set
** @param type	Type of shape
** @param shape	The shape
*/

void
	obj_set(t_obj *obj, int type, void *shape)
{
	t_objset obj_cfg;
	init_obj_cfg(type, &obj_cfg);

	ft_bzero(obj, sizeof(t_obj));
	obj->type = type;
	obj->shape = shape;
	obj->f_inter = obj_cfg.f_inter;
	obj->f_gui = obj_cfg.f_gui;
	obj->find_normal = obj_cfg.find_normal;
	obj->get_uv = obj_cfg.get_uv;
}
