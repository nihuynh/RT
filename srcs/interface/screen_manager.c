/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 16:24:22 by sklepper          #+#    #+#             */
/*   Updated: 2019/06/19 01:29:03 by nihuynh          ###   ########.fr       */
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
	fullscreen(t_sdl *sdl, t_gui *gui)
{
	sdl->img.height = (sdl->img.height == sdl->height_vp) ? sdl->height_vp
		* RENDER_SCALE : sdl->height_vp;
	sdl->img.width = (sdl->img.width == sdl->width_vp) ? sdl->width_vp
		* RENDER_SCALE : sdl->width_vp;
	realloc_pxl(sdl, sdl->img.width, sdl->img.height);
	gui->flags_render = (sdl->img.height == sdl->height_vp) ? ImGuiCond_Always
		: ImGuiCond_Once;
	gui->stats_open = !gui->sdl->fullscreen;
	gui->edit_open = !gui->sdl->fullscreen;
	gui->render_set_open = !gui->sdl->fullscreen;
	gui->sdl->needs_render = 1;
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
