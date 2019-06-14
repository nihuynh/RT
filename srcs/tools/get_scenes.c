/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_scenes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 02:25:10 by sklepper          #+#    #+#             */
/*   Updated: 2019/06/14 15:13:16 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <dirent.h>
#include "config.h"
#include "libft.h"

static inline void
	add_scene(char *name, t_data *app, char *dir)
{
	t_scene_name	scene;

	if (!(scene.name = ft_strdup(name)))
		ft_error(__func__, __LINE__);
	if (!(scene.dir = ft_strjoin(dir, name)))
		ft_error(__func__, __LINE__);
	ft_lstpushnew(&app->lst_scenes, &scene, sizeof(scene));
}

void
	get_scenes(t_data *app)
{
	DIR				*d;
	struct dirent	*dir;
	char			*abs_path;

	abs_path = ft_strjoin(app->option.path, SCENE_DIR);
	d = opendir(abs_path);
	if (d)
	{
		while ((dir = readdir(d)) != NULL)
		{
			if (ft_strstr(dir->d_name, ".rt"))
				add_scene(dir->d_name, app, abs_path);
		}
		closedir(d);
	}
	ft_lstsort(&app->lst_scenes, &scene_cmp);
	ft_strdel(&abs_path);
}
