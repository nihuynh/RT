/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 16:31:49 by nihuynh           #+#    #+#             */
/*   Updated: 2019/04/24 19:07:19 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "librt.h"
#include "ftmem.h"

void
	init_scene(t_scene *scene)
{
	scene->back_color = itocolor(BACK_COLOR);
	scene->amb_light = AMB_LIGHT;
	scene->depth_max = DEPTH_MAX;
	scene->fov = FOV;
	scene->absorb = 1;
	scene->deflect = 1;
	scene->facing = 1;
	scene->i_light = 1;
	scene->light = 1;
	scene->shadow = 1;
	scene->shine = 1;
}

void
	init(t_data *data)
{
	init_scene(&data->scene_set);
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
	data->sdl.render_fullscreen = &render_fullscreen;
	data->sdl.click_map = &click_event;
}
