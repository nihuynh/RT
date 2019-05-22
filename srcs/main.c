/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 22:13:42 by nihuynh           #+#    #+#             */
/*   Updated: 2019/05/22 22:15:22 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "libft.h"
#include "config.h"
#include "interface.h"

t_data	*get_app(t_data *app)
{
	static t_data *app_save;

	if (app != NULL)
		app_save = app;
	return (app_save);
}

void	interactive(char *filename, int runmode)
{
	t_data		app;

	ft_bzero(&app, sizeof(t_data));
	get_app(&app);
	init_textures(&app);
	parse_material_csv(&app, "resources/materialList.csv");
	if (DEBUG)
		ft_printf("Loading textures and material are completed\n");
	app.sdl = init_sdl(WIDTH, HEIGHT);
	init_mthr_sdl(app.sdl, &process_pixel, &app);
	hook_sdl(&app);
	load_scene(&app, filename);
	if (runmode == RM_UNIT_TEST)
		return ;
	if (DEBUG)
		ft_printf("RT is starting\n");
	loop_sdl(app.sdl, &app);
	free_app(&app);
}

int		main(int ac, char **av)
{
	int		options;
	int		mode;

	if (ac == 1)
	{
		ft_putendl(USAGE);
		return (-1);
	}
	if ((options = ft_options(ac, av, USAGE).key_found_bitrpz) == -1)
		return (-1);
	if (ac == 2 || (ac > 2 && options != 0))
	{
		mode = (options & (1 << 19)) ? RM_UNIT_TEST : RM_NORMAL;
		interactive(av[1], mode);
	}
	while (options & (1 << 11))
		;
	return (0);
}
