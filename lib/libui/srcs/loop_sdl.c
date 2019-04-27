/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_sdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 02:39:43 by nihuynh           #+#    #+#             */
/*   Updated: 2019/04/27 11:24:32 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"
#include "ftio.h"
#include "imgui_impl_sdl.h"

static inline void
	maps(t_sdl *sdl, void *arg, SDL_Event event, int *quit)
{
	if (event.type == SDL_KEYDOWN && sdl->key_map)
		sdl->key_map(quit, event.key.keysym.sym, arg, SDL_PRESSED);
	else if (event.type == SDL_KEYUP && sdl->key_map)
		sdl->key_map(quit, event.key.keysym.sym, arg, SDL_RELEASED);
	else if (event.type == SDL_MOUSEMOTION && sdl->mouse_map)
		sdl->mouse_map(&event, arg);
	else if (event.type == SDL_MOUSEBUTTONDOWN && sdl->click_map)
		sdl->click_map(&event, arg);
}

/*
** @brief Loop waiting for events to happen
**
** @param sdl
** @param arg
*/

void
	loop_sdl(t_sdl *sdl, void *arg)
{
	SDL_Event	event;
	int			quit;

	quit = 0;
	while (!quit)
	{
		while (SDL_PollEvent(&event))
		{
			ImGui_ImplSDL2_ProcessEvent(&event);
			if (event.type == SDL_QUIT)
				quit = 1;
			else
				maps(sdl, arg, event, &quit);
		}
		if (sdl->update)
			sdl->update(arg);
		if (sdl->needs_render && sdl->data_thr)
			render_mthr_sdl(sdl);
		if (sdl->needs_render && sdl->pool)
			pool_render(sdl->pool);
		if (sdl->render_gui && !sdl->fullscreen)
			sdl->render_gui(arg);
	}
}
