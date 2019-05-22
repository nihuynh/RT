/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_sdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 12:52:36 by sklepper          #+#    #+#             */
/*   Updated: 2019/05/22 06:38:56 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"
#include <stdlib.h>

void	exit_sdl(t_sdl *sdl)
{
	int idx;

	idx = -1;
	if (sdl->renderer != NULL)
		SDL_DestroyRenderer(sdl->renderer);
	if (sdl->win != NULL)
		SDL_DestroyWindow(sdl->win);
	if (sdl->data_thr != NULL)
	{
		free((void*)sdl->data_thr);
		sdl->data_thr = NULL;
	}
	if (sdl->pool != NULL)
		destroy_pool(sdl->pool);
	SDL_Quit();
}
