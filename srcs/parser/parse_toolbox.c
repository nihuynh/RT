/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_toolbox.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 04:29:28 by nihuynh           #+#    #+#             */
/*   Updated: 2019/05/14 22:02:20 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "libft.h"
#include "config.h"
#include "rt.h"

/*
** @brief		Parse the color of an object from a string
**
** @param color		Adress of the color to parse
** @param lines		Array of all lines
** @param line_idx	Current line of the parsing
** @param key		Name of the key
*/

void
	parse_color(t_color *color, char **lines, int line_idx, char *key)
{
	float	toby[3];
	int		idx;
	char	*line;

	idx = -1;
	line = lines[line_idx];
	if (!line)
		ft_error_wmsg(ERR_PARSE_STRN, line_idx, line);
	line = check_key(line, line_idx, key, ERR_PARSE_COLOR);
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
		ft_error_wmsg(ERR_PARSE_COLOR, line_idx, line);
	*color = (t_color){toby[0], toby[1], toby[2]};
	if (DEBUG)
		ft_printf("Color : %i %i %i\n", color->r, color->g, color->b);
}

/*
** @brief Parse a vector from a string
**
** @param vec		Address of the vector to parse
** @param lines		Array of all lines
** @param line_idx	Current line of the parsing
** @param key		Name of the key
*/

void
	parse_vector(t_vec3 *vec, char **lines, int line_idx, char *key)
{
	float	toby[3];
	int		idx;
	char	*line;

	idx = -1;
	line = lines[line_idx];
	if (!line)
		ft_error_wmsg(ERR_PARSE_STRN, line_idx, line);
	line = check_key(line, line_idx, key, ERR_PARSE_VECTOR);
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
		ft_error_wmsg(ERR_PARSE_VECTOR, line_idx, line);
	*vec = (t_vec3){toby[0], toby[1], toby[2]};
	if (DEBUG)
		ft_printf("Vector : %f %f %f\n", vec->x, vec->y, vec->z);
}

/*
** @brief Parse a float value of an object from a string
**
** @param val	Adress of the float value to parse
** @param lines		Array of all lines
** @param line_idx	Current line of the parsing
** @param key		Name of the key
*/

void
	parse_fval(float *val, char **lines, int line_idx, const char *key)
{
	char	*line;

	line = lines[line_idx];
	if (!line)
		ft_error_wmsg(ERR_PARSE_STRN, line_idx, line);
	line = check_key(line, line_idx, key, ERR_PARSE_FLOAT);
	*val = ft_atof(line);
	if (DEBUG)
		ft_printf("Float value : %f\n", *val);
}

void
	parse_limit(float *l_x, float *l_y, char **lines, int line_idx)
{
	float	toby[2];
	int		idx;
	char	*line;

	idx = -1;
	line = lines[line_idx];
	if (!line)
		ft_error_wmsg(ERR_PARSE_STRN, line_idx, line);
	line = check_key(line, line_idx, "limit(", ERR_PARSE_FLOAT);
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
		ft_error_wmsg(ERR_PARSE_FLOAT, line_idx, line);
	*l_x = toby[0];
	*l_y = toby[1];
	if (DEBUG)
		ft_printf("Limit : %f %f\n", l_x, l_y);
}
