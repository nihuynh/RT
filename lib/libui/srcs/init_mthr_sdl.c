/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mthr_sdl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 00:14:04 by nihuynh           #+#    #+#             */
/*   Updated: 2018/12/19 20:59:44 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"
#include "libft.h"

void	init_mthr_sdl(t_sdl *sdl, int (*do_pxl) (int, int, void*), void *data)
{
	int	idx;
	int	vp_len;

	idx = -1;
	vp_len = sdl->width_vp * sdl->height_vp;
	sdl->thr_len = vp_len / THR_C;
	if (!(sdl->data_thr = ft_memalloc(sizeof(t_data_thr) * THR_C)))
		ft_error(__func__, __LINE__);
	while (++idx < THR_C)
	{
		sdl->data_thr[idx].idx = idx;
		sdl->data_thr[idx].sdl = sdl;
		sdl->data_thr[idx].do_pxl = do_pxl;
		sdl->data_thr[idx].prg_data = data;
		sdl->data_thr[idx].data = ft_memalloc(sizeof(int) * sdl->thr_len);
		if (sdl->data_thr[idx].data == NULL)
			ft_error(__func__, __LINE__);
	}
}
