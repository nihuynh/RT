/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_toolbox.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 16:39:57 by sklepper          #+#    #+#             */
/*   Updated: 2019/06/14 05:56:10 by sklepper         ###   ########.fr       */
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

	ft_bzero(&node, sizeof(t_texture));
	node.name = ft_strdup("none");
	ft_lstpushnew(&app->lst_tex, &node, sizeof(t_texture));
	node.name = ft_strdup("checkers");
	node.f_texture = &texture_checkers;
	ft_lstpushnew(&app->lst_tex, &node, sizeof(t_texture));
	node.name = ft_strdup("strips");
	node.f_texture = &texture_strips;
	ft_lstpushnew(&app->lst_tex, &node, sizeof(t_texture));
}

void
	init_textures(t_data *app)
{
	textures_procedural(app);
	open_textures(app);
	ft_lstsort(&app->lst_tex, &texture_cmp);
}
