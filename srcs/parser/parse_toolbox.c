/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_toolbox.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 04:29:28 by nihuynh           #+#    #+#             */
/*   Updated: 2019/05/19 06:35:21 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "libft.h"
#include "config.h"
#include "rt.h"

void
	parse_color(t_color *color, char *key, t_parse_txt *scene_file)
{
	float	toby[3];
	int		idx;
	char	*line;

	idx = -1;
	line = check_key(scene_file, key);
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
		scene_file->err_set(scene_file, __func__, __LINE__, __FILE__);
		scene_file->err_exit(ERR_PARSE_COLOR, scene_file);
	}
	*color = (t_color){toby[0], toby[1], toby[2]};
	if (DEBUG)
		ft_printf("Color : %i %i %i\n", color->r, color->g, color->b);
}

void
	parse_vector(t_vec3 *vec, char *key, t_parse_txt *scene_file)
{
	float	toby[3];
	int		idx;
	char	*line;

	idx = -1;
	line = check_key(scene_file, key);
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
		scene_file->err_set(scene_file, __func__, __LINE__, __FILE__);
		scene_file->err_exit(ERR_PARSE_VECTOR, scene_file);
	}
	*vec = (t_vec3){toby[0], toby[1], toby[2]};
	if (DEBUG)
		ft_printf("Vector : %f %f %f\n", vec->x, vec->y, vec->z);
}

void
	parse_fval(float *val, char *key, t_parse_txt *scene_file)
{
	char	*line;

	line = check_key(scene_file, key);
	*val = ft_atof(line);
	if (DEBUG)
		ft_printf("Float value : %f\n", *val);
}

void
	parse_limit(float *l_x, float *l_y, t_parse_txt *scene_file)
{
	float	toby[2];
	int		idx;
	char	*line;

	idx = -1;
	line = check_key(scene_file, "limit(");
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
		scene_file->err_set(scene_file, __func__, __LINE__, __FILE__);
		scene_file->err_exit(ERR_PARSE_LIMIT, scene_file);
	}
	*l_x = toby[0];
	*l_y = toby[1];
	if (DEBUG)
		ft_printf("Limit : %f %f\n", l_x, l_y);
}
