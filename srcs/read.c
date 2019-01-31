/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 16:28:57 by sklepper          #+#    #+#             */
/*   Updated: 2018/12/19 17:14:39 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "parse.h"
#include "libft.h"
#include <unistd.h>

int		line_counter(char *str)
{
	int		fd;
	char	*line;
	int		line_count;

	line_count = 0;
	fd = ft_fopen_read(str);
	while (ft_gnl(fd, &line, "\n") > 0)
	{
		line_count++;
		ft_strdel(&line);
	}
	close(fd);
	return (line_count);
}

int		parse_camera(char **greed, t_data *data, int line_idx)
{
	if (DEBUG)
		ft_printf("camera at line = %i\n", line_idx);
	if (greed[line_idx + 2] == NULL || greed[line_idx + 3] == NULL)
		parsing_error(line_idx, ERR_PARSE_CONTENT, data, greed);
	parse_origin(&data->cam.pos, greed[line_idx + 2], 3);
	parse_normal(&data->cam.dir, greed[line_idx + 3], 4);
	return (line_idx + 5);
}

int		parse_content(char **greed, t_data *data, int line_idx, int line_max)
{
	if (greed[++line_idx] == NULL || greed[line_idx][0] != '{')
		parsing_error(line_idx, ERR_P_BRACKET, data, greed);
	line_idx++;
	while (greed[line_idx] && line_idx < line_max)
	{
		if (greed[line_idx][0] == '}')
			return (++line_idx);
		else if (ft_strstr(greed[line_idx], "object(light)") != NULL)
			line_idx = parse_light(greed, data, line_idx);
		else if (ft_strstr(greed[line_idx], "object(plane)") != NULL)
			line_idx = parse_shape(greed, data, line_idx, PLANE);
		else if (ft_strstr(greed[line_idx], "object(sphere)") != NULL)
			line_idx = parse_shape(greed, data, line_idx, SPHERE);
		else if (ft_strstr(greed[line_idx], "object(cylinder)") != NULL)
			line_idx = parse_shape(greed, data, line_idx, CYLINDER);
		else if (ft_strstr(greed[line_idx], "object(cone)") != NULL)
			line_idx = parse_shape(greed, data, line_idx, CONE);
		else
			parsing_error(line_idx, ERR_PARSE_CONTENT, data, greed);
	}
	return (++line_idx);
}

void	parser(char **greed, t_data *data, int line_max)
{
	int line_idx;

	line_idx = 0;
	while (line_idx < line_max)
	{
		if (ft_strstr(greed[line_idx], "content") != NULL)
			line_idx = parse_content(greed, data, line_idx, line_max);
		else if (ft_strstr(greed[line_idx], "camera") != NULL)
			line_idx = parse_camera(greed, data, line_idx);
		else
			parsing_error(line_idx, ERR_PARSE_CONTENT, data, greed);
	}
}

int		reader(char *str, t_data *data)
{
	int		fd;
	int		line_count;
	char	**greed;

	if ((line_count = line_counter(str)) < 9)
		return (EXIT_FAILURE);
	if (!(greed = ft_memalloc(sizeof(char *) * (line_count + 1))))
		return (EXIT_FAILURE);
	fd = ft_fopen_read(str);
	line_count = 0;
	while (ft_gnl(fd, &greed[line_count], "\n") > 0)
		line_count++;
	close(fd);
	if (DEBUG)
		ft_puttab(greed);
	parser(greed, data, line_count);
	ft_tabdel(greed);
	return (EXIT_SUCCESS);
}
