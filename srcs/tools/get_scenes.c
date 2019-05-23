/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_scenes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 02:25:10 by sklepper          #+#    #+#             */
/*   Updated: 2019/05/23 03:36:54 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <dirent.h>
#include "config.h"
#include "libft.h"

static inline void
	add_scene(char *name, t_data *app)
{
	t_scene_name	scene;

	if (!(scene.name = ft_strdup(name)))
		ft_error(__func__, __LINE__);
	if (!(scene.dir = ft_strjoin(SCENE_DIR, name)))
		ft_error(__func__, __LINE__);
	ft_lstpushnew(&app->lst_scenes, &scene, sizeof(scene));
}

void
	get_scenes(t_data *app)
{
	DIR				*d;
	struct dirent	*dir;

	d = opendir(SCENE_DIR);
	if (d)
	{
		while ((dir = readdir(d)) != NULL)
		{
			if (ft_strstr(dir->d_name, ".rt"))
				add_scene(dir->d_name, app);
		}
		closedir(d);
	}
}
