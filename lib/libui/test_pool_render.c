/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_pool_render.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 11:32:35 by nihuynh           #+#    #+#             */
/*   Updated: 2019/04/12 23:34:17 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libui.h"

/*
**	gcc -Wall -Werror -Wextra test_pool_render.c libui.a -I/Users/nihuynh/.brew/include/SDL2 -L/Users/nihuynh/.brew/lib -lSDL2 ../libft/libft.a
*/


int	process_pixel(int x, int y, void *arg)
{
	(void)x;
	(void)y;
	(void)arg;
	return (0xFF0000);
}

int	main(void)
{
	t_sdl		sdl;
	SDL_Event	event;
	int			quit = 0;

	init_sdl(&sdl, 800, 800);
	sdl.needs_render = true;
	while (!quit)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				quit = 1;
		}
		render_sdl(&sdl, &process_pixel, NULL);
	}
	exit_sdl(&sdl);
	return (0);
}
