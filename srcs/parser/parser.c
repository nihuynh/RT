/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 10:12:22 by sklepper          #+#    #+#             */
/*   Updated: 2019/05/19 06:51:07 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "config.h"
#include "libft.h"
#include "parse.h"



static inline void
	parse_material(t_material *dst, t_parse_txt *scene_file)
{
	t_data		*app;
	char		*str;
	t_material	*mat;

	app = get_app(NULL);
	if ((str = ft_strstr(scene_file->get_curr_line(scene_file), "mat(")))
	{
		str += 4;
		if (!(mat = ft_lstgetelt(app->lst_mat, &matcmp, str)))
		{
			scene_file->err_set(scene_file, __func__, __LINE__, __FILE__);
			scene_file->err_exit(ERR_UNKNWD_MAT, scene_file);
		}
		ft_memcpy(dst, mat, sizeof(t_material));
		scene_file->line_idx++;
		return ;
	}
	ft_bzero(dst, sizeof(t_material));
	dst->name = "";
	dst->tex = parse_texture(&app->lst_tex, scene_file);
	parse_color(&dst->color_diffuse, "color_diffuse(", scene_file);
	parse_color(&dst->color_specular, "color_specular(", scene_file);
	parse_color(&dst->color_tex, "color_tex(", scene_file);
	parse_fval(&dst->spec_idx, "spec_idx(", scene_file);
	parse_fval(&dst->spec_power, "spec_power(", scene_file);
	parse_color(&dst->refraction_color, "refraction_color(", scene_file);
	parse_color(&dst->reflection_color, "reflection_color(", scene_file);
	parse_fval(&dst->refraction_idx, "refraction_idx(", scene_file);
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
	create_obj(t_obj *obj, t_parse_txt *scene_file, int type)
{
	t_parse		cfg;
	void		*shape;
	t_data		*app;

	app = get_app(NULL);
	init_parse_cfg(type, &cfg);
	if (DEBUG)
		ft_putendl(cfg.printout);
	if (!(shape = malloc(cfg.content_size)))
		ft_error(__func__, __LINE__);
	check_opening_bracket(scene_file);
	cfg.setter(shape, scene_file);
	obj_set(obj, type, shape);
	obj->export = cfg.export;
	parse_material(&(obj->material), scene_file);
	check_closing_bracket(scene_file);
}

/**
** @brief Built a shape obj and add it to the scene.lst_obj
**
** @param app
** @param scene_file
** @param type
*/

void
	parse_shape(t_data *app, t_parse_txt *scene_file, int type)
{
	t_obj		obj;

	if (DEBUG)
		ft_putendl("Shape node :");
	create_obj(&obj, scene_file, type);
	ft_lstpushnew(&app->scene.lst_obj, &obj, sizeof(t_obj));

}

/**
** @brief Built a light obj and add it to the scene.lst_light
**
** @param data
** @param scene_file
*/

void
	parse_light(t_data *app, t_parse_txt *scene_file)
{
	t_light		light;

	if (DEBUG)
		ft_putendl("Light node :");
	check_opening_bracket(scene_file);
	light_set(&light, scene_file);
	ft_lstpushnew(&app->scene.lst_light, &light, sizeof(t_light));
	check_closing_bracket(scene_file);
}
