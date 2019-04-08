/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sdl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 21:35:33 by nihuynh           #+#    #+#             */
/*   Updated: 2019/04/08 19:22:55 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"
#include "libft.h"
#include "ftio.h"

static inline void
	putcolor(t_sdl *sdl, int color, int x, int y)
{
	t_color	tmp;

	tmp.r = ((color & MASK_RED) >> 16);
	tmp.g = ((color & MASK_GREEN) >> 8);
	tmp.b = (color & MASK_BLUE);
	SDL_SetRenderDrawColor(sdl->renderer, tmp.r, tmp.g, tmp.b, 255);
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
	elapsed_time = ft_curr_usec() - elapsed_time;
	ft_printf("Frame took %f ms to render\n", (float)elapsed_time / 1000);
}
