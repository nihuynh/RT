/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_toolbox.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 16:39:57 by sklepper          #+#    #+#             */
/*   Updated: 2019/05/20 11:24:18 by sklepper         ###   ########.fr       */
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
