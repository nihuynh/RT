/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 16:31:49 by nihuynh           #+#    #+#             */
/*   Updated: 2019/05/17 06:32:01 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "librt.h"
#include "ftmem.h"
#include "interface.h"
#include "config.h"

void
	default_settings(t_settings *settings)
{
	settings->back_color = itocolor(BACK_COLOR);
	settings->depth_max = DEPTH_MAX;
	settings->filter = (t_color){1, 1, 1};
	settings->fov = FOV;
	settings->absorb = 1;
	settings->deflect = 1;
	settings->facing = 1;
	settings->i_light = 1;
	settings->light = 1;
	settings->shadow = 1;
	settings->shine = 1;
}

void
	init(t_data *app)
{
	default_settings(&app->settings);
	init_sdl(&app->sdl, WIDTH, HEIGHT);
	hook_sdl(app);
	hook_cam_to_gui(app);
	init_interface(&app->gui, app->sdl.win, app);
	init_gui(&app->gui, app);
	app->sdl.needs_render = true;
}

void
	hook_cam_to_gui(t_data *app)
{
	set_direction(&app->cam, app->cam.dir);
	if (DEBUG)
		print_matrix(&app->cam.rotation);
	app->gui.cam_cpy = app->cam;
}

void
	hook_sdl(t_data *app)
{
	app->sdl.key_map = &key_event;
	app->sdl.mouse_map = &mouse_motion;
	app->sdl.update = &update;
	app->sdl.render_gui = &render_gui;
	app->sdl.click_map = &click_event;
}
