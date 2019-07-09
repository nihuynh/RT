/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_screenshot.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 10:09:20 by sklepper          #+#    #+#             */
/*   Updated: 2019/07/09 11:43:00 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"
#include <time.h>
#include "libft.h"
#include "t_data.h"
#include <SDL_image.h>

static inline char
	*name_by_timestamp(char *arg)
{
	time_t	t;
	char	time_stamp[70];
	char	*scene_name;

	t = time(&t);
	strftime(time_stamp, sizeof(time_stamp), "(%F_%T).png", localtime(&t));
	if (!(scene_name = ft_strrchr(arg, '/')))
		scene_name = arg;
	else
		scene_name++;
	return (ft_strjoin(scene_name, time_stamp));
}

static inline char
	*name_by_framecount(char *arg, int frame_count)
{
	char	*scene_name;
	char	*tmp;

	if (!(scene_name = ft_strrchr(arg, '/')))
		scene_name = arg;
	else
		scene_name++;
	if (!(tmp = ft_strjoini(scene_name, frame_count)))
		ft_error(__func__, __LINE__);
	return (ft_strjoinfree(tmp, ".png"));
}

static inline void
	save_render(t_sdl *sdl, char *name)
{
	SDL_Surface	*surface;

	if (!(surface = SDL_CreateRGBSurfaceWithFormatFrom(sdl->img.pixels,
			sdl->img.width, sdl->img.height,
			32, 4 * sdl->img.width,
			SDL_PIXELFORMAT_ARGB8888)))
		return ;
	IMG_SavePNG(surface, name);
	ft_printf("Screenshot taken [%s]\n", name);
	SDL_FreeSurface(surface);
}

void
	save_screenshot(t_sdl *sdl, char *arg)
{
	t_data		*app;
	char		*abs_name __attribute__((cleanup(ft_strdel)));
	char		*file_name __attribute__((cleanup(ft_strdel)));

	app = get_app(NULL);
	if (!(file_name = name_by_timestamp(arg)))
		ft_error(__func__, __LINE__);
	if (!(abs_name = ft_strjoin(app->option.path, file_name)))
		ft_error(__func__, __LINE__);
	save_render(sdl, abs_name);
}

void
	record_frame(t_data *app)
{
	char		*abs_name __attribute__((cleanup(ft_strdel)));
	char		*file_name __attribute__((cleanup(ft_strdel)));

	if (!(file_name = name_by_framecount(app->arg, app->gui.animated_frames)))
		ft_error(__func__, __LINE__);
	if (!(abs_name = ft_strjoin(app->option.path, file_name)))
		ft_error(__func__, __LINE__);
	save_render(app->sdl, abs_name);
}
