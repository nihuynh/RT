/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   record_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 17:58:45 by sklepper          #+#    #+#             */
/*   Updated: 2019/06/20 18:12:20 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_data.h"
#include "libui.h"
#include "libft.h"

static inline char
	*name_screenshot(char *arg, int frame_count)
{
	char	*scene_name;
	char	*tmp;

	if (!(scene_name = ft_strrchr(arg, '/')))
		scene_name = arg;
	else
		scene_name++;
	tmp = ft_strjoini(scene_name, frame_count);
	return (ft_strjoinfree(tmp, ".bmp"));
}

void
	record_frame(t_data *app)
{
	SDL_Surface	*surface;
	char		*name;

	if (!(surface = SDL_CreateRGBSurfaceWithFormatFrom(app->sdl->img.pixels,
			app->sdl->img.width, app->sdl->img.height,
			32, 4 * app->sdl->img.width,
			SDL_PIXELFORMAT_ARGB8888)))
		return ;
	if (!(name = name_screenshot(app->arg, app->gui.animated_frames)))
		SDL_SaveBMP(surface, "placeholder.bmp");
	else
	{
		SDL_SaveBMP(surface, name);
		ft_strdel(&name);
	}
	ft_putendl("Screenshot taken ! enjoy !");
	SDL_FreeSurface(surface);
}
