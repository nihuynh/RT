/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 22:13:42 by nihuynh           #+#    #+#             */
/*   Updated: 2019/06/25 17:50:35 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <time.h>
#include "rt.h"
#include "libft.h"
#include "config.h"
#include "interface.h"

t_data
	*get_app(t_data *app)
{
	static t_data *app_save;

	if (app == NULL)
		return (app_save);
	if (app_save == app)
		app_save = NULL;
	else
		app_save = app;
	return (app_save);
}

t_data
	*boot_rt(int ac, char **av)
{
	t_data	*app;

	if (DEBUG)
		ft_putendl("RT is booting ...");
	if (!(app = ft_memalloc(sizeof(t_data))))
		ft_error(__func__, __LINE__);
	app->option = ft_options(ac, av, USAGE);
	get_app(app);
	if (app->option.test_(app->option, 'h'))
		return (app);
	if (DEBUG)
		ft_printf("Loading textures and material are completed\n");
	app->sdl = init_sdl(WIDTH, HEIGHT);
	init_mthr_sdl(app->sdl, &process_pixel, app);
	hook_sdl(app);
	init_textures(app);
	parse_material_csv(app, "resources/materialList.csv");
	get_scenes(app);
	return (app);
}

t_scene_name
	*select_rand_scene(t_list *list_scenes)
{
	t_list			*node;
	unsigned int	scene_idx;

	srand(time(NULL));
	scene_idx = rand() % ft_lstlen(list_scenes);
	node = ft_lstat(list_scenes, scene_idx);
	if (!(node = ft_lstat(list_scenes, scene_idx)))
		ft_error(__func__, __LINE__);
	return (node->content);
}

void
	interactive(int ac, char **av)
{
	t_data			*app;
	t_scene_name	*default_scene;

	app = boot_rt(ac, av);
	if (app->option.test_(app->option, 'h'))
	{
		free_app(app);
		return ;
	}
	if (ac == 1 || ac == (1 + app->option.count_opt))
	{
		if (app->lst_scenes == NULL)
			ft_error(__func__, __LINE__);
		default_scene = select_rand_scene(app->lst_scenes);
		load_scene(app, default_scene->dir);
	}
	else
		load_scene(app, av[1]);
	if (!(app->option.test_(app->option, 't')))
	{
		if (DEBUG)
			ft_printf("RT is starting\n");
		loop_sdl(app->sdl, app);
	}
	free_app(app);
}

int
	main(int ac, char **av)
{
	interactive(ac, av);
	return (EXIT_SUCCESS);
}
