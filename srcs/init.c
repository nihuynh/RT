/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 16:31:49 by nihuynh           #+#    #+#             */
/*   Updated: 2019/05/13 16:57:38 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "librt.h"
#include "ftmem.h"
#include "interface.h"

void
	init_settings(t_settings *settings)
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
	init_settings(&app->settings);
	init_sdl(&app->sdl, WIDTH, HEIGHT);
	init_render(app);
	init_interface(&app->gui, app->sdl.win, app);
	init_gui(&app->gui, app);
}

void
	init_render(t_data *app)
{
	set_direction(&app->cam, app->cam.dir);
	if (DEBUG)
		print_matrix(&app->cam.rotation);
	app->sdl.key_map = &key_event;
	app->sdl.mouse_map = &mouse_motion;
	app->sdl.update = &update;
	app->sdl.render_gui = &render_gui;
	app->sdl.click_map = &click_event;
	app->sdl.needs_render = true;
	app->gui.cam_cpy = app->cam;
}
