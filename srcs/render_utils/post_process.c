/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 14:35:31 by nihuynh           #+#    #+#             */
/*   Updated: 2019/05/04 14:55:51 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

void
	apply_simple_filter(t_sdl *sdl, uint32_t (*func) (uint32_t))
{
	t_pxl		idx;
	int			idx_pxl;
	uint32_t	tmp_color;

	idx.y = -1;
	while (++idx.y < sdl->img.height)
	{
		idx.x = -1;
		while (++idx.x < sdl->img.width)
		{
			idx_pxl = (idx.y * sdl->img.height) + idx.x;
			tmp_color = sdl->img.pixels[idx_pxl];
			sdl->img.pixels[idx_pxl] = func(tmp_color);
		}
	}
}
