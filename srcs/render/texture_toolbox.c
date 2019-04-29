/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_toolbox.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 16:39:57 by sklepper          #+#    #+#             */
/*   Updated: 2019/04/29 19:17:56 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	t_list		*lst_node;

	node.pixels = NULL;
	node.name = "none";
	node.f_texture = NULL;
	if (!(lst_node = ft_lstnew(&node, sizeof(t_texture))))
		ft_error(__func__, __LINE__);
	ft_lstadd(&app->lst_tex, lst_node);
	node.name = "checkers";
	node.f_texture = &texture_checkers;
	if (!(lst_node = ft_lstnew(&node, sizeof(t_texture))))
		ft_error(__func__, __LINE__);
	ft_lstadd(&app->lst_tex, lst_node);
	node.name = "strips";
	node.f_texture = &texture_strips;
	if (!(lst_node = ft_lstnew(&node, sizeof(t_texture))))
		ft_error(__func__, __LINE__);
	ft_lstadd(&app->lst_tex, lst_node);
}

void
	init_textures(t_data *app)
{
	textures_procedural(app);
}

t_texture
	*parse_texture(t_list *lst_tex, char *str, int line)
{
	t_texture	*tex;

	tex = NULL;
	if (!str)
		ft_error_wmsg(ERR_PARSE_STRN, line, str);
	if ((str = ft_strstr(str, "texture(")))
	{
		str += 8;
		if (!(tex = ft_lstgetelt(lst_tex, &texcmp, str)))
			tex = ft_lstgetelt(lst_tex, &texcmp, "none");
	}
	return (tex);
}
