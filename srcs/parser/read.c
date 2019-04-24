/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 16:28:57 by tdarchiv          #+#    #+#             */
/*   Updated: 2019/04/24 15:31:28 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "parse.h"
#include "libft.h"
#include <unistd.h>

/*
** @brief	Parser for the camera
**
** @param greed		Contains the whole input file
** @param data		General struct for holding data
** @param line_idx	Line index to navigate in greed
** @return int		Line on which it finished parsing the camera
*/

int
	parse_camera(char **greed, t_data *data, int line_idx)
{
	if (DEBUG)
		ft_printf("camera at line = %i\n", line_idx);
	if (greed[line_idx + 2] == NULL || greed[line_idx + 3] == NULL)
		parsing_error(line_idx, ERR_PARSE_CONTENT, data, greed);
	parse_vector(&data->cam.pos, greed[line_idx + 2], 3, "origin(");
	parse_vector(&data->cam.dir, greed[line_idx + 3], 4, "direction(");
	vec3_normalize(&data->cam.dir);
	return (line_idx + 5);
}

/*
** @brief	Sorting objects in the content section of the input file
**
** @param greed		Contains the whole input file
** @param data		General struct for holding data
** @param line_idx	Line index to navigate in greed
** @param line_max	Maximum value for line_idx
** @return int		Returns the line on which it finished parsing the content
*/

int
	parse_content(char **greed, t_data *data, int line_idx, int line_max)
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

/*
** @brief	First sort between the camera parser and the content parser
**
** @param greed		Contains the whole input file
** @param data		General struct for holding data
** @param line_max	Maximum value for line_idx
*/

void
	parser(char **greed, t_data *data, int line_max)
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

/*
** @brief	Reading the input file and beginning parsing
**
** @param str	Name of the input file
** @param data	General struct for holding data
** @return int	Return 0 if everything went right, 1 otherwise
*/

int
	reader(char *str, t_data *data)
{
	int		fd;
	int		line_count;
	char	**greed;

	parse_material_csv(data, "materialList.csv");
	if ((line_count = ft_line_count(str)) < 9)
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
