/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fullscreen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 16:24:22 by sklepper          #+#    #+#             */
/*   Updated: 2019/05/22 07:18:14 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "libft.h"
#include "interface.h"
#include "config.h"

void	fullscreen(t_sdl *sdl, t_gui *gui)
{
	int		idx;
	int		ofs;

	sdl->img.height = (sdl->img.height == sdl->height_vp) ? sdl->height_vp
		* RENDER_SCALE : sdl->height_vp;
	sdl->img.width = (sdl->img.width == sdl->width_vp) ? sdl->width_vp
		* RENDER_SCALE : sdl->width_vp;
	free(sdl->img.pixels);
	if (!(sdl->img.pixels = malloc(sizeof(uint32_t)
		* sdl->img.height * sdl->img.width)))
		error_sdl(sdl);
	sdl->thr_len = sdl->img.width * (sdl->img.height / THR_C);
	idx = -1;
	while (++idx < THR_C)
	{
		ofs = idx * sdl->thr_len;
		sdl->data_thr[idx].pixels = &sdl->img.pixels[ofs];
	}
	gui->ui.flags_render = (sdl->img.height == sdl->height_vp)
								? ImGuiCond_Always : ImGuiCond_Once;
}
