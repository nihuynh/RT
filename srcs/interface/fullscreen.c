/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fullscreen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 16:24:22 by sklepper          #+#    #+#             */
/*   Updated: 2019/05/24 14:14:13 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.h>
#include <SDL_image.h>
#include "rt.h"
#include "libft.h"
#include "interface.h"
#include "config.h"

#if defined(__APPLE__)
# define GL_SILENCE_DEPRECATION
# include <OpenGL/gl.h>
#else
# include <GL/gl.h>
#endif

void	hook_render_to_gui(t_gui *gui, SDL_Window *window);

void	realloc_pxl(t_sdl *sdl, int width, int height)
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

void	fullscreen(t_sdl *sdl, t_gui *gui)
{
	sdl->img.height = (sdl->img.height == sdl->height_vp) ? sdl->height_vp
		* RENDER_SCALE : sdl->height_vp;
	sdl->img.width = (sdl->img.width == sdl->width_vp) ? sdl->width_vp
		* RENDER_SCALE : sdl->width_vp;
	realloc_pxl(sdl, sdl->img.width, sdl->img.height);
	gui->flags_render = (sdl->img.height == sdl->height_vp) ? ImGuiCond_Always
		: ImGuiCond_Once;
}

void resize_app(int width, int height, t_data *app)
{
	app->sdl->height_vp = height;
	app->sdl->width_vp = width;
	realloc_pxl(app->sdl, width * RENDER_SCALE, height * RENDER_SCALE);
	SDL_SetWindowSize(app->sdl->win, width, height);
	SDL_GL_DeleteContext(app->gui.gl_context);
	hook_render_to_gui(&app->gui, app->sdl->win);
	app->sdl->needs_render = true;
	app->sdl->partial_render = false;

    // glViewport(0, 0, width, height);
    // glClearColor(0, 0, 0, 0);
    // glClear(GL_COLOR_BUFFER_BIT);
    // SDL_GL_SwapWindow(app->sdl->win);
    // igRender();
	// igSetNextWindowPos((ImVec2){0, 0}, 0, (ImVec2){0, 0});
	// igSetNextWindowSize((ImVec2){app->sdl->width_vp, app->sdl->height_vp}, 0);
	// if (app->sdl->renderer != NULL)
	// 	SDL_DestroyRenderer(app->sdl->renderer);
	// if (!(app->sdl->renderer = SDL_CreateRenderer(app->sdl->win, -1, 0x00000001)))
	// 	error_sdl(app->sdl);
	// SDL_SetHint(SDL_HINT_BMP_SAVE_LEGACY_FORMAT, "1");
	// if (IMG_Init(0) != 0)
	// 	error_sdl(app->sdl);
}
