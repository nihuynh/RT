/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 16:28:57 by sklepper          #+#    #+#             */
/*   Updated: 2019/03/19 17:48:51 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "parse.h"
#include "libft.h"
#include <unistd.h>

/**
 * @brief	Parser for the camera
 *
 * @param greed		Contains the whole input file
 * @param data		General struct for holding data
 * @param line_idx	Line index to navigate in greed
 * @return int		Line on which it finished parsing the camera
 */

int
	parse_camera(char **greed, t_data *data, int line_idx)
{
	if (DEBUG)
		ft_printf("camera at line = %i\n", line_idx);
	if (greed[line_idx + 2] == NULL || greed[line_idx + 3] == NULL)
		parsing_error(line_idx, ERR_PARSE_CONTENT, data, greed);
	parse_origin(&data->cam.pos, greed[line_idx + 2], 3);
	parse_normal(&data->cam.dir, greed[line_idx + 3], 4);
	vec3_find(&data->cam.pos, &data->cam.dir, &data->cam.dir);
	vec3_normalize(&data->cam.dir);
	return (line_idx + 5);
}

/**
 * @brief	Sorting objects in the content section of the input file
 *
 * @param greed		Contains the whole input file
 * @param data		General struct for holding data
 * @param line_idx	Line index to navigate in greed
 * @param line_max	Maximum value for line_idx
 * @return int		Returns the line on which it finished parsing the content
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

/**
 * @brief	First sort between the camera parser and the content parser
 *
 * @param greed		Contains the whole input file
 * @param data		General struct for holding data
 * @param line_max	Maximum value for line_idx
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

void
	split_to_mat(char **split, t_material *mat)
{
	if (!(mat->name = ft_strdup(split[0])))
		ft_error(__func__, __LINE__);
	itocolor(&mat->color_ambient, ft_atoi_base(split[1], 16));
	itocolor(&mat->color_diffuse, ft_atoi_base(split[2], 16));
	itocolor(&mat->color_specular, ft_atoi_base(split[3], 16));
	itocolor(&mat->self_light, ft_atoi_base(split[4], 16));
	mat->spec_idx = ft_atoi(split[5]);
	mat->spec_power = ft_atoi(split[6]);
	mat->absorb_idx = ft_atoi(split[7]);
	mat->deflect_idx = ft_atoi(split[8]);
}


void
	parse_material_csv(t_data *data, char *csv_file)
{
	int			fd;
	char		*line;
	char		**split;
	t_material	node;
	t_list		*lst_node;

	fd = ft_fopen_read(csv_file);
	while (ft_gnl(fd, &line, "\n") > 0)
	{
		if (!(split = ft_strsplit(line, ';')))
			ft_error(__func__, __LINE__);
		if (ft_tablen(split) != 9)
			ft_error(__func__, __LINE__);
		split_to_mat(split, &node);
		if (!(lst_node = ft_lstnew(&node, sizeof(t_material))))
			ft_error(__func__, __LINE__);
		ft_lstadd(&data->lst_mat, lst_node);
		lst_node = NULL;
		ft_tabdel(split);
		ft_strdel(&line);
	}
	close(fd);
}

/**
 * @brief	Reading the input file and beginning parsing
 *
 * @param str	Name of the input file
 * @param data	General struct for holding data
 * @return int	Return 0 if everything went right, 1 otherwise
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
