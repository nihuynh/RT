/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 16:31:49 by nihuynh           #+#    #+#             */
/*   Updated: 2019/04/16 17:47:41 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "librt.h"
#include "ftmem.h"

void
	init_scene(t_scene *scene)
{
	scene->back_color = itocolor(BACK_COLOR);
	scene->depth_max = DEPTH_MAX;
	scene->fov = FOV;
}

void
	init(t_data *data)
{
	init_scene(&data->scene_set);
	init_sdl(&data->sdl, WIDTH, HEIGHT);
	init_render(data);
	init_interface(&data->gui, data->sdl.win, data);
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
}
