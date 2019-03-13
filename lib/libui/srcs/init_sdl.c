/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 20:00:24 by sklepper          #+#    #+#             */
/*   Updated: 2019/02/27 17:04:22 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.h>
#include "libft.h"
#include "libui.h"

int		init_sdl(t_sdl *sdl, int width, int height)
{
	ft_bzero(sdl, sizeof(t_sdl));
	sdl->width_vp = width;
	sdl->height_vp = height;
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		error_sdl(sdl);
	if (!(sdl->win = SDL_CreateWindow("RT",
									SDL_WINDOWPOS_CENTERED,
									SDL_WINDOWPOS_CENTERED,
									width,
									height,
									SDL_WINDOW_SHOWN)))
		error_sdl(sdl);
	if (!(sdl->renderer = SDL_CreateRenderer(sdl->win, -1, 0x00000001)))
		error_sdl(sdl);
	while (SDL_PollEvent(&sdl->event))
		;
	SDL_SetHint(SDL_HINT_BMP_SAVE_LEGACY_FORMAT, "1");
	return (0);
}
