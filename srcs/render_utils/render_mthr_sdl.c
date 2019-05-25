/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_mthr_sdl.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 23:21:40 by nihuynh           #+#    #+#             */
/*   Updated: 2019/05/24 21:39:59 by nihuynh          ###   ########.fr       */
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
	while (--inc_y > 0)
	{
		inc_x = inc;
		while (--inc_x >= 0)
			slice->pixels[idx_in_slice++] = color;
		idx_in_slice += img_w - (inc -1);
		if (idx_in_slice  + inc > slice->sdl->thr_len)
			break ;
	}
}

int is_out_of_slice(int idx_in_slice, int thr_len, int inc, int img_w)
{
	int last_line;

	last_line = img_w * (inc - 1);

	if (idx_in_slice >= thr_len)
		return (EXIT_FAILURE);
	// if (idx_in_slice + last_line > thr_len)
	// 	return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static inline t_pxl
	get_real_coordinate(t_data_thr *slice, int idx)
{
	t_pxl		res;
	int			ofs;

	ofs =  slice->idx * slice->sdl->thr_len;
	res.x = idx % slice->sdl->img.width;
	res.y = (ofs + idx) / slice->sdl->img.width;
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
		sdl->sub_sample = SUB_SAMPLE;
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
	if (sdl->partial_render && sdl->sub_sample <= 1)
	{
		sdl->needs_render = false;
		sdl->partial_render = false;
	}
	if (sdl->sub_sample > 1)
		sdl->sub_sample >>= 1;
	elapsed_time = ft_curr_usec() - elapsed_time;
	push_render_time(sdl, (float)elapsed_time / 1000);
	ft_printf("Frame took %f ms to render\n", (float)elapsed_time / 1000);
	sdl->progress_sub_sample += 0.25;
}

t_data_thr
	init_data_thr(t_sdl *sdl, int (*do_pxl) (int, int, void*), void *data)
{
	t_data_thr	slice;

	slice.idx = 0;
	slice.sdl = sdl;
	slice.do_pxl = do_pxl;
	slice.prg_data = data;
	slice.pixels = sdl->img.pixels;
	return (slice);
}

void
	render_sdl_(t_sdl *sdl)
{
	t_data_thr	slice;
	long		elapsed_time;

	elapsed_time = ft_curr_usec();
	init_data_thr(sdl, sdl->data_thr[0].do_pxl, get_app(NULL));
	if (!sdl->partial_render && sdl->sub_sample <= 1)
	{
		sdl->partial_render = true;
		sdl->sub_sample = SUB_SAMPLE;
	}
	process_data(&slice);
	if (sdl->partial_render && sdl->sub_sample <= 1)
	{
		sdl->needs_render = false;
		sdl->partial_render = false;
	}
	if (sdl->sub_sample > 1)
		sdl->sub_sample >>= 1;
	elapsed_time = ft_curr_usec() - elapsed_time;
	push_render_time(sdl, (float)elapsed_time / 1000);
	ft_printf("Frame took %f ms to render\n", (float)elapsed_time / 1000);
	sdl->progress_sub_sample = fabsf((float)(sdl->sub_sample  - SUB_SAMPLE) / (SUB_SAMPLE - 1));
}
