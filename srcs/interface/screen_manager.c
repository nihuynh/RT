/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 16:24:22 by sklepper          #+#    #+#             */
/*   Updated: 2019/06/20 19:29:24 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.h>
#include "config.h"
#include "libui.h"
#include "interface.h"

void
	realloc_pxl(t_sdl *sdl, int width, int height)
{
	int		idx;
	int		ofs;

	if (sdl->img.pixels)
		free(sdl->img.pixels);
	sdl->img.height = height;
	sdl->img.width = width;
	sdl->thr_len = (width * height) / THR_C;
	if (!(sdl->img.pixels = malloc(sizeof(uint32_t) * width * height)))
		error_sdl(sdl);
	idx = -1;
	while (++idx < THR_C)
	{
		ofs = idx * sdl->thr_len;
		sdl->data_thr[idx].pixels = &sdl->img.pixels[ofs];
	}
}

void
	resize_app(int width, int height, t_data *app)
{
	app->sdl->width_vp = width;
	app->sdl->height_vp = height;
	realloc_pxl(app->sdl, width * RENDER_SCALE, height * RENDER_SCALE);
	SDL_SetWindowSize(app->sdl->win, width, height);
	app->sdl->needs_render = true;
}

void
	fullscreen(t_sdl *sdl, t_gui *gui)
{
	if (!(sdl->fullscreen))
	{
		SDL_SetWindowFullscreen(sdl->win, 0);
		resize_app(sdl->width_vp, sdl->height_vp, gui->app);
		gui->flags_render = ImGuiCond_Always;
	}
	else
	{
		SDL_SetWindowFullscreen(sdl->win, SDL_WINDOW_FULLSCREEN_DESKTOP);
		SDL_GetWindowSize(sdl->win, &sdl->width_vp, &sdl->height_vp);
		realloc_pxl(sdl, sdl->width_vp, sdl->height_vp - MENUBAR_HEIGHT);
		gui->flags_render = ImGuiCond_Once;
	}
	gui->stats_open = !sdl->fullscreen;
	gui->edit_open = !sdl->fullscreen;
	gui->render_set_open = !sdl->fullscreen;
	gui->sdl->needs_render = 1;
}
