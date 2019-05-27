/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_sdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 12:52:36 by sklepper          #+#    #+#             */
/*   Updated: 2019/05/26 20:16:55 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"
#include <stdlib.h>

void	exit_sdl(t_sdl *sdl)
{
	int idx;

	idx = -1;
	if (sdl->win != NULL)
		SDL_DestroyWindow(sdl->win);
	if (sdl->data_thr != NULL)
	{
		free((void*)sdl->data_thr);
		sdl->data_thr = NULL;
	}
	if (sdl->pool != NULL)
		destroy_pool(sdl->pool);
	if (sdl->img.pixels)
		free(sdl->img.pixels);
	SDL_Quit();
}
