/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 16:28:57 by tdarchiv          #+#    #+#             */
/*   Updated: 2019/05/19 03:50:57 by nihuynh          ###   ########.fr       */
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
	parse_vector(&app->cam.pos, scene_file->greed, scene_file->line_idx++, "origin(");
	parse_vector(&app->cam.dir, scene_file->greed, scene_file->line_idx++, "direction(");
	parse_color(&app->settings.amb_light, scene_file->greed, scene_file->line_idx++, "amb_light(");
	vec3_normalize(&app->cam.dir);
}

int
	parse_obj(t_data *app, t_parse_txt *scene_file)
{
	char	*type_tested;
	int		type;

	type = -1;
	type_tested = NULL;
	if (ft_strrchr(scene_file->get_curr_line(scene_file),'}') != NULL)
		return (EXIT_SUCCESS);
	while ((type_tested = get_obj_str(++type)))
	{
		if (ft_strstr(scene_file->get_curr_line(scene_file), type_tested))
		{
			parse_shape(app, scene_file, type);
			return (EXIT_SUCCESS);
		}
	}
	return (EXIT_FAILURE);
}

char
	*check_if_obj(t_parse_txt *scene_file, char *err_msg)
{
	char *res;

	res = check_key(scene_file->get_curr_line(scene_file),
					scene_file->line_idx, "object(", err_msg);
	return (res);
}

void
	parse_content(t_data *data, t_parse_txt *scene_file)
{
	char	*obj_type;

	while (scene_file->line_idx < scene_file->line_max - 1)
	{
		if (ft_strrchr(scene_file->get_curr_line(scene_file),'}') != NULL)
			break ;
		obj_type = check_if_obj(scene_file, ERR_P_CONTENT);
		if (ft_strstr(obj_type, "light") != NULL)
			parse_light(data, scene_file);
		else if (parse_obj(data, scene_file))
		{
			scene_file->err_set(scene_file, __func__, __LINE__, __FILE__);
			scene_file->err_exit(ERR_P_CONTENT, scene_file);
		}
	}
}

void
	parser(t_data *data, t_parse_txt *scene_file)
{
	if (ft_strstr(scene_file->get_curr_line(scene_file), "camera"))
	{
		scene_file->line_idx += 2;
		parse_camera(data, scene_file);
		scene_file->line_idx++;
	}
	else
	{
		scene_file->err_set(scene_file, __func__, __LINE__, __FILE__);
		scene_file->err_exit("camera missing", scene_file);
	}
	if (ft_strstr(scene_file->get_curr_line(scene_file), "content"))
	{
		scene_file->line_idx += 2;
		parse_content(data, scene_file);
	}
	else
	{
		scene_file->err_set(scene_file, __func__, __LINE__, __FILE__);
		scene_file->err_exit("content missing", scene_file);
	}
}

int
	reader(char *filename, t_data *data)
{
	t_parse_txt	scene_file;

	if (load_parse_txt(&scene_file, filename))
	{
		scene_file.err_set(&scene_file, __func__, __LINE__, __FILE__);
		scene_file.err_exit(ERR_FILE, &scene_file);
	}
	if (DEBUG)
		ft_puttab(scene_file.greed);
	parser(data, &scene_file);
	ft_lstrev(&data->scene.lst_light);
	ft_lstrev(&data->scene.lst_obj);
	ft_tabdel(scene_file.greed);
	return (EXIT_SUCCESS);
}
