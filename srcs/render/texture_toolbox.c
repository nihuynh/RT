/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_toolbox.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 16:39:57 by sklepper          #+#    #+#             */
/*   Updated: 2019/05/19 16:26:48 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <zconf.h>
#include "rt.h"
#include "config.h"
#include "libft.h"
#include "parse.h"

static inline void
	textures_procedural(t_data *app)
{
	t_texture	node;

	node.pixels = NULL;
	node.name = "none";
	node.f_texture = NULL;
	ft_lstpushnew(&app->lst_tex, &node, sizeof(t_texture));
	node.name = "checkers";
	node.f_texture = &texture_checkers;
	ft_lstpushnew(&app->lst_tex, &node, sizeof(t_texture));
	node.name = "strips";
	node.f_texture = &texture_strips;
	ft_lstpushnew(&app->lst_tex, &node, sizeof(t_texture));
}

void
	init_textures(t_data *app)
{
	textures_procedural(app);
	open_textures(app);
}

t_texture
	create_texture(char *filename)
{
	t_texture	result;
	char		*cleaned_name;

	if (!(result.name = ft_strdup(filename)))
		ft_error(__func__, __LINE__);
	result.name[ft_strlen(result.name) - 1] = '\0';
	if (!(cleaned_name = ft_strdup(TEX_DIR)))
		ft_error(__func__, __LINE__);
	if (!(cleaned_name = ft_strjoinfree(cleaned_name, result.name)))
		ft_error(__func__, __LINE__);
	result.f_texture = &sample;
	result.pixels = load_texture(cleaned_name, &result.width, &result.height);
	ft_strdel(&cleaned_name);
	return (result);
}

