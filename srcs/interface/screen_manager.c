/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 16:24:22 by sklepper          #+#    #+#             */
/*   Updated: 2019/06/22 18:20:46 by nihuynh          ###   ########.fr       */
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

// void
// 	resize_app(int width, int height, t_data *app)
// {
// 	app->sdl->width_vp = width;
// 	app->sdl->height_vp = height;
// 	realloc_pxl(app->sdl, width * RENDER_SCALE, height * RENDER_SCALE);
// 	SDL_SetWindowSize(app->sdl->win, width, height);
// 	app->sdl->needs_render = true;
// }

void
	toggle_layout(t_sdl *sdl, t_gui *gui)
{
	SDL_GetWindowSize(sdl->win, &sdl->width_vp, &sdl->height_vp);
	if (sdl->layout)
	{
		realloc_pxl(sdl, sdl->width_vp * RENDER_SCALE, sdl->height_vp * RENDER_SCALE);
		gui->flags_render = ImGuiCond_Always;
	}
	else
	{
		realloc_pxl(sdl, sdl->width_vp, sdl->height_vp - MENUBAR_HEIGHT);
		gui->flags_render = ImGuiCond_Once;
	}
	gui->stats_open = sdl->layout;
	gui->edit_open = sdl->layout;
	gui->render_set_open = sdl->layout;
	gui->sdl->needs_render = 1;
}

void
	toggle_fullscreen(t_sdl *sdl, t_gui *gui)
{
	if (!(sdl->fullscreen))
		SDL_SetWindowFullscreen(sdl->win, 0);
	else
		SDL_SetWindowFullscreen(sdl->win, SDL_WINDOW_FULLSCREEN_DESKTOP);
	toggle_layout(sdl, gui);
}

void
	resize_app(int width, int height, t_data *app)
{
	app->sdl->width_vp = width;
	app->sdl->height_vp = height;
	app->sdl->fullscreen = false;
	SDL_SetWindowFullscreen(app->sdl->win, 0);
	SDL_SetWindowSize(app->sdl->win, width, height);
	toggle_layout(app->sdl, &app->gui);
	app->sdl->needs_render = true;
}
