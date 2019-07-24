/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_sdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 12:52:36 by sklepper          #+#    #+#             */
/*   Updated: 2019/07/24 18:40:50 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"
#include "ftmem.h"

void	exit_sdl(t_sdl *sdl)
{
	if (sdl == NULL)
		return ;
	if (sdl->win != NULL)
		SDL_DestroyWindow(sdl->win);
	if (sdl->data_thr != NULL)
		ft_memdel((void**)&sdl->data_thr);
	if (sdl->pool != NULL)
		destroy_pool(sdl->pool);
	if (sdl->img.pixels)
		ft_memdel((void**)&sdl->img.pixels);
	ft_memdel((void**)&sdl);
	SDL_Quit();
}
