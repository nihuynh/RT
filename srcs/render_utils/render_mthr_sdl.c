/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_mthr_sdl.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 23:21:40 by nihuynh           #+#    #+#             */
/*   Updated: 2019/05/22 23:19:54 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <math.h>
#include "libui.h"
#include "libft.h"

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
	idx_in_slice = 0;
	inc = slice->sdl->sub_sample;
	if (inc == SUB_SAMPLE)
		ft_bzero(slice->pixels, sizeof(int) * slice->sdl->thr_len);
	while (idx_in_slice < slice->sdl->thr_len)
	{
		slice->pixels[idx_in_slice] = slice->do_pxl(idx_in_slice % img.width,
		ofs + idx_in_slice / img.width, slice->prg_data) | C_MASK;
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
		sdl->sub_sample--;
	elapsed_time = ft_curr_usec() - elapsed_time;
	push_render_time(sdl, (float)elapsed_time / 1000);
	ft_printf("Frame took %f ms to render\n", (float)elapsed_time / 1000);
	sdl->progress_sub_sample = fabsf((float)(sdl->sub_sample  - SUB_SAMPLE) / (SUB_SAMPLE - 1));
}
