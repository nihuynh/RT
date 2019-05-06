/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fullscreen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 16:24:22 by sklepper          #+#    #+#             */
/*   Updated: 2019/05/06 17:26:40 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "libft.h"
#include "interface.h"

void	fullscreen(t_sdl *sdl, t_gui *gui)
{
	int	idx;

	sdl->img.height = (sdl->img.height == sdl->height_vp) ? sdl->height_vp / 2
															: sdl->height_vp;
	sdl->img.width = (sdl->img.width == sdl->width_vp) ? sdl->width_vp / 2
														: sdl->width_vp;
	free(sdl->img.pixels);
	if (!(sdl->img.pixels = malloc(sizeof(uint32_t)
		* sdl->img.height * sdl->img.width)))
		error_sdl(sdl);
	sdl->thr_len = sdl->img.width * sdl->img.height / THR_C;
	idx = -1;
	while (++idx < THR_C)
	{
		free(sdl->data_thr[idx].data);
		sdl->data_thr[idx].data = ft_memalloc(sizeof(int) * sdl->thr_len);
		if (sdl->data_thr[idx].data == NULL)
			ft_error(__func__, __LINE__);
	}
	gui->flags_render = (sdl->img.height == sdl->height_vp) ? ImGuiCond_Always
															: ImGuiCond_Once;
}
