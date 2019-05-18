/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 16:28:57 by tdarchiv          #+#    #+#             */
/*   Updated: 2019/05/18 04:00:05 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "config.h"
#include "parse.h"
#include "libft.h"
#include <unistd.h>

/**
** @brief	Parser for the camera
**
** @param greed		Contains the whole input file
** @param data		General struct for holding data
** @param line_idx	Line index to navigate in greed
** @return int		Line on which it finished parsing the camera
*/

void
	parse_camera(t_data *data, t_parse_txt *scene_file)
{
	parse_vector(&data->cam.pos, scene_file->greed, scene_file->line_idx++, "origin(");
	parse_vector(&data->cam.dir, scene_file->greed, scene_file->line_idx++, "direction(");
	parse_color(&data->settings.amb_light, scene_file->greed, scene_file->line_idx++, "amb_light(");
	vec3_normalize(&data->cam.dir);
}


int
	parse_obj(t_data *app, t_parse_txt *scene_file)
{
	char	*type_tested;
	int		type;

	type = -1;
	type_tested = NULL;
	while ((type_tested = get_obj_str(++type)))
	{
		if (ft_strstr(scene_file->greed[scene_file->line_idx], type_tested))
		{
			parse_shape(app, scene_file, type);
			return (EXIT_SUCCESS);
		}
	}
	return (EXIT_FAILURE);
}



/**
** @brief	Sorting objects in the content section of the input file
**
** @param greed		Contains the whole input file
** @param data		General struct for holding data
** @param line_idx	Line index to navigate in greed
** @param line_max	Maximum value for line_idx
** @return int		Returns the line on which it finished parsing the content
*/

char
	*check_if_obj(t_parse_txt *scene_file, char *err_msg)
{
	char *res;

	res = check_key(scene_file->greed[scene_file->line_idx],
					scene_file->line_idx, "object(", err_msg);
	return (res);
}

void
	parse_content(t_data *data, t_parse_txt *scene_file)
{
	char	*obj_type;

	while (scene_file->line_idx + 2 < scene_file->line_max)
	{
		obj_type = check_if_obj(scene_file, ERR_P_CONTENT);
		if (ft_strstr(obj_type, "light") != NULL)
			parse_light(data, scene_file);
		else if (parse_obj(data, scene_file))
			parsing_error(ERR_P_CONTENT, scene_file, __func__, __LINE__);
		if (ft_strstr(scene_file->greed[scene_file->line_idx], "}") != NULL)
			scene_file->line_idx++;
	}
}

/**
** @brief	First sort between the camera parser and the content parser
**
** @param greed		Contains the whole input file
** @param data		General struct for holding data
** @param line_max	Maximum value for line_idx
*/

void
	parser(t_data *data, t_parse_txt *scene_file)
{
	if (ft_strstr(scene_file->greed[scene_file->line_idx], "camera"))
	{
		scene_file->line_idx += 2;
		parse_camera(data, scene_file);
		scene_file->line_idx++;
	}
	if (ft_strstr(scene_file->greed[scene_file->line_idx], "content"))
	{
		scene_file->line_idx += 2;
		parse_content(data, scene_file);
	}
	else
		parsing_error(ERR_P_CONTENT, scene_file, __func__, __LINE__);
}

/**
** @brief	Reading the input file and beginning parsing
**
** @param str	Name of the input file
** @param data	General struct for holding data
** @return int	Return 0 if everything went right, 1 otherwise
*/

char			*safe_line(t_parse_txt *scene_file)
{
	if (ft_btw(scene_file->line_idx, 0, scene_file->line_max))
		parsing_error("line_idx out of range", scene_file, __func__, __LINE__);
	if (!(scene_file->greed[scene_file->line_idx]))
		parsing_error("String null", scene_file, __func__, __LINE__);
	return (scene_file->greed[scene_file->line_idx]);
}

int
	reader(char *str, t_data *data)
{
	int			fd;
	t_parse_txt	scene_file;

	if ((scene_file.line_max = ft_line_count(str)) < 9)
		return (EXIT_FAILURE);
	if (!(scene_file.greed = ft_memalloc(sizeof(char *) * (scene_file.line_max + 1))))
		return (EXIT_FAILURE);
	fd = ft_fopen_read(str);
	scene_file.line_idx = 0;
	while (ft_gnl(fd, &scene_file.greed[scene_file.line_idx], "\n") > 0)
		scene_file.line_idx++;
	close(fd);
	scene_file.line_idx = 0;
	scene_file.get_curr_line = &safe_line;
	if (DEBUG)
		ft_puttab(scene_file.greed);
	parser(data, &scene_file);
	ft_lstrev(&data->scene.lst_light);
	ft_lstrev(&data->scene.lst_obj);
	ft_tabdel(scene_file.greed);
	return (EXIT_SUCCESS);
}
