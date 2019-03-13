/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putpixel_sdl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 09:01:23 by nihuynh           #+#    #+#             */
/*   Updated: 2018/11/30 09:41:30 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

void	putpixel_sdl(t_sdl *sdl, t_color col, int x, int y)
{
	SDL_SetRenderDrawColor(sdl->renderer, col.r, col.g, col.b, 255);
	SDL_RenderDrawPoint(sdl->renderer, x, y);
}
