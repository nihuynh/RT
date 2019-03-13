/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 22:04:38 by nihuynh           #+#    #+#             */
/*   Updated: 2018/12/10 14:04:41 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Example program:
** Using SDL2 to create an application window
*/

#include "SDL.h"
#include "libft.h"

int		main(void)
{
	int			quit;
	SDL_Event	e;
	SDL_Window	*win;

	quit = 0;
	win = NULL;
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		ft_printf("Error during init of SDL(%s)\n", SDL_GetError());
		return (-1);
	}
	else
	{
		win = SDL_CreateWindow("Tuto", 0, 0, 800, 800, SDL_WINDOW_RESIZABLE);
		while (!quit)
			while (SDL_PollEvent(&e))
				if (e.type == SDL_QUIT)
					quit = 1;
		if (win)
			SDL_DestroyWindow(win);
		else
			ft_printf("Erreur de création de la fenêtre(%s)\n", SDL_GetError());
	}
	SDL_Quit();
	return (0);
}
