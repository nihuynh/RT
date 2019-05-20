/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 04:18:50 by nihuynh           #+#    #+#             */
/*   Updated: 2019/05/20 14:38:23 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "ftstring.h"

/**
** @brief Verify curr_line is containing the proper value and key.
**
** @param scene_file
** @param key		: key to find
** @return char*	: A pointer to the beginning of the value for the parameter
*/

char
	*get_args_key_require(t_parse_txt *scene_file, const char *key)
{
	char *check_line_args;

	check_line_args = scene_file->pop_line(scene_file);
	if (!(check_line_args = ft_strstr(check_line_args, key)))
	{
		scene_file->err_set(scene_file, __func__, __LINE__, __FILE__);
		scene_file->err_exit(ERR_P_KEY, scene_file);
	}
	check_line_args += ft_strlen(key);
	if (ft_strrchr(check_line_args, ')') == NULL)
	{
		scene_file->err_set(scene_file, __func__, __LINE__, __FILE__);
		scene_file->err_exit(ERR_P_CLOSE_PAR, scene_file);
	}
	return (check_line_args);
}

/**
** @brief Verify that the curr_line is a opening bracket
**
** @param scene_file
*/

void
	check_opening_bracket(t_parse_txt *scene_file)
{
	if (ft_strchr(scene_file->get_curr_line(scene_file), '{') != NULL)
		scene_file->line_idx++;
	else
	{
		scene_file->err_set(scene_file, __func__, __LINE__, __FILE__);
		scene_file->err_exit(ERR_P_BRACKET_OPEN, scene_file);
	}
}

/**
** @brief  Verify that the curr_line is a closing bracket
**
** @param scene_file
*/

void
	check_closing_bracket(t_parse_txt *scene_file)
{
	if (ft_strchr(scene_file->get_curr_line(scene_file), '}') != NULL)
		scene_file->line_idx++;
	else
	{
		scene_file->err_set(scene_file, __func__, __LINE__, __FILE__);
		scene_file->err_exit(ERR_P_BRACKET_CLSE, scene_file);
	}
}

int
	matcmp(void *content, void *key)
{
	t_material	*mat;
	char		*ckey;

	mat = content;
	ckey = key;
	return (!ft_strncasecmp(mat->name, ckey, ft_strlen(mat->name)));
}

int
	texcmp(void *content, void *key)
{
	t_texture	*tex;
	char		*ckey;

	tex = content;
	ckey = key;
	return (!ft_strncasecmp(tex->name, ckey, ft_strlen(tex->name)));
}
