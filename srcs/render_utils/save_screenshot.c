/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_screenshot.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 10:09:20 by sklepper          #+#    #+#             */
/*   Updated: 2019/05/04 15:10:37 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"
#include <time.h>
#include "libft.h"

static inline char
	*name_screenshot(char *arg)
{
	time_t	t;
	char	time_stamp[70];
	char	*scene_name;

	t = time(&t);
	strftime(time_stamp, sizeof(time_stamp), "(%F_%T).bmp", localtime(&t));
	if (!(scene_name = ft_strrchr(arg, '/')))
		scene_name = arg;
	else
		scene_name++;
	return (ft_strjoin(scene_name, time_stamp));
}

void
	save_screenshot(t_sdl *sdl, char *arg)
{
	SDL_Surface	*surface;
	char		*name;

	if (!(surface = SDL_CreateRGBSurfaceWithFormatFrom(sdl->img.pixels,
			sdl->img.width, sdl->img.height,
			32, 4 * sdl->img.width,
			SDL_PIXELFORMAT_ARGB8888)))
		return ;
	if (!(name = name_screenshot(arg)))
		SDL_SaveBMP(surface, "placeholder.bmp");
	else
	{
		SDL_SaveBMP(surface, name);
		free(name);
	}
	ft_putendl("Screenshot taken ! enjoy !");
	SDL_FreeSurface(surface);
}
