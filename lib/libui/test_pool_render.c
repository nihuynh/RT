/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_pool_render.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 11:32:35 by nihuynh           #+#    #+#             */
/*   Updated: 2019/03/18 11:39:49 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libui.h"

int	process_pixel(int x, int y, void *arg)
{
	(void)x;
	(void)y;
	(void)arg;
	return (0xFFFFFF);
}

int	main(int ac, char **av)
{
	t_sdl		sdl;
	init_sdl(&sdl, 800, 800);
	init_pool_render(&sdl, 16, &process_pixel);
	loop_sdl(&sdl, NULL);
	exit_sdl(&sdl);
	return (0);
}
