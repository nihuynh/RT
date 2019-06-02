/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_mthr_sdl.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 23:21:40 by nihuynh           #+#    #+#             */
/*   Updated: 2019/06/03 00:46:09 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <math.h>
#include "libui.h"
#include "libft.h"
#include "rt.h"
#include "config.h"

void
	sub_sampler(t_data_thr *slice, int idx_in_slice, int inc, int color, int img_w)
{
	int inc_x;
	int inc_y;
	(void)img_w;

	inc_y = inc;
	while (--inc_y >= 0)
	{
		inc_x = inc;
		while (--inc_x >= 0)
			slice->pixels[idx_in_slice++] = color;
		idx_in_slice += img_w - (inc -1);
		if (idx_in_slice  + inc > slice->sdl->thr_len)
			break ;
	}
}

static inline t_pxl
	get_real_coordinate(t_data_thr *slice, int idx)
{
	t_pxl	res;
	int			idx_total;

	idx_total = slice->idx * slice->sdl->thr_len + idx;
	res.x = idx_total % slice->sdl->img.width;
	res.y = idx_total / slice->sdl->img.width;
	return (res);
}

static inline void
	*process_data(void *arg)
{
	t_data_thr	*slice;
	int			idx_in_slice;
	int			img_w;
	int			inc;
	int			color;
	t_pxl		real_pos;

	slice = arg;
	img_w = slice->sdl->img.width;
	inc = slice->sdl->sub_sample;
	idx_in_slice = 0;
	if (inc == SUB_SAMPLE)
		ft_bzero(slice->pixels, sizeof(int) * slice->sdl->thr_len);
	while (idx_in_slice < slice->sdl->thr_len)
	{
		real_pos = get_real_coordinate(slice, idx_in_slice);
		color = slice->do_pxl(real_pos.x, real_pos.y, slice->prg_data) | C_MASK;
		sub_sampler(slice, idx_in_slice, inc, color, img_w);
		idx_in_slice += inc;
	}
	pthread_exit(NULL);
}

void
	render_mthr_sdl(t_sdl *sdl)
{
	int			cthr;
	int			sats;
	void		*ptr;
	pthread_t	threads[THR_C];
	long		elapsed_time;

	elapsed_time = ft_curr_usec();
	if (!sdl->partial_render && sdl->sub_sample <= 1)
	{
		sdl->progress_sub_sample = 0;
		sdl->partial_render = true;
		if (sdl->sub_s)
			sdl->sub_sample = SUB_SAMPLE;
		else
			sdl->sub_sample = 1;
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
	if (sdl->sub_sample > 1)
		sdl->sub_sample >>= 1;
	else
	{
		sdl->needs_render = false;
		sdl->partial_render = false;
	}
	elapsed_time = ft_curr_usec() - elapsed_time;
	push_render_time(sdl, (float)elapsed_time / 1000);
	ft_printf("Frame took %f ms to render\n", (float)elapsed_time / 1000);
	sdl->progress_sub_sample += 0.25;
}
