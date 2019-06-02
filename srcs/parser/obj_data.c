/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 18:16:47 by nihuynh           #+#    #+#             */
/*   Updated: 2019/06/03 00:38:22 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "config.h"
#include "libft.h"
#include "export.h"
#include "librt.h"
#include "interface.h"

/**
** @brief		Setting config for the type of object we want to parse
**
** @param type		: type of the object requested
** @param config	: Dst of the data
*/

void
	init_parse_cfg(int type, t_parse *config)
{
	const t_parse index_config[] = {
		{"plane", sizeof(t_plane), &plane_set, &plane_export},
		{"sphere", sizeof(t_sphere), &sphere_set, &sphere_export},
		{"cone", sizeof(t_cone), &cone_set, &cone_export},
		{"cylinder", sizeof(t_cylinder), &cylinder_set, &cylinder_export},
		{"csg", sizeof(t_csg), &csg_set, &csg_export}
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

/**
** @brief Return the str from type
**
** @param type		: Object type
** @return char*	: str of object type
*/

char
	*get_obj_str(int type)
{
	t_parse cfg;

	init_parse_cfg(type, &cfg);
	return (cfg.printout);
}

/**
** @brief Return the obj type from a str
**
** @param obj_type	: str who can be object type
** @return int		: Object type
*/

int
	get_obj_type(char *obj_type)
{
	char	*type_tested;
	int		type;

	type = -1;
	type_tested = NULL;
	while ((type_tested = get_obj_str(++type)))
	{
		if (ft_strstr(obj_type, type_tested))
			return (type);
	}
	return (-1);
}

/**
** @brief Get the obj functions depending on the type needed
**
** @param type		: type of the object requested
** @param config 	: Dst of the data
*/

void
	init_obj_cfg(int type, t_objset *config)
{
	const t_objset obj_func[] = {
		{&inter_plane, &ui_plane, &normal_plane, &get_plane_uv},
		{&inter_sphere, &ui_sphere, &normal_sphere, &get_sphere_uv},
		{&inter_cone, &ui_cone, &normal_cone, &get_cone_uv},
		{&inter_cylinder, &ui_cylinder, &normal_cylinder, &get_cylinder_uv},
		{&inter_csg, &ui_csg, NULL, NULL}
	};

	config = ft_memcpy(config, &obj_func[type], sizeof(t_objset));
}

/**
** @brief	Setting the obj struct.
**
** @param obj 	: Dst of the data
** @param type	: type of the object requested
** @param shape	: Adress of the shape data
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
