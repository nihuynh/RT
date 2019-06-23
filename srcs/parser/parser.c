/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 10:12:22 by sklepper          #+#    #+#             */
/*   Updated: 2019/06/23 14:57:28 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"
#include "libft.h"
#include "parse.h"

/**
** @brief Built a light obj and add it to the scene.lst_light
**
** @param scene_file	: Parsing struct
*/

void
	parse_light(t_parse_txt *scene_file)
{
	t_light		light;

	check_opening_bracket(scene_file);
	if (DEBUG)
		ft_putendl("Light node :");
	light_set(&light, scene_file);
	light.name = name_obj(-1, &scene_file->app->scene.nb_light);
	ft_lstpushnew(&scene_file->app->scene.lst_light, &light, sizeof(t_light));
	check_closing_bracket(scene_file);
}

char
	*parse_str(t_parse_txt *scene_file, char *key)
{
	char	*line;
	char	*name;
	size_t	n;

	if (!(line = get_args_after_key(scene_file, key)))
		return (NULL);
	n = ft_strclen(line, ')');
	if (!(name = ft_strndup(line, n)))
		ft_error(__func__, __LINE__);
	return (name);
}
