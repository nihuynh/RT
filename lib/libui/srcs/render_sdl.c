/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sdl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 21:35:33 by nihuynh           #+#    #+#             */
/*   Updated: 2019/04/12 23:14:46 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"
#include "libft.h"
#include "ftio.h"

#define SHIFT_RED		0
#define SHIFT_GREEN		8
#define SHIFT_BLUE		16

static inline void
	putcolor(t_sdl *sdl, int color, int x, int y)
{
	uint8_t r;
	uint8_t g;
	uint8_t b;

	r = (color >> SHIFT_RED) & 0xFF;
	g = (color >> SHIFT_GREEN) & 0xFF;
	b = (color >> SHIFT_BLUE);
	SDL_SetRenderDrawColor(sdl->renderer, r, g, b, 255);
	SDL_RenderDrawPoint(sdl->renderer, x, y);
}

void
	render_sdl(t_sdl *sdl, int (*do_pxl) (int, int, void*), void *data)
{
	long	elapsed_time;
	t_pxl	idx;

	if (sdl->needs_render == false)
		return ;
	elapsed_time = ft_curr_usec();
	idx.y = -1;
	while (++idx.y < sdl->height_vp)
	{
		idx.x = -1;
		while (++idx.x < sdl->width_vp)
			putcolor(sdl, do_pxl(idx.x, idx.y, data), idx.x, idx.y);
	}
	SDL_RenderPresent(sdl->renderer);
	sdl->needs_render = false;
	elapsed_time = ft_curr_usec() - elapsed_time;
	ft_printf("Frame took %f ms to render\n", (float)elapsed_time / 1000);
}
