/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_sdl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 20:10:41 by sklepper          #+#    #+#             */
/*   Updated: 2018/12/20 18:22:03 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.h>
#include "libui.h"
#include "libft.h"

void	error_sdl(t_sdl *sdl)
{
	ft_printf("Erreur SDL_Init : %s", SDL_GetError());
	if (sdl->renderer != NULL)
		SDL_DestroyRenderer(sdl->renderer);
	if (sdl->win != NULL)
		SDL_DestroyWindow(sdl->win);
	SDL_Quit();
	exit(-1);
}
