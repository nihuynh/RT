/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 16:12:24 by sklepper          #+#    #+#             */
/*   Updated: 2019/05/17 21:06:23 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "libft.h"

t_data *get_app(t_data *app)
{
	static t_data *_app;

	if (app != NULL)
		_app = app;
	return (_app);
}

void	interactive(char *filename, int runmode)
{
	t_data		app;

	ft_bzero(&app, sizeof(t_data));
	get_app(&app);
	if (!(app.arg = ft_strdup(filename)))
		ft_error(__func__, __LINE__);
	init_textures(&app);
	parse_material_csv(&app, "materialList.csv");
	if (reader(filename, &app) == EXIT_FAILURE)
		ft_error(__func__, __LINE__);
	if (runmode == RM_UNIT_TEST)
		return ;
	init(&app);
	init_mthr_sdl(&app.sdl, &process_pixel, &app);
	loop_sdl(&app.sdl, &app);
	exit_safe(&app);
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
	if ((options = ft_options(ac, av, USAGE)) == -1)
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
