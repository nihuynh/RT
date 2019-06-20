/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_shape.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 01:04:29 by nihuynh           #+#    #+#             */
/*   Updated: 2019/06/20 20:05:15 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"
#include "libft.h"
#include "parse.h"

static inline t_texture
	*parse_texture(char *key_name, t_parse_txt *scene_file)
{
	t_texture	*tex;
	char		*line;

	line = get_args_after_key(scene_file, key_name);
	if (line == NULL)
		return (ft_lstgetelt(scene_file->app->lst_tex, &texcmp, "none"));
	tex = ft_lstgetelt(scene_file->app->lst_tex, &texcmp, line);
	if (tex == NULL)
		return (ft_lstgetelt(scene_file->app->lst_tex, &texcmp, "none"));
	if (!(tex->pixels))
		load_texture(tex);
	return (tex);
}

static inline t_material
	expand_parse(t_parse_txt *scene_file, t_material mat)
{
	mat.name = "custom";
	mat.color_diffuse = parse_color("color_diffuse(", scene_file);
	mat.color_specular = parse_color("color_specular(", scene_file);
	mat.color_tex = parse_color("color_tex(", scene_file);
	mat.spec_idx = parse_fval("spec_idx(", scene_file);
	mat.spec_power = parse_fval("spec_power(", scene_file);
	mat.refraction_color = parse_color("refraction_color(", scene_file);
	mat.reflection_color = parse_color("reflection_color(", scene_file);
	mat.refraction_idx = parse_fval("refraction_idx(", scene_file);
	mat.uv_mapping.scale = parse_vec2("uv_scale(", scene_file);
	mat.uv_mapping.offset = parse_vec2("uv_offset(", scene_file);
	mat.uv_mapping.repeat = true;
	return (mat);
}

static inline t_material
	parse_material(t_parse_txt *scene_file)
{
	t_material	res;
	char		*str;
	t_material	*mat;

	ft_bzero(&res, sizeof(t_material));
	res.tex = parse_texture("texture(", scene_file);
	res.normal_map = parse_texture("normal_map(", scene_file);
	res.spec_map = parse_texture("spec_map(", scene_file);
	if ((str = ft_strstr(get_curr_line(scene_file), "mat(")))
	{
		str += 4;
		if (!(mat = ft_lstgetelt(scene_file->app->lst_mat, &matcmp, str)))
		{
			err_set(scene_file, __func__, __LINE__, __FILE__);
			err_exit(ERR_UNKNWD_MAT, scene_file);
		}
		scene_file->line_idx++;
		return (*mat);
	}
	return (expand_parse(scene_file, res));
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
	obj_set(obj_dst, type);
	init_parse_cfg(type, &cfg);
	if (DEBUG)
		ft_putendl(cfg.printout);
	if (!(shape = malloc(cfg.content_size)))
		ft_error(__func__, __LINE__);
	obj_dst->name = parse_str(scene_file, "name(");
	cfg.setter(obj_dst, shape, scene_file);
	obj_dst->shape = shape;
	if (!obj_dst->name)
		obj_dst->name = name_obj(type, &scene_file->app->scene.nb_objs[type]);
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
