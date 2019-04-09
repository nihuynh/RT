/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 16:12:24 by sklepper          #+#    #+#             */
/*   Updated: 2019/04/08 18:22:10 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "libui.h"
#include "libft.h"

void	interactive(char *filename, int width, int height, int runmode)
{
	t_data		data;

	ft_bzero(&data, sizeof(t_data));
	data.arg = filename;
	if (reader(filename, &data) == EXIT_FAILURE)
		ft_error(__func__, __LINE__);
	init_sdl(&data.sdl, width, height);
	interface(data.sdl.win);
	init_render(&data);
	if (MTHR)
	{
		init_mthr_sdl(&data.sdl, &process_pixel, &data);
		render_mthr_sdl(&data.sdl);
	}
	else
		render_sdl(&data.sdl, &process_pixel, &data);
	if (runmode == RM_NORMAL)
		loop_sdl(&data.sdl, &data);
	exit_safe(&data);
}

int		main(int ac, char **av)
{
	int		options;

	options = ft_options(ac, av, USAGE);
	if (options & (1 << 7) || options == -1)
		return (-1);
	if (ac == 2 || (ac == 3 && options & (1 << 19)))
	{
		if (options & (1 << 19))
			interactive(av[1], WIDTH, HEIGHT, RM_UNIT_TEST);
		else
			interactive(av[1], WIDTH, HEIGHT, RM_NORMAL);
		while (DEBUG_LEAK)
			;
		return (0);
	}
	else
	{
		ft_putendl(USAGE);
		return (-1);
	}
	return (0);
}
