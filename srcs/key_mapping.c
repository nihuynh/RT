/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_mapping.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 23:51:14 by sklepper          #+#    #+#             */
/*   Updated: 2019/03/14 09:40:57 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "ftio.h"
#include <SDL.h>
#include <stdio.h>

/*
** @brief Key mapping
**
** @param quit	Set to 1 to quit the programm
** @param key	Keycode of the pressed key
** @param arg	Data
*/

static inline int
	camera(t_data *data, SDL_Keycode key)
{
	int	res;

	res = 0;
	if (key == SDLK_w && (res = 1))
		camera_zoom(data, Z_STEP);
	else if (key == SDLK_s && (res = 1))
		camera_zoom(data, -Z_STEP);
	else if (key == SDLK_a && (res = 1))
		camera_side(data, -Z_STEP);
	else if (key == SDLK_d && (res = 1))
		camera_side(data, Z_STEP);
	else if (key == SDLK_q && (res = 1))
		camera_height(data, Z_STEP);
	else if (key == SDLK_e && (res = 1))
		camera_height(data, -Z_STEP);
	else if (key == SDLK_RIGHT && (res = 1))
		camera_pan(data, A_STEP);
	else if (key == SDLK_LEFT && (res = 1))
		camera_pan(data, -A_STEP);
	else if (key == SDLK_UP && (res = 1))
		camera_pitch(data, A_STEP);
	else if (key == SDLK_DOWN && (res = 1))
		camera_pitch(data, -A_STEP);
	return (res);
}

void
	key_mapping(int *quit, SDL_Keycode key, void *arg)
{
	t_data *data;

	data = arg;
	if (key == SDLK_ESCAPE)
		*quit = 1;
	else if (key == SDLK_p)
		save_screenshot(&data->sdl, data->arg);
	else if (camera(data, key))
		(void)0;
	else
		ft_printf("the key press is : %d\n", (int)key);
}

void
	mouse_mapping(SDL_Event *event, void *arg)
{
	t_data *data;

	data = arg;
	if (event->type == SDL_MOUSEBUTTONDOWN)
		return ;
}
