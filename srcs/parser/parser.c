/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 10:12:22 by sklepper          #+#    #+#             */
/*   Updated: 2019/05/06 19:45:36 by nihuynh          ###   ########.fr       */
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
		{"plane", sizeof(t_plane), &plane_set, &plane_export, 6},
		{"sphere", sizeof(t_sphere), &sphere_set, &sphere_export, 5},
		{"cone", sizeof(t_cone), &cone_set, &cone_export, 7},
		{"cylinder", sizeof(t_cylinder), &cylinder_set, &cylinder_export, 7}
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
	const t_objset obj_func[] = {
		{&inter_plane, &interface_plane, &normal_plane, &get_plane_uv},
		{&inter_sphere, &interface_sphere, &normal_sphere, &get_sphere_uv},
		{&inter_cone, &interface_cone, &normal_cone, &get_cone_uv},
		{&inter_cylinder, &interface_cylinder, &normal_cylinder, &get_cylinder_uv},
	};

	ft_bzero(obj, sizeof(t_obj));
	obj->type = type;
	obj->shape = shape;
	obj->f_inter = obj_func[type].f_inter;
	obj->f_gui = obj_func[type].f_gui;
	obj->find_normal = obj_func[type].find_normal;
	obj->get_uv = obj_func[type].get_uv;
}

static inline int
	parse_material(t_data *data, t_material *dst, char **tab, int idx)
{
	char		*str;
	t_material	*mat;

	if ((str = ft_strstr(tab[idx], "mat(")))
	{
		str += 4;
		if (!(mat = ft_lstgetelt(data->lst_mat, &matcmp, str)))
			ft_error(__func__, __LINE__);
		ft_memcpy(dst, mat, sizeof(t_material));
		return (idx + 2);
	}
	dst->name = "";
	dst->tex = parse_texture(data->lst_tex, tab[idx], idx);
	parse_color(&dst->color_diffuse, tab[idx + 1], idx + 1, "color_diffuse(");
	parse_color(&dst->color_specular, tab[idx + 2], idx + 2, "color_specular(");
	parse_color(&dst->self_light, tab[idx + 3], idx + 3, "self_light(");
	parse_fval(&dst->spec_idx, tab[idx + 4], idx + 4, "spec_idx(");
	parse_fval(&dst->spec_power, tab[idx + 5], idx + 5, "spec_power(");
	idx += 6;
	parse_color(&dst->refraction_color, tab[idx], idx, "refraction_color(");
	idx++;
	parse_color(&dst->reflection_color, tab[idx], idx, "reflection_color(");
	parse_fval(&dst->refraction_idx, tab[idx + 1], idx + 1, "refraction_idx(");
	return (idx + 3);
}

/*
** @brief	General parser for all of the shapes
**
** @param greed	Contains the whole input file
** @param data	General struct for holding data
** @param l_idx	Line index to navigate in greed
** @param type	Type of shape to parse
** @return int	Returns the line on which it finished parsing the shape
*/

int
	parse_shape(char **greed, t_data *d, int l_idx, int type)
{
	t_obj		obj;
	t_parse		cfg;
	void		*shape;
	int			idx;

	init_parse(type, &cfg);
	if (DEBUG)
		ft_putendl(cfg.printout);
	if (!(shape = malloc(cfg.content_size)))
		ft_error(__func__, __LINE__);
	cfg.setter(shape, greed, ++l_idx);
	obj_set(&obj, type, shape);
	obj.export = cfg.export;
	idx = parse_material(d, &obj.material, greed, l_idx + cfg.line_offset - 2);
	ft_lstpushnew(&d->scene.lst_obj, &obj, sizeof(t_obj));
	return (idx);
}

/*
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
	t_light		light;

	line_idx++;
	if (DEBUG)
		ft_putendl("Light :");
	light_set(&light, greed, line_idx);
	ft_lstpushnew(&data->scene.lst_light, &light, sizeof(t_light));
	line_idx += 5;
	return (line_idx);
}
