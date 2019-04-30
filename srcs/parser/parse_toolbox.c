/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_toolbox.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 04:29:28 by nihuynh           #+#    #+#             */
/*   Updated: 2019/04/30 18:44:39 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "libft.h"
#include "rt.h"

/*
** @brief		Parse the color of an object from a string
**
** @param color	Adress of the color to parse
** @param str	String to parse
** @param line	Current line of the parsing
*/

void
	parse_color(t_color *color, char *str, int line, char *key)
{
	float	toby[3];
	int		idx;

	idx = -1;
	if (!str)
		ft_error_wmsg(ERR_PARSE_STRN, line, str);
	str = check_key(str, line, key, ERR_PARSE_COLOR);
	while (++idx < 3)
	{
		toby[idx] = ft_atof(str);
		while (*str && *str != ' ' && *str != ')')
			str++;
		while (*str && *str == ' ' && *str != ')')
			str++;
		if (!*str || *str == ')')
			break;
	}
	if (idx != 3)
		ft_error_wmsg(ERR_PARSE_COLOR, line, str);
	color->r = toby[0];
	color->g = toby[1];
	color->b = toby[2];
	if (DEBUG)
		ft_printf("Color : %i %i %i\n", color->r, color->g, color->b);
}

/*
** @brief Parse a vector from a string
**
** @param vec		Address of the vector to parse
** @param str		String to parse
** @param line		Current line of the parsing
** @param key		Name of the key
*/

void
	parse_vector(t_vec3 *vec, char *str, int line, char *key)
{
	float	toby[3];
	int		idx;

	idx = -1;
	if (!str)
		ft_error_wmsg(ERR_PARSE_STRN, line, str);
	str = check_key(str, line, key, ERR_PARSE_VECTOR);
	while (++idx < 3)
	{
		toby[idx] = ft_atof(str);
		while (*str && *str != ' ' && *str != ')')
			str++;
		while (*str && *str == ' ' && *str != ')')
			str++;
		if (!*str || *str == ')')
			break;
	}
	if (idx != 3)
		ft_error_wmsg(ERR_PARSE_VECTOR, line, str);
	vec->x = toby[0];
	vec->y = toby[1];
	vec->z = toby[2];
	if (DEBUG)
		ft_printf("Vector : %f %f %f\n", vec->x, vec->y, vec->z);
}

/*
** @brief Parse a float value of an object from a string
**
** @param val	Adress of the float value to parse
** @param str	String to parse
** @param line	Current line of the parsing
*/

void
	parse_fval(float *val, char *str, int line, const char *key)
{
	if (!str)
		ft_error_wmsg(ERR_PARSE_STRN, line, str);
	str = check_key(str, line, key, ERR_PARSE_FLOAT);
	*val = ft_atof(str);
	if (DEBUG)
		ft_printf("Float value : %f\n", *val);
}

void
	parse_limit(float *l_x, float *l_y, char *str, int line)
{
	float	toby[2];
	int		idx;

	idx = -1;
	if (!str)
		ft_error_wmsg(ERR_PARSE_STRN, line, str);
	str = check_key(str, line, "limit(", ERR_PARSE_FLOAT);
	while (++idx < 2)
	{
		toby[idx] = ft_atof(str);
		while (*str && *str != ' ' && *str != ')')
			str++;
		while (*str && *str == ' ' && *str != ')')
			str++;
		if (!*str || *str == ')')
			ft_error_wmsg(ERR_PARSE_FLOAT, line, str);
	}
	*l_x = toby[0];
	*l_y = toby[1];
	if (DEBUG)
		ft_printf("Limit : %f %f\n", l_x, l_y);
}
