/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 16:31:49 by nihuynh           #+#    #+#             */
/*   Updated: 2019/03/15 17:59:51 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "librt.h"
#include "ftmem.h"

void
	init_render(t_data *data)
{
	int		len;
	t_vec3	vi;

	len = HEIGHT * WIDTH;
	vec3_new(&vi, 0, 0, -1);
	mat3_rot(&data->matrix_camera[0], &data->matrix_camera[1], &vi, &data->cam);
	if (DEBUG)
		print_matrix(&data->matrix_camera[0], &data->matrix_camera[1]);
	data->sdl.key_map = &key_event;
	data->sdl.mouse_map = &mouse_mapping;
	data->sdl.update = &update;
}
