/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_toolbox.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 16:39:57 by sklepper          #+#    #+#             */
/*   Updated: 2019/05/12 07:56:03 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <zconf.h>
#include "rt.h"
#include "libft.h"
#include "parse.h"

int
	texcmp(void *content, void *key)
{
	t_texture	*tex;
	char		*ckey;

	tex = content;
	ckey = key;
	return (!ft_strncasecmp(tex->name, ckey, ft_strlen(tex->name)));
}

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
}

t_texture
	create_texture(char *filename)
{
	t_texture	result;
	char		*cleaned_name;

	cleaned_name = ft_strdup(filename);
	cleaned_name[ft_strlen(cleaned_name) - 1] = '\0';
	result.f_texture = &sample;
	result.name = cleaned_name;
	result.pixels = load_texture(cleaned_name, &result.width, &result.height);
	return (result);
}

t_texture
	*parse_texture(t_list **lst_tex, char **lines, int line_idx)
{
	t_texture	*tex;
	t_texture	new_tex;
	char		*line;

	line = lines[line_idx];
	if (!line)
		ft_error_wmsg(ERR_PARSE_STRN, line_idx, line);
	if (!(line = ft_strstr(line, "texture(")))
		return (NULL);
	line += 8;
	tex = ft_lstgetelt(*lst_tex, &texcmp, line);
	if (tex == NULL)
	{
		if (ft_strstr(line, ".ppm"))
		{
			new_tex = create_texture(line);
			ft_lstpushnew(lst_tex, &new_tex, sizeof(t_texture));
			return (ft_lstgetelt(*lst_tex, &texcmp, line));
		}
		else
			return (ft_lstgetelt(*lst_tex, &texcmp, "none"));
	}
	return (tex);
}
