/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 16:12:24 by sklepper          #+#    #+#             */
/*   Updated: 2019/04/24 18:19:51 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "libui.h"
#include "libft.h"
#include <unistd.h>

int
	get_red(int x, int y, void *arg)
{
	(void)x;
	(void)y;
	(void)arg;
	return (0xFF0000);
}

void	interactive(char *filename, int runmode)
{
	t_data		data;

	ft_bzero(&data, sizeof(t_data));
	data.arg = filename;
	if (reader(filename, &data) == EXIT_FAILURE)
		ft_error(__func__, __LINE__);
	if (runmode == RM_UNIT_TEST)
		return ;
	init(&data);
	init_pool(&data.sdl, &process_pixel, &data, 16);
	// init_mthr_sdl(&data.sdl, &process_pixel, &data);
	// render_mthr_sdl(&data.sdl);
	loop_sdl(&data.sdl, &data);
	exit_safe(&data);
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
