/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 18:16:47 by nihuynh           #+#    #+#             */
/*   Updated: 2019/05/18 02:00:31 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "rt.h"
#include "config.h"
#include "libft.h"
#include "parse.h"

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
		{"plane", sizeof(t_plane), &plane_set, &plane_export, 3},
		{"sphere", sizeof(t_sphere), &sphere_set, &sphere_export, 2},
		{"cone", sizeof(t_cone), &cone_set, &cone_export, 4},
		{"cylinder", sizeof(t_cylinder), &cylinder_set, &cylinder_export, 4},
		{"csg", sizeof(t_btree), &csg_set, &csg_export, 0}
	};
	if (ft_btw(type, 0, sizeof(index_config) / sizeof(t_parse)))
	{
		config = ft_memcpy(config, &index_config[type], sizeof(t_parse));
		return ;
	}
	if (DEBUG)
		ft_printf("Type is not found type : %d", type);
	config->printout = NULL;
}

char
	*get_obj_str(int type)
{
	t_parse cfg;

	init_parse_cfg(type, &cfg);
	return (cfg.printout);
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

	ft_bzero(obj, sizeof(t_obj));
	init_obj_cfg(type, &obj_cfg);
	obj->type = type;
	obj->shape = shape;
	obj->f_inter = obj_cfg.f_inter;
	obj->f_gui = obj_cfg.f_gui;
	obj->find_normal = obj_cfg.find_normal;
	obj->get_uv = obj_cfg.get_uv;
}
