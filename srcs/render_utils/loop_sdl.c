/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_sdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 02:39:43 by nihuynh           #+#    #+#             */
/*   Updated: 2019/06/19 01:34:14 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"
#include "config.h"
#include "libft.h"
#include "imgui_impl_sdl.h"

static inline void
	event_handle(t_sdl *sdl, void *arg, SDL_Event *event, int *quit)
{
	ImGui_ImplSDL2_ProcessEvent(event);
	if (event->type == SDL_QUIT)
	{
		*quit = 1;
		return ;
	}
	if (event->type == SDL_KEYDOWN && sdl->key_map)
		sdl->key_map(quit, event->key.keysym.sym, arg, SDL_PRESSED);
	else if (event->type == SDL_KEYUP && sdl->key_map)
		sdl->key_map(quit, event->key.keysym.sym, arg, SDL_RELEASED);
	else if (event->type == SDL_MOUSEMOTION && sdl->mouse_map)
		sdl->mouse_map(event, arg);
	else if (event->type == SDL_MOUSEBUTTONDOWN && sdl->click_map)
		sdl->click_map(event, arg);
}

/**
** @brief Loop waiting for events to happen
**
** @param sdl
** @param arg
*/

void
	loop_sdl(t_sdl *sdl, void *arg)
{
	long		start_time;
	SDL_Event	event;
	int			quit;

	start_time = ft_curr_usec();
	quit = 0;
	while (!quit)
	{
		if (sdl->needs_render)
		{
			while (SDL_PollEvent(&event))
				event_handle(sdl, arg, &event, &quit);
		}
		else if (SDL_WaitEventTimeout(&event, 100))
		{
			event_handle(sdl, arg, &event, &quit);
			while (SDL_PollEvent(&event))
				event_handle(sdl, arg, &event, &quit);
		}
		sdl->update(arg);
		if (sdl->needs_render)
			render_mthr_sdl(sdl);
		sdl->render_gui(arg);
		push_gui_time(sdl, ft_curr_usec() - start_time);
		start_time = ft_curr_usec();
	}
}
