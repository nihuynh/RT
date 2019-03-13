/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_mthr_sdl.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 23:21:40 by nihuynh           #+#    #+#             */
/*   Updated: 2018/12/19 21:01:05 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <time.h>
#include "libui.h"
#include "libft.h"

SIVOID	putcolor(t_sdl *sdl, int color, int x, int y)
{
	t_color	tmp;

	tmp.r = ((color & MASK_RED) >> 16);
	tmp.g = ((color & MASK_GREEN) >> 8);
	tmp.b = (color & MASK_BLUE);
	SDL_SetRenderDrawColor(sdl->renderer, tmp.r, tmp.g, tmp.b, 255);
	SDL_RenderDrawPoint(sdl->renderer, x, y);
}

SIVOID	apply_color(t_sdl *sdl)
{
	t_pxl	idx;
	int		ofs;
	int		*cursor;
	t_pxl	pxl;

	idx.y = -1;
	while (++idx.y < THR_C)
	{
		idx.x = 0;
		ofs = idx.y * (sdl->height_vp / THR_C);
		while (idx.x < sdl->thr_len)
		{
			cursor = &sdl->data_thr[idx.y].data[idx.x];
			pxl.x = idx.x % sdl->width_vp;
			pxl.y = ofs + idx.x / sdl->width_vp;
			putcolor(sdl, cursor[0], pxl.x, pxl.y);
			putcolor(sdl, cursor[1], pxl.x + 1, pxl.y);
			putcolor(sdl, cursor[2], pxl.x + 2, pxl.y);
			putcolor(sdl, cursor[3], pxl.x + 3, pxl.y);
			idx.x += 4;
		}
	}
	SDL_RenderPresent(sdl->renderer);
}

SIVOID	*process_data(void *arg)
{
	t_data_thr	*slice;
	t_sdl		*sdl;
	int			i;
	int			ofs;

	slice = arg;
	sdl = slice->sdl;
	ofs = slice->idx * (sdl->height_vp / THR_C);
	i = -1;
	while (++i < sdl->thr_len)
	{
		slice->data[i] = slice->do_pxl(i % sdl->width_vp,
			ofs + i / sdl->width_vp,
			slice->prg_data);
	}
	pthread_exit(NULL);
}

void	render_mthr_sdl(t_sdl *sdl)
{
	clock_t		timer;
	int			cthr;
	int			sats;
	void		*ptr;
	pthread_t	toby[THR_C];

	if (sdl->isrender)
		return ;
	timer = clock();
	cthr = -1;
	sats = 0;
	while (++cthr < THR_C && !sats)
	{
		ptr = &(sdl->data_thr[cthr]);
		sats = pthread_create(&toby[cthr], NULL, process_data, ptr);
	}
	sdl->isrender = 1;
	cthr = -1;
	while (++cthr < THR_C)
		pthread_join(toby[cthr], NULL);
	apply_color(sdl);
	timer = clock() - timer;
	ft_printf("Frame took %dms to render\n", (int)timer / 4000);
}
