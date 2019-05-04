/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_mthr_sdl.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 23:21:40 by nihuynh           #+#    #+#             */
/*   Updated: 2019/05/04 16:19:38 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "libui.h"
#include "libft.h"
#include "librt.h"
#include "color.h"

uint32_t	sepia(uint32_t in_col)
{
	t_color c;
	t_color out;

	c.r = (in_col >> SHIFT_RED) & 0xFF;
	c.g = (in_col >> SHIFT_GREEN) & 0xFF;
	c.b = (in_col >> SHIFT_BLUE) & 0xFF;
	out.r = ft_clampf((c.r * .393) + (c.g *.769) + (c.b * .189), 0, 255.0);
	out.g = ft_clampf((c.r * .349) + (c.g *.686) + (c.b * .168), 0, 255.0);
	out.b = ft_clampf((c.r * .272) + (c.g *.534) + (c.b * .131), 0, 255.0);
	color_scalar(&out, 1 / 255.f);
	return (colortoi(out));
}

uint32_t	grayscale(uint32_t in_col)
{
	t_color	c;
	int		out;
	int		res;

	c.r = (in_col >> SHIFT_RED) & 0xFF;
	c.g = (in_col >> SHIFT_GREEN) & 0xFF;
	c.b = (in_col >> SHIFT_BLUE) & 0xFF;
	out = (c.r + c.g + c.b) / 3;
	res = (out << SHIFT_RED) + (out << SHIFT_GREEN) + (out << SHIFT_BLUE);
	return (res);
}

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

static inline void
	*process_data(void *arg)
{
	t_data_thr	*slice;
	t_sdl		*sdl;
	int			i;
	int			ofs;

	slice = arg;
	sdl = slice->sdl;
	ofs = slice->idx * (sdl->img.height / THR_C);
	i = -1;
	while (++i < sdl->thr_len)
	{
		slice->data[i] = slice->do_pxl(i % sdl->img.width,
		ofs + i / sdl->img.width,
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
	pthread_t	threads[THR_C];

	elapsed_time = ft_curr_usec();
	cthr = -1;
	sats = 0;
	while (++cthr < THR_C && !sats)
	{
		ptr = &(sdl->data_thr[cthr]);
		sats = pthread_create(&threads[cthr], NULL, process_data, ptr);
	}
	sdl->needs_render = false;
	cthr = -1;
	while (++cthr < THR_C)
		pthread_join(threads[cthr], NULL);
	apply_color(sdl);
	// apply_simple_filter(sdl, &sepia);
	elapsed_time = ft_curr_usec() - elapsed_time;
	ft_printf("Frame took %f ms to render\n", (float)elapsed_time / 1000);
}
