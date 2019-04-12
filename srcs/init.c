/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 16:31:49 by nihuynh           #+#    #+#             */
/*   Updated: 2019/04/12 16:16:25 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "librt.h"
#include "ftmem.h"

void
	init_scene(t_scene *scene)
{
	scene->back_color = BACK_COLOR;
	scene->amb_light = AMB_LIGHT;
	scene->no_light = NO_LIGHT;
	scene->no_facing = NO_FACING;
	scene->no_i_light = NO_I_LIGHT;
	scene->no_shine = NO_SHINE;
	scene->no_shadow = NO_SHADOW;
	scene->no_deflect = NO_DEFLECT;
	scene->no_absorb = NO_ABSORB;
	scene->depth_max = DEPTH_MAX;
	scene->fov = FOV;
}

void
	init(t_data	*data)
{
	init_scene(&data->scene_settings);
	init_sdl(&data->sdl, WIDTH, HEIGHT, GUI);
	init_render(data);
	if (data->sdl.gui == 1)
		init_interface(&data->gui, data->sdl.win);
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
}
