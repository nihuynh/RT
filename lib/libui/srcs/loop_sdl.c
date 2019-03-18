/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_sdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 02:39:43 by nihuynh           #+#    #+#             */
/*   Updated: 2019/03/14 17:32:58 by tdarchiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"
#include "ftio.h"

/**
** @brief Loop waiting for events to happen
**
** @param sdl
** @param arg
*/

void	loop_sdl(t_sdl *sdl, void *arg)
{
	SDL_Event	event;
	int			quit;

	quit = 0;
	while (!quit)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				quit = 1;
			else if (event.type == SDL_KEYDOWN && sdl->key_map)
				sdl->key_map(&quit, event.key.keysym.sym, arg, SDL_PRESSED);
			else if (event.type == SDL_KEYUP && sdl->key_map)
				sdl->key_map(&quit, event.key.keysym.sym, arg, SDL_RELEASED);
			else if (event.type == SDL_MOUSEBUTTONDOWN && sdl->mouse_map)
				sdl->mouse_map(&event, arg);
		}
		if (sdl->update)
			sdl->update(arg);
		if (sdl->needs_render && sdl->data_thr)
			render_mthr_sdl(sdl);
	}
}
