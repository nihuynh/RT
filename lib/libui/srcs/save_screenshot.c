/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_screenshot.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 10:09:20 by sklepper          #+#    #+#             */
/*   Updated: 2019/03/05 14:56:49 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"
#include <time.h>
#include "libft.h"

static inline int
	confirmation(t_sdl *sdl)
{
	int buttonid;

	const SDL_MessageBoxButtonData buttons[] = {
		{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "Yes" },
		{								0, 0, "No" },
	};
	const SDL_MessageBoxColorScheme colorScheme = {
		{
			{ 255,   0,   0 }, {   0, 255,   0 }, { 255, 255,   0 },
			{   0,   0, 255 }, { 255,   0, 255 }
		}
	};
	const SDL_MessageBoxData messageboxdata = {
		SDL_MESSAGEBOX_INFORMATION, sdl->win, "Screenshot",
		"Do you want to take a screenshot ?", SDL_arraysize(buttons),
		buttons, &colorScheme
	};
	if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0)
	{
		SDL_Log("error displaying message box");
		return 0;
	}
	return (buttonid);
}

#include <stdio.h>

static inline char
	*name_screenshot(char *arg)
{
	time_t	t;
	struct	tm tm;
	char	titi[70];
	char	**toby;
	int		i;

	t = time(&t);
	tm = *localtime(&t);
	strftime(titi, sizeof(titi), "%F_%T", &tm);
	printf("%s\n", arg);
	toby = ft_strsplit(arg, '/');
	i = 0;
	while (toby[i])
		i++;
	i--;
	printf("%s\n", toby[i]);
	return(ft_strjoinfree(toby[i], titi));
}

void
	save_screenshot(t_sdl *sdl, char *arg)
{
	const Uint32 format = SDL_PIXELFORMAT_ARGB8888;
	SDL_Surface *surface;
	char *name;

	if (confirmation(sdl) == 0)
		return ;
	if (!(surface = SDL_CreateRGBSurfaceWithFormat(0, sdl->width_vp,
					sdl->height_vp, 32, format)))
		return ;
	if (SDL_RenderReadPixels(sdl->renderer, NULL, format, surface->pixels,
						surface->pitch) == 0)
	{
		name = name_screenshot(arg);
		SDL_SaveBMP(surface, name);
		free(name);
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Screenshot",
					"Screenshot taken.", sdl->win);
	}
	else
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Screenshot",
					"Screenshot failed", sdl->win);
	SDL_FreeSurface(surface);
}
