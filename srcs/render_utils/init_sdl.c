/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 20:00:24 by sklepper          #+#    #+#             */
/*   Updated: 2019/05/14 11:00:36 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.h>
#include "libft.h"
#include "libui.h"

int		init_sdl(t_sdl *sdl, int width, int height)
{
	ft_bzero(sdl, sizeof(t_sdl));
	sdl->height_vp = height;
	sdl->width_vp = width;
	sdl->img.height = height * 0.7;
	sdl->img.width = width * 0.7;
	if (!(sdl->img.pixels = malloc(sizeof(uint32_t)
		* sdl->img.height * sdl->img.width)))
		error_sdl(sdl);
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
	SDL_SetHint(SDL_HINT_BMP_SAVE_LEGACY_FORMAT, "1");
	return (0);
}
