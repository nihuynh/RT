/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 10:12:22 by sklepper          #+#    #+#             */
/*   Updated: 2018/12/20 23:26:20 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "libft.h"
#include "parse.h"

static inline void	init_parse(int type, t_parse *config)
{
	const t_parse index_config[4] = {
		{"Plane : ", sizeof(t_plane), &plane_set, 6},
		{"Sphere : ", sizeof(t_sphere), &sphere_set, 6},
		{"Cone : ", sizeof(t_cone), &cone_set, 7},
		{"Cylinder : ", sizeof(t_cylinder), &cylinder_set, 7},
	};

	config = ft_memcpy(config, &index_config[type], sizeof(t_parse));
}

static inline void	obj_set(t_obj *obj, int type, void *shape)
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

int					parse_shape(char **greed, t_data *data, int l_idx, int type)
{
	t_list		*node;
	t_obj		obj;
	t_parse		config;
	void		*shape;
	int			idx;

	l_idx++;
	init_parse(type, &config);
	if (DEBUG)
		ft_putendl(config.printout);
	if (!(shape = malloc(config.content_size)))
		ft_error(__func__, __LINE__);
	config.setter(shape, greed, l_idx);
	obj_set(&obj, type, shape);
	idx = l_idx + config.line_offset - 2;
	parse_fval(&obj.diffuse, greed[idx], idx, "diffuse(");
	obj.diffuse /= 100;
	if (!(node = ft_lstnew(&obj, sizeof(t_obj))))
		ft_error(__func__, __LINE__);
	ft_lstadd(&data->lst_obj, node);
	l_idx += config.line_offset;
	return (l_idx);
}

int					parse_light(char **greed, t_data *data, int line_idx)
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
	data->nb_light++;
	line_idx += 5;
	return (line_idx);
}
