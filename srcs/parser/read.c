/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 16:28:57 by tdarchiv          #+#    #+#             */
/*   Updated: 2019/05/19 07:28:59 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "config.h"
#include "parse.h"
#include "libft.h"

/**
** @brief 	Parser for the camera
**
** @param app 			General struct for holding data
** @param scene_file	Contains the whole input file & idx
*/

void
	parse_camera(t_data *app, t_parse_txt *scene_file)
{
	scene_file->line_idx++;
	check_opening_bracket(scene_file);
	parse_vector(&app->cam.pos, "origin(", scene_file);
	parse_vector(&app->cam.dir, "direction(", scene_file);
	parse_color(&app->settings.amb_light, "amb_light(", scene_file);
	vec3_normalize(&app->cam.dir);
	check_closing_bracket(scene_file);
}

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

void
	parse_content(t_data *app, t_parse_txt *scene_file)
{
	char	*obj_type;
	int		type;

	scene_file->line_idx++;
	check_opening_bracket(scene_file);
	while (scene_file->line_idx < scene_file->line_max - 1)
	{
		if (ft_strrchr(scene_file->get_curr_line(scene_file),'}') != NULL)
			break ;
		obj_type = check_key(scene_file, "object(");
		if (ft_strstr(obj_type, "light") != NULL)
			parse_light(app, scene_file);
		else if ((type = get_obj_type(obj_type)) >= 0)
			parse_shape(app, scene_file, type);
		else
		{
			scene_file->err_set(scene_file, __func__, __LINE__, __FILE__);
			scene_file->err_exit(ERR_UNKNWD_OBJ, scene_file);
		}
	}
	check_closing_bracket(scene_file);
}

void
	parser(t_data *app, t_parse_txt *scene_file)
{
	if (ft_strstr(scene_file->get_curr_line(scene_file), "camera"))
		parse_camera(app, scene_file);
	else
	{
		scene_file->err_set(scene_file, __func__, __LINE__, __FILE__);
		scene_file->err_exit(ERR_P_CAMERA, scene_file);
	}
	if (ft_strstr(scene_file->get_curr_line(scene_file), "content"))
		parse_content(app, scene_file);
	else
	{
		scene_file->err_set(scene_file, __func__, __LINE__, __FILE__);
		scene_file->err_exit(ERR_P_CONTENT, scene_file);
	}
}

int
	reader(char *filename, t_data *app)
{
	t_parse_txt	scene_file;

	if (load_parse_txt(&scene_file, filename))
	{
		scene_file.err_set(&scene_file, __func__, __LINE__, __FILE__);
		scene_file.err_exit(ERR_FILE, &scene_file);
	}
	if (DEBUG)
		ft_puttab(scene_file.greed);
	parser(app, &scene_file);
	ft_lstrev(&app->scene.lst_light);
	ft_lstrev(&app->scene.lst_obj);
	ft_tabdel(scene_file.greed);
	return (EXIT_SUCCESS);
}
