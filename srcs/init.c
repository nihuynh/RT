/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 16:31:49 by nihuynh           #+#    #+#             */
/*   Updated: 2019/05/09 13:58:41 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "librt.h"
#include "ftmem.h"

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
	init(t_data *data)
{
	init_settings(&data->settings);
	init_sdl(&data->sdl, WIDTH, HEIGHT);
	init_render(data);
	init_interface(&data->gui, data->sdl.win, data);
	data->sdl.needs_render = true;
}

void
	init_render(t_data *data)
{
	set_direction(&data->cam, data->cam.dir);
	if (DEBUG)
		print_matrix(&data->cam.rotation);
	data->sdl.key_map = &key_event;
	data->sdl.mouse_map = &mouse_motion;
	data->sdl.update = &update;
	data->sdl.render_gui = &render_gui;
	data->sdl.click_map = &click_event;
	data->gui.cam_cpy = data->cam;
}
