/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_sdl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 20:10:41 by sklepper          #+#    #+#             */
/*   Updated: 2019/05/24 14:43:10 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.h>
#include "libui.h"
#include "libft.h"

void	error_sdl(t_sdl *sdl)
{
	ft_printf("Erreur SDL_Init : %s", SDL_GetError());
	exit_sdl(sdl);
	exit(-1);
}
