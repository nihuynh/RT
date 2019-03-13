/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_sdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 12:52:36 by sklepper          #+#    #+#             */
/*   Updated: 2018/12/20 18:22:16 by nihuynh          ###   ########.fr       */
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
		while (++idx < THR_C)
			free((void*)sdl->data_thr[idx].data);
		free((void*)sdl->data_thr);
	}
	SDL_Quit();
}
