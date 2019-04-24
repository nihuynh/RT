/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_fullscreen.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 11:58:45 by sklepper          #+#    #+#             */
/*   Updated: 2019/04/24 17:30:50 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static inline void
	putcolor_sdl(t_sdl *sdl, int color, int x, int y)
{
	t_color	tmp;

	tmp = itocolor(color);
	SDL_SetRenderDrawColor(sdl->renderer, tmp.r, tmp.g, tmp.b, 255);
	SDL_RenderDrawPoint(sdl->renderer, x, y);
}

void
	render_fullscreen(t_sdl *sdl)
{
	t_img	*img;
	int		x;
	int		y;

	if (sdl->needs_render == false)
		return ;
	img = &sdl->img;
	y = -1;
	while (++y < img->height)
	{
		x = -1;
		while (++x < img->width)
			putcolor_sdl(sdl, img->pixels[(y * img->height) + x], x, y);
	}
	SDL_RenderPresent(sdl->renderer);
	sdl->needs_render = false;
}
