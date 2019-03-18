/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 10:12:22 by sklepper          #+#    #+#             */
/*   Updated: 2019/03/18 16:49:40 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "libft.h"
#include "parse.h"

/*
** @brief		Setting config for the type of object we want to parse
**
** @param type		The type of object we want to parse
** @param config 	The struct that is gonna hold the config
*/

static inline void
	init_parse(int type, t_parse *config)
{
	const t_parse index_config[4] = {
		{"Plane : ", sizeof(t_plane), &plane_set, 6},
		{"Sphere : ", sizeof(t_sphere), &sphere_set, 5},
		{"Cone : ", sizeof(t_cone), &cone_set, 6},
		{"Cylinder : ", sizeof(t_cylinder), &cylinder_set, 6},
	};

	config = ft_memcpy(config, &index_config[type], sizeof(t_parse));
}

/*
** @brief	Setting the obj struct for the shape
**
** @param obj	Struct that we want to set
** @param type	Type of shape
** @param shape	The shape
*/

static inline void
	obj_set(t_obj *obj, int type, void *shape)
{
	obj->type = type;
	obj->shape = shape;
	if (type == SPHERE)
		obj->f_inter = &inter_sphere;
	else if (type == PLANE)
		obj->f_inter = &inter_plane;
	else if (type == CONE)
		obj->f_inter = &inter_cone;
	else if (type == CYLINDER)
		obj->f_inter = &inter_cylinder;
}

static inline void
	load_material(t_material *dst, char *str)
{
	(void)str;
	// CSV ?
	// load the material list.
	// find the right material
	// copy the mat into dst
	itocolor(&dst->color_ambient, 0x1D0E12);
	itocolor(&dst->color_diffuse, 0xB76E2F);
	itocolor(&dst->color_specular, 0xE7CDB4);
	itocolor(&dst->self_light, 0x000000);
	dst->spec_idx = 0.5;
	dst->spec_power = 56;
	dst->absorb_idx = 0;
	dst->deflect_idx = 0.75;
}

static inline int
	parse_material(t_material *dst, char **tab, int idx)
{
	char *str;
	if ((str = ft_strstr(tab[idx], "mat(")))
	{
		str += 4;
		load_material(dst, str);
		return (idx + 2);
	}
	parse_color(&dst->color_ambient, tab[idx], idx, "color_ambient(");
	parse_color(&dst->color_diffuse, tab[idx + 1], idx + 1, "color_diffuse(");
	parse_color(&dst->color_specular, tab[idx + 2], idx + 2, "color_specular(");
	parse_color(&dst->self_light, tab[idx + 3], idx + 3, "self_light(");
	parse_fval(&dst->spec_idx, tab[idx + 4], idx + 4, "spec_idx(");
	parse_fval(&dst->spec_power, tab[idx + 5], idx + 5, "spec_power(");
	parse_fval(&dst->absorb_idx, tab[idx + 6], idx + 6, "absorb_idx(");
	parse_fval(&dst->deflect_idx, tab[idx + 7], idx + 7, "deflect_idx(");
	return (idx + 9);
}

/**
** @brief	General parser for all of the shapes
**
** @param greed	Contains the whole input file
** @param data	General struct for holding data
** @param l_idx	Line index to navigate in greed
** @param type	Type of shape to parse
** @return int	Returns the line on which it finished parsing the shape
*/

int
	parse_shape(char **greed, t_data *data, int l_idx, int type)
{
	t_list		*node;
	t_obj		obj;
	t_parse		config;
	void		*shape;
	int			idx;

	init_parse(type, &config);
	if (DEBUG)
		ft_putendl(config.printout);
	if (!(shape = malloc(config.content_size)))
		ft_error(__func__, __LINE__);
	config.setter(shape, greed, ++l_idx);
	obj_set(&obj, type, shape);
	idx = parse_material(&obj.material, greed, l_idx + config.line_offset - 2);
	if (!(node = ft_lstnew(&obj, sizeof(t_obj))))
		ft_error(__func__, __LINE__);
	ft_lstadd(&data->lst_obj, node);
	return (idx);
}

/**
** @brief	Parser for light objects
**
** @param greed		Contains the whole input file
** @param data		General struct for holding data
** @param line_idx	Line index to navigate in greed
** @return int		Returns the line on which it finished parsing the light
*/

int
	parse_light(char **greed, t_data *data, int line_idx)
{
	t_list		*node;
	t_light		light;

	line_idx++;
	if (DEBUG)
		ft_putendl("Light :");
	light_set(&light, greed, line_idx);
	if (!(node = ft_lstnew(&light, sizeof(t_light))))
		ft_error(__func__, __LINE__);
	ft_lstadd(&data->lst_light, node);
	line_idx += 5;
	return (line_idx);
}
