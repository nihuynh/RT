/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 16:28:57 by tdarchiv          #+#    #+#             */
/*   Updated: 2019/05/20 13:52:04 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "librt.h"
#include "config.h"
#include "parse.h"
#include "libft.h"

static inline void
	parse_camera(t_parse_txt *scene_file)
{
	scene_file->line_idx++;
	check_opening_bracket(scene_file);
	parse_vector(&scene_file->app->cam.pos, "origin(", scene_file);
	parse_vector(&scene_file->app->cam.dir, "direction(", scene_file);
	parse_color(&scene_file->app->settings.amb_light, "amb_light(", scene_file);
	vec3_normalize(&scene_file->app->cam.dir);
	check_closing_bracket(scene_file);
}

static inline void
	parse_content(t_parse_txt *scene_file)
{
	char	*obj_type;
	int		type;

	scene_file->line_idx++;
	check_opening_bracket(scene_file);
	while (scene_file->line_idx < scene_file->line_max - 1)
	{
		if (ft_strrchr(scene_file->get_curr_line(scene_file), '}') != NULL)
			break ;
		obj_type = get_args_key_require(scene_file, "object(");
		if (ft_strstr(obj_type, "light") != NULL)
			parse_light(scene_file);
		else if ((type = get_obj_type(obj_type)) >= 0)
			parse_shape(scene_file, type);
		else
		{
			scene_file->err_set(scene_file, __func__, __LINE__, __FILE__);
			scene_file->err_exit(ERR_UNKNWD_OBJ, scene_file);
		}
	}
	check_closing_bracket(scene_file);
}

/*
** @brief 	:  Parse the camera & the content
**
** @param scene_file	: data in txt to parse
*/

static inline void
	parser(t_parse_txt *scene_file)
{
	if (ft_strstr(scene_file->get_curr_line(scene_file), "camera"))
		parse_camera(scene_file);
	else
	{
		scene_file->err_set(scene_file, __func__, __LINE__, __FILE__);
		scene_file->err_exit(ERR_P_CAMERA, scene_file);
	}
	if (ft_strstr(scene_file->get_curr_line(scene_file), "content"))
		parse_content(scene_file);
	else
	{
		scene_file->err_set(scene_file, __func__, __LINE__, __FILE__);
		scene_file->err_exit(ERR_P_CONTENT, scene_file);
	}
}

/*
** @brief	: Top function to organise the parsing
**
** @param filename	: file to parse
** @param app		: link to the data
** @return int		: status of the function
*/

int
	reader(char *filename, t_data *app)
{
	t_parse_txt	scene_file;

	if (load_parse_txt(&scene_file, app, filename))
	{
		scene_file.err_set(&scene_file, __func__, __LINE__, __FILE__);
		scene_file.err_exit(ERR_FILE, &scene_file);
	}
	if (DEBUG)
		ft_puttab(scene_file.greed);
	parser(&scene_file);
	ft_tabdel(scene_file.greed);
	if (DEBUG)
		ft_printf("parse_txt deallocated. line_idx = %d / %d\n",
			scene_file.line_idx, scene_file.line_max);
	ft_lstrev(&app->scene.lst_light);
	ft_lstrev(&app->scene.lst_obj);
	return (EXIT_SUCCESS);
}
