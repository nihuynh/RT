/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_toolbox.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 04:29:28 by nihuynh           #+#    #+#             */
/*   Updated: 2019/05/20 22:22:23 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "libft.h"
#include "config.h"
#include "rt.h"

t_color
	parse_color(char *key, t_parse_txt *scene_file)
{
	float	toby[3];
	int		idx;
	char	*line;

	idx = -1;
	line = get_args_key_require(scene_file, key);
	while (++idx < 3)
	{
		toby[idx] = ft_atof(line);
		while (*line && *line != ' ' && *line != ')')
			line++;
		while (*line && *line == ' ' && *line != ')')
			line++;
		if (!*line || *line == ')')
			break ;
	}
	if (idx != 2)
	{
		err_set(scene_file, __func__, __LINE__, __FILE__);
		err_exit(ERR_PARSE_COLOR, scene_file);
	}
	if (DEBUG)
		ft_printf("Color : %f %f %f\n", toby[0], toby[1], toby[2]);
	return ((t_color){toby[0], toby[1], toby[2]});
}

t_vec3
	parse_vector(char *key, t_parse_txt *scene_file)
{
	float	toby[3];
	int		idx;
	char	*line;

	idx = -1;
	line = get_args_key_require(scene_file, key);
	while (++idx < 3)
	{
		toby[idx] = ft_atof(line);
		while (*line && *line != ' ' && *line != ')')
			line++;
		while (*line && *line == ' ' && *line != ')')
			line++;
		if (!*line || *line == ')')
			break ;
	}
	if (idx != 2)
	{
		err_set(scene_file, __func__, __LINE__, __FILE__);
		err_exit(ERR_PARSE_VECTOR, scene_file);
	}
	if (DEBUG)
		ft_printf("Vector : %f %f %f\n", toby[0], toby[1], toby[2]);
	return ((t_vec3){toby[0], toby[1], toby[2]});
}

float
	parse_fval(char *key, t_parse_txt *scene_file)
{
	char	*line;
	float	res;

	line = get_args_key_require(scene_file, key);
	res = ft_atof(line);
	if (DEBUG)
		ft_printf("Float value : %f\n", res);
	return (res);
}

void
	parse_limit(float *l_x, float *l_y, t_parse_txt *scene_file)
{
	float	toby[2];
	int		idx;
	char	*line;

	idx = -1;
	line = get_args_key_require(scene_file, "limit(");
	while (++idx < 2)
	{
		toby[idx] = ft_atof(line);
		while (*line && *line != ' ' && *line != ')')
			line++;
		while (*line && *line == ' ' && *line != ')')
			line++;
		if (!*line || *line == ')')
			break ;
	}
	if (idx != 1)
	{
		err_set(scene_file, __func__, __LINE__, __FILE__);
		err_exit(ERR_PARSE_LIMIT, scene_file);
	}
	*l_x = toby[0];
	*l_y = toby[1];
	if (DEBUG)
		ft_printf("Limit : %f %f\n", toby[0], toby[1]);
}
