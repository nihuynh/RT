/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 16:31:49 by nihuynh           #+#    #+#             */
/*   Updated: 2019/03/18 15:28:22 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "librt.h"
#include "ftmem.h"

void
	init_render(t_data *data)
{
	set_direction(&data->cam, data->cam.dir);
	if (DEBUG)
		print_matrix(&data->cam.rotation);
	data->sdl.key_map = &key_event;
	data->sdl.mouse_map = &mouse_motion;
	data->sdl.update = &update;
}
