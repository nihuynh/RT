/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_sdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 02:39:43 by nihuynh           #+#    #+#             */
/*   Updated: 2019/03/01 20:34:50 by nihuynh          ###   ########.fr       */
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
	int quit;

	quit = 0;
	while (!quit)
	{
		while (SDL_PollEvent(&sdl->event))
		{
			if (sdl->event.type == SDL_QUIT)
				quit = 1;
			else if (sdl->event.type == SDL_KEYDOWN && sdl->key_map)
				sdl->key_map(&quit, sdl->event.key.keysym.sym, arg);
			else if (sdl->event.type == SDL_MOUSEBUTTONDOWN && sdl->mouse_map)
				sdl->mouse_map(&sdl->event, arg);
		}
		if (!sdl->isrender && sdl->data_thr)
			render_mthr_sdl(sdl);
	}
}
