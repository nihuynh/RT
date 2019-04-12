/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_mthr_sdl.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 23:21:40 by nihuynh           #+#    #+#             */
/*   Updated: 2019/04/12 22:20:47 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "libui.h"
#include "libft.h"

static inline void
	apply_color(t_sdl *sdl)
{
	t_pxl		idx;
	int			ofs;
	uint32_t	*pc;
	int			pxl_idx;

	idx.y = -1;
	while (++idx.y < THR_C)
	{
		idx.x = 0;
		ofs = idx.y * (sdl->height_vp / THR_C);
		while (idx.x < sdl->thr_len)
		{
			pc = (uint32_t *) &sdl->data_thr[idx.y].data[idx.x];
			pxl_idx = (ofs + idx.x / sdl->width_vp) * sdl->img.width
				+ idx.x % sdl->width_vp;
			sdl->img.pixels[pxl_idx] = pc[0] | C_MASK;
			sdl->img.pixels[pxl_idx + 1] = pc[1] | C_MASK;
			sdl->img.pixels[pxl_idx + 2] = pc[2] | C_MASK;
			sdl->img.pixels[pxl_idx + 3] = pc[3] | C_MASK;
			idx.x += 4;
		}
	}
}

static inline void
	*process_data(void *arg)
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

void
	render_mthr_sdl(t_sdl *sdl)
{
	long		elapsed_time;
	int			cthr;
	int			sats;
	void		*ptr;
	pthread_t	toby[THR_C];

	elapsed_time = ft_curr_usec();
	cthr = -1;
	sats = 0;
	while (++cthr < THR_C && !sats)
	{
		ptr = &(sdl->data_thr[cthr]);
		sats = pthread_create(&toby[cthr], NULL, process_data, ptr);
	}
	sdl->needs_render = false;
	cthr = -1;
	while (++cthr < THR_C)
		pthread_join(toby[cthr], NULL);
	apply_color(sdl);
	elapsed_time = ft_curr_usec() - elapsed_time;
	ft_printf("Frame took %f ms to render\n", (float)elapsed_time / 1000);
}
