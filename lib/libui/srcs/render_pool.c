/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_pool.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 11:12:38 by nihuynh           #+#    #+#             */
/*   Updated: 2019/03/19 13:57:07 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"
#include "libft.h"

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
	init_pool_render(t_sdl *sdl, int thr_count, int (*do_pxl) (int, int, void*))
{
	sdl->sample_scale = 1; // dont use for now
	sdl->pxl_idx = 0;
	sdl->offset = 0;
}


void
	render_pool(t_sdl *sdl, void *data)
{
	long	elapsed_time;
	t_pxl	idx;

	if (sdl->isrender)
		return ;
	elapsed_time = ft_curr_usec();
	// Do the render
	// set the parameter
	// go for the compute
	// wait threads done
	SDL_RenderPresent(sdl->renderer);
	elapsed_time = ft_curr_usec() - elapsed_time;
	ft_printf("Frame took %f ms to render\n", (float) elapsed_time / 1000);
}
