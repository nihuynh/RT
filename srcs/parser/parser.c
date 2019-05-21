/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 10:12:22 by sklepper          #+#    #+#             */
/*   Updated: 2019/05/21 03:18:23 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"
#include "libft.h"
#include "parse.h"

static inline t_texture
	*parse_texture(t_parse_txt *scene_file)
{
	t_texture	*tex;
	char		*line;

	line = get_args_key_require(scene_file, "texture(");
	tex = ft_lstgetelt(scene_file->app->lst_tex, &texcmp, line);
	if (tex == NULL)
		return (ft_lstgetelt(scene_file->app->lst_tex, &texcmp, "none"));
	if (!(tex->pixels))
		tex->pixels = load_texture(tex);
	return (tex);
}

static inline t_material
	parse_material(t_parse_txt *scene_file)
{
	char		*str;
	t_material	mat;
	t_material	*mat_from_lst;

	if ((str = ft_strstr(get_curr_line(scene_file), "mat(")))
	{
		str += 4;
		if (!(mat_from_lst = ft_lstgetelt(scene_file->app->lst_mat, &matcmp, str)))
		{
			err_set(scene_file, __func__, __LINE__, __FILE__);
			err_exit(ERR_UNKNWD_MAT, scene_file);
		}
		scene_file->line_idx++;
		return (*mat_from_lst);
	}
	ft_bzero(&mat, sizeof(t_material));
	mat.name = "";
	mat.tex = parse_texture(scene_file);
	mat.color_diffuse = parse_color("color_diffuse(", scene_file);
	mat.color_specular = parse_color("color_specular(", scene_file);
	mat.color_tex = parse_color("color_tex(", scene_file);
	mat.spec_idx = parse_fval("spec_idx(", scene_file);
	mat.spec_power = parse_fval("spec_power(", scene_file);
	mat.refraction_color = parse_color("refraction_color(", scene_file);
	mat.reflection_color = parse_color("reflection_color(", scene_file);
	mat.refraction_idx = parse_fval("refraction_idx(", scene_file);
	return (mat);
}

/**
** @brief	General parser for all of the shapes
**
** @param obj_dst		: Dst of the data
** @param scene_file	: Parsing struct
** @param type			: Type of the shape to parse
*/

void
	create_obj_from_txt(t_obj *obj_dst, t_parse_txt *scene_file, int type)
{
	t_parse		cfg;
	void		*shape;

	check_opening_bracket(scene_file);
	init_parse_cfg(type, &cfg);
	if (DEBUG)
		ft_putendl(cfg.printout);
	if (!(shape = malloc(cfg.content_size)))
		ft_error(__func__, __LINE__);
	cfg.setter(shape, scene_file);
	obj_set(obj_dst, type, shape);
	obj_dst->export = cfg.export;
	obj_dst->material = parse_material(scene_file);
	check_closing_bracket(scene_file);
}

/**
** @brief Built a shape obj and add it to the scene.lst_obj
**
** @param scene_file	: Parsing struct
** @param type			: Type of the shape to parse
*/

void
	parse_shape(t_parse_txt *scene_file, int type)
{
	t_obj		obj;

	if (DEBUG)
		ft_putendl("Shape node :");
	create_obj_from_txt(&obj, scene_file, type);
	ft_lstpushnew(&scene_file->app->scene.lst_obj, &obj, sizeof(t_obj));

}

/**
** @brief Built a light obj and add it to the scene.lst_light
**
** @param scene_file	: Parsing struct
*/

void
	parse_light(t_parse_txt *scene_file)
{
	t_light		light;

	check_opening_bracket(scene_file);
	if (DEBUG)
		ft_putendl("Light node :");
	light_set(&light, scene_file);
	ft_lstpushnew(&scene_file->app->scene.lst_light, &light, sizeof(t_light));
	check_closing_bracket(scene_file);
}
