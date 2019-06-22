/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_toolbox.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 16:39:57 by sklepper          #+#    #+#             */
/*   Updated: 2019/06/22 18:40:09 by nihuynh          ###   ########.fr       */
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
	node.name = ft_strdup("wave");
	node.f_texture = &texture_wave;
	ft_lstpushnew(&app->lst_tex, &node, sizeof(t_texture));
	node.name = ft_strdup("perlin");
	node.f_texture = &texture_perlin;
	ft_lstpushnew(&app->lst_tex, &node, sizeof(t_texture));
}

void
	init_textures(t_data *app)
{
	open_textures(app);
	ft_lstsort(&app->lst_tex, &texture_cmp);
	textures_procedural(app);
}
