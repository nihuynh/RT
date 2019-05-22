/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 16:12:24 by sklepper          #+#    #+#             */
/*   Updated: 2019/05/22 21:11:58 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "libft.h"
#include "config.h"
#include "interface.h"

t_data	*get_app(t_data *app)
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

__attribute__((constructor)) void
	boot_rt(int ac, char **av)
{
	t_data		*app;

	if (DEBUG)
		ft_putendl("RT is booting ...");
	if (!(app = ft_memalloc(sizeof(t_data))))
		ft_error(__func__, __LINE__);
	get_app(app);
	app->option = ft_options(ac, av, USAGE);
	if (app->option.key_found_bitrpz == -1)
		ft_error(__func__, __LINE__);
	init_textures(app);
	parse_material_csv(app, "resources/materialList.csv");
	if (DEBUG)
		ft_printf("Loading textures and material are completed\n");
	app->sdl = init_sdl(WIDTH, HEIGHT);
	init_mthr_sdl(app->sdl, &process_pixel, app);
	hook_sdl(app);
}

int
	main(int ac, char **av)
{
	t_data	*app;

	app = get_app(NULL);
	if (ac > 1)
		load_scene(app, av[1]);
	if (app->option.key_found_bitrpz & (1 << ('t' - 'a')))
		return (EXIT_SUCCESS);
	loop_sdl(app->sdl, &app);
	free_app(app);
	return (EXIT_SUCCESS);
}
