/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putcolor_sdl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 09:48:05 by nihuynh           #+#    #+#             */
/*   Updated: 2018/12/12 18:22:52 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

void	putcolor_sdl(t_sdl *sdl, int color, int x, int y)
{
	t_color	tmp;

	tmp.r = ((color & MASK_RED) >> 16);
	tmp.g = ((color & MASK_GREEN) >> 8);
	tmp.b = (color & MASK_BLUE);
	SDL_SetRenderDrawColor(sdl->renderer, tmp.r, tmp.g, tmp.b, 255);
	SDL_RenderDrawPoint(sdl->renderer, x, y);
}
