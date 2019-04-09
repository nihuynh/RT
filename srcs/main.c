/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 16:12:24 by sklepper          #+#    #+#             */
/*   Updated: 2019/04/08 17:54:22 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "libui.h"
#include "libft.h"

void	oneframe(char *filename)
{
	t_data		data;

	ft_bzero(&data, sizeof(t_data));
	data.arg = filename;
	if (reader(filename, &data) == EXIT_FAILURE)
		ft_error(__func__, __LINE__);
	init_sdl(&data.sdl, WIDTH, HEIGHT);
	interface(data.sdl.win);
	init_render(&data);
	if (MTHR)
	{
		init_mthr_sdl(&data.sdl, &process_pixel, &data);
		render_mthr_sdl(&data.sdl);
	}
	else
		render_sdl(&data.sdl, &process_pixel, &data);
	loop_sdl(&data.sdl, &data);
	exit_safe(&data);
}

int		main(int ac, char **av)
{
	if (ac != 2)
	{
		ft_putendl(USAGE);
		return (-1);
	}
	oneframe(av[1]);
	while (DEBUG_LEAK)
		;
	return (0);
}
