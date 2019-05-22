/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_mthr_sdl.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 23:21:40 by nihuynh           #+#    #+#             */
/*   Updated: 2019/05/22 04:41:42 by nihuynh          ###   ########.fr       */
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
		ofs = idx.y * (sdl->img.height / THR_C);
		while (idx.x < sdl->thr_len)
		{
			pc = (uint32_t *)&sdl->data_thr[idx.y].data[idx.x];
			pxl_idx = (ofs + idx.x / sdl->img.width) * sdl->img.width
				+ idx.x % sdl->img.width;
			sdl->img.pixels[pxl_idx] = pc[0] | C_MASK;
			sdl->img.pixels[pxl_idx + 1] = pc[1] | C_MASK;
			sdl->img.pixels[pxl_idx + 2] = pc[2] | C_MASK;
			sdl->img.pixels[pxl_idx + 3] = pc[3] | C_MASK;
			idx.x += 4;
		}
	}
}

static void	under_sample(int *img_str, int idx, int inc_offset)
{
	int idx_local;
	int color;

	color = 0; // img_str[idx];
	idx_local = UNDER_SAMPLE - inc_offset - 1;
	while (++idx_local < UNDER_SAMPLE - (UNDER_SAMPLE - inc_offset))
		img_str[++idx] = color;
}

static inline void
	*process_data(void *arg)
{
	t_data_thr	*slice;
	t_img		img;
	int			idx_in_slice;
	int			inc;
	int			ofs;

	slice = arg;
	img = slice->sdl->img;
	ofs = slice->idx * (img.height / THR_C);
	idx_in_slice = slice->sdl->inc_offset;
	inc = slice->sdl->inc_offset;
	while (idx_in_slice < slice->sdl->thr_len)
	{
		slice->data[idx_in_slice] = slice->do_pxl(idx_in_slice % img.width,
		ofs + idx_in_slice / img.width, slice->prg_data);
		if (inc > 1)
			under_sample(slice->data, idx_in_slice, inc);
		idx_in_slice += inc;
	}
	pthread_exit(NULL);
}


void
	render_mthr_sdl(t_sdl *sdl)
{
	long		start_time;
	int			cthr;
	int			sats;
	void		*ptr;
	pthread_t	threads[THR_C];

	start_time = ft_curr_usec();
	if (!sdl->partial_render && sdl->inc_offset <= 1)
	{
		sdl->partial_render = true;
		sdl->inc_offset = UNDER_SAMPLE;
	}
	cthr = -1;
	sats = 0;
	while (++cthr < THR_C && !sats)
	{
		ptr = &(sdl->data_thr[cthr]);
		sats = pthread_create(&threads[cthr], NULL, process_data, ptr);
	}
	cthr = -1;
	while (++cthr < THR_C)
		pthread_join(threads[cthr], NULL);
	apply_color(sdl);
	if (sdl->partial_render && sdl->inc_offset <= 1)
	{
		sdl->needs_render = false;
		sdl->partial_render = false;
	}
	if (sdl->inc_offset > 1)
		sdl->inc_offset--;
	push_render_time(sdl, ft_curr_usec() - start_time);
	// SDL_Delay(5000 / UNDER_SAMPLE);
}
