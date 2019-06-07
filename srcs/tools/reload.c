/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reload.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 14:14:02 by sklepper          #+#    #+#             */
/*   Updated: 2019/06/07 14:58:41 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "t_gui.h"
#include "t_data.h"
#include "config.h"
#include "librt.h"
#include "libft.h"

static inline void
	default_gui_settings(t_gui *gui)
{
	gui->export_open = false;
	gui->light_set = NULL;
	gui->obj_set = NULL;
	gui->flags_render = 2;
	gui->add_obj_type = 0;
	gui->stats_open = true;
	gui->edit_open = true;
	gui->render_set_open = true;
}

static inline void
	hook_cam_to_gui(t_data *app)
{
	set_direction(&app->cam, app->cam.dir);
	if (DEBUG)
		print_matrix(&app->cam.rotation);
	app->gui.cam_cpy = app->cam;
}

static inline void
	default_settings(t_settings *settings)
{
	settings->back_color = itocolor(BACK_COLOR);
	settings->depth_max = DEPTH_MAX;
	settings->filter = (t_color){1, 1, 1};
	settings->fov = FOV;
	settings->absorb = 1;
	settings->deflect = 1;
	settings->facing = 1;
	settings->light = 1;
	settings->shadow = 1;
	settings->shine = 1;
	settings->debug_normal = 0;
	settings->normal_mapping = 1;
}

static inline void
	set_win_title(SDL_Window *win, char *filename)
{
	char	*title;

	if (filename == NULL)
		return ;
	if ((title = ft_strrchr(filename, '/')))
		title++;
	else
		title = filename;
	if (!(title = ft_strjoin("RT - ", title)))
		ft_error(__func__, __LINE__);
	SDL_SetWindowTitle(win, title);
	ft_strdel(&title);
}

void
	load_scene(t_data *app, char *filename)
{
	free_scene(app);
	if (!(app->arg = ft_strdup(filename)))
		ft_error(__func__, __LINE__);
	if (reader(filename, app) == EXIT_FAILURE)
		ft_error(__func__, __LINE__);
	default_settings(&app->settings);
	default_gui_settings(&app->gui);
	hook_cam_to_gui(app);
	set_win_title(app->sdl->win, filename);
	app->sdl->needs_render = true;
	app->sdl->partial_render = false;
	if (DEBUG)
		ft_printf("Loading of the scene is completed\n");
}
