/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_toolbox.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 04:29:28 by nihuynh           #+#    #+#             */
/*   Updated: 2019/03/19 15:59:06 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "libft.h"
#include "rt.h"

/**
** @brief			Verify if a line is containing the proper value and key.
**
** @param str 		String to check
** @param line		Current line of parsing
** @param key		Parameter to find
** @param err		Error to send if the parameter is not found
** @return char*	A pointer to the beginning of the value for the parameter
*/

static inline char
	*check_key(char *str, int line, const char *key, char *err)
{
	if (!(str = ft_strstr(str, key)))
		ft_error_wmsg(ERR_P_KEY, line, str);
	str += ft_strlen(key);
	if (!*str)
		ft_error_wmsg(err, line, str);
	if (ft_strrchr(str, ')') == NULL)
		ft_error_wmsg(ERR_P_CLOSE_PAR, line, str);
	return (str);
}

/**
** @brief		Parse the color of an object from a string
**
** @param color	Adress of the color to parse
** @param str	String to parse
** @param line	Current line of the parsing
*/

void
	parse_color(t_color *color, char *str, int line, char *key)
{
	uint8_t toby[3];
	int		idx;

	idx = -1;
	if (!str)
		ft_error_wmsg(ERR_PARSE_STRN, line, str);
	str = check_key(str, line, key, ERR_PARSE_COLOR);
	while (++idx < 3)
	{
		toby[idx] = (uint8_t)ft_clamp(ft_atoi(str), 0, 255);
		while (*str && *str != ' ' && *str != ')')
			str++;
		while (*str && *str == ' ' && *str != ')')
			str++;
		if (!*str)
			ft_error_wmsg(ERR_PARSE_COLOR, line, str);
	}
	if (idx != 3 && ((*str >= '9' && *str <= '9') || *str == '-'))
		ft_error_wmsg(ERR_PARSE_COLOR, line, str);
	color->r = toby[0];
	color->g = toby[1];
	color->b = toby[2];
	if (DEBUG)
		ft_printf("Color : %i %i %i\n", color->r, color->g, color->b);
}

/**
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
		if (!*str)
			ft_error_wmsg(ERR_PARSE_VECTOR, line, str);
	}
	if (idx != 3 && ((*str >= '9' && *str <= '9') || *str == '-'))
		ft_error_wmsg(ERR_PARSE_VECTOR, line, str);
	vec->x = toby[0];
	vec->y = toby[1];
	vec->z = toby[2];
	if (DEBUG)
		ft_printf("Vector : %f %f %f\n", vec->x, vec->y, vec->z);
}

/**
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
		if (!*str)
			ft_error_wmsg(ERR_PARSE_FLOAT, line, str);
	}
	*l_x = toby[0];
	*l_y = toby[1];
	if (DEBUG)
		ft_printf("Limit : %f %f\n", l_x, l_y);
}

void
	parse_texture(t_plane *plane, char *str, int line)
{
	char *ptr;

	if (!str)
		ft_error_wmsg(ERR_PARSE_STRN, line, str);
	str = check_key(str, line, "texture(", ERR_PARSE_VECTOR);
	if ((ptr = ft_strstr(str, "checkers")))
		plane->f_texture = &texture_checkers;
	else if ((ptr = ft_strstr(str, "strips")))
		plane->f_texture = &texture_strips;
	else
		plane->f_texture = NULL;
}
