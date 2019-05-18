/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 10:12:22 by sklepper          #+#    #+#             */
/*   Updated: 2019/05/18 03:11:32 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "config.h"
#include "libft.h"
#include "parse.h"



static inline int
	parse_material(t_data *data, t_material *dst, char **tab, int idx)
{
	char		*str;
	t_material	*mat;
	int			idx_local;

	if ((str = ft_strstr(tab[idx], "mat(")))
	{
		str += 4;
		if (!(mat = ft_lstgetelt(data->lst_mat, &matcmp, str)))
			ft_error(__func__, __LINE__);
		ft_memcpy(dst, mat, sizeof(t_material));
		return (1);
	}
	idx_local = idx;
	ft_bzero(dst, sizeof(t_material));
	dst->name = "";
	dst->tex = parse_texture(&data->lst_tex, tab, idx++);
	parse_color(&dst->color_diffuse, tab, idx++, "color_diffuse(");
	parse_color(&dst->color_specular, tab, idx++, "color_specular(");
	parse_color(&dst->color_tex, tab, idx++, "color_tex(");
	parse_fval(&dst->spec_idx, tab, idx++, "spec_idx(");
	parse_fval(&dst->spec_power, tab, idx++, "spec_power(");
	parse_color(&dst->refraction_color, tab, idx++, "refraction_color(");
	parse_color(&dst->reflection_color, tab, idx++, "reflection_color(");
	parse_fval(&dst->refraction_idx, tab, idx++, "refraction_idx(");
	return (idx - idx_local);
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

void
	create_obj(t_obj *obj, char **greed, int *l_idx, int type)
{
	t_parse		cfg;
	void		*shape;
	t_data		*app;

	app = get_app(NULL);
	init_parse_cfg(type, &cfg);
	*l_idx +=  2;
	if (DEBUG)
		ft_putendl(cfg.printout);
	if (!(shape = malloc(cfg.content_size)))
		ft_error(__func__, __LINE__);
	cfg.setter(shape, greed, *l_idx);
	obj_set(obj, type, shape);
	obj->export = cfg.export;
	*l_idx +=  cfg.line_offset;
	*l_idx += parse_material(app, &(obj->material), greed, *l_idx);
}

void
	parse_shape(t_data *app, t_parse_txt *scene_file, int type)
{
	t_obj		obj;

	create_obj(&obj, scene_file->greed, &scene_file->line_idx, type);
	ft_lstpushnew(&app->scene.lst_obj, &obj, sizeof(t_obj));
	scene_file->line_idx++;
}

/*
** @brief	Parser for light objects
**
** @param greed		Contains the whole input file
** @param data		General struct for holding data
** @param line_idx	Line index to navigate in greed
** @return int		Returns the line on which it finished parsing the light
*/

void
	parse_light(t_data *data, t_parse_txt *scene_file)
{
	t_light		light;

	if (DEBUG)
		ft_putendl("Light :");
	scene_file->line_idx += 2;
	light_set(&light, scene_file->greed, scene_file->line_idx);
	ft_lstpushnew(&data->scene.lst_light, &light, sizeof(t_light));
	scene_file->line_idx += 4;
}
