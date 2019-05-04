/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 14:35:31 by nihuynh           #+#    #+#             */
/*   Updated: 2019/05/04 15:47:22 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

void
	apply_simple_filter(t_sdl *sdl, uint32_t (*func) (uint32_t))
{
	int			idx_pxl;
	int			idx_limit;

	idx_pxl = -1;
	idx_limit = sdl->img.height * sdl->img.width;
	while (++idx_pxl < idx_limit)
	{
		sdl->img.pixels[idx_pxl] = func(sdl->img.pixels[idx_pxl]) | C_MASK;
	}
}
