/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_toolbox.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 16:39:57 by sklepper          #+#    #+#             */
/*   Updated: 2019/06/25 22:34:26 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <zconf.h>
#include "t_data.h"
#include "tools.h"
#include "render.h"
#include "config.h"
#include "libft.h"
#include "parse.h"

static inline void
	textures_procedural(t_data *app)
{
	t_texture				node;
	int						len;
	const	t_tex_proced	proced_texture[] = {
		{"none", NULL},
		{"checkers", &texture_checkers},
		{"strips", &texture_strips},
		{"wave", &texture_wave},
		{"perlin", &texture_perlin},
		{"wood", &texture_wood},
		{"marble", &texture_marble},
		{"cloud", &texture_cloud}
	};

	ft_bzero(&node, sizeof(t_texture));
	len = sizeof(proced_texture) / sizeof(t_tex_proced);
	while (--len >= 0)
	{
		if (!(node.name = ft_strdup(proced_texture[len].name)))
			ft_error(__func__, __LINE__);
		node.f_texture = proced_texture[len].f_texture;
		ft_lstpushnew(&app->lst_tex, &node, sizeof(t_texture));
	}
}

void
	init_textures(t_data *app)
{
	open_textures(app);
	ft_lstsort(&app->lst_tex, &texture_cmp);
	textures_procedural(app);
}
