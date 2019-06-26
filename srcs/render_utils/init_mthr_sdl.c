/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mthr_sdl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 00:14:04 by nihuynh           #+#    #+#             */
/*   Updated: 2019/06/26 18:04:04 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"
#include "libft.h"

void
	init_mthr_sdl(t_sdl *sdl, int (*do_pxl) (int, int, void*),
		void *data, void (*prep_render)(t_sdl*))
{
	int		idx;
	int		ofs;

	idx = -1;
	sdl->thr_len = sdl->img.width * (sdl->img.height / THR_C);
	if (!(sdl->data_thr = ft_memalloc(sizeof(t_data_thr) * THR_C)))
		ft_error(__func__, __LINE__);
	while (++idx < THR_C)
	{
		sdl->data_thr[idx].idx = idx;
		sdl->data_thr[idx].sdl = sdl;
		sdl->data_thr[idx].do_pxl = do_pxl;
		sdl->data_thr[idx].prg_data = data;
		ofs = idx * sdl->thr_len;
		sdl->data_thr[idx].pixels = &sdl->img.pixels[ofs];
	}
	sdl->prep_render = prep_render;
}
