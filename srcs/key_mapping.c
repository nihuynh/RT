/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_mapping.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 23:51:14 by sklepper          #+#    #+#             */
/*   Updated: 2019/03/14 19:01:00 by tdarchiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "ftio.h"
#include <SDL.h>

/*
** @brief Key mapping
**
** @param quit	Set to 1 to quit the program
** @param key	Keycode of the pressed key
** @param arg	Data
** @param state	True if key is pressed, False if released
*/

static inline int
	camera(t_cam *cam, SDL_Keycode key, bool state)
{
	int	res;

	res = 0;
	(key == SDLK_w) && (cam->move_forward = state);
	(key == SDLK_s) && (cam->move_backward = state);
	(key == SDLK_q) && (cam->move_upward = state);
	(key == SDLK_e) && (cam->move_downward = state);
	(key == SDLK_a) && (cam->strafe_left = state);
	(key == SDLK_d) && (cam->strafe_right = state);
	(key == SDLK_UP) && (cam->rotate_up = state);
	(key == SDLK_DOWN) && (cam->rotate_down = state);
	(key == SDLK_LEFT) && (cam->rotate_left = state);
	(key == SDLK_RIGHT) && (cam->rotate_right = state);
	return (res);
}

void
	key_event(int *quit, SDL_Keycode key, void *arg, bool state)
{
	t_data		*app;
	static bool	mouse_captured;

	app = arg;
	if (key == SDLK_ESCAPE)
		*quit = 1;
	else if (key == SDLK_p)
		save_screenshot(&app->sdl, app->arg);
	else if (key == SDLK_SPACE && state == SDL_RELEASED)
	{
		mouse_captured ^= 1;
		SDL_SetRelativeMouseMode(mouse_captured);
	}
	else if (camera(&app->cam, key, state))
		(void)0;
	else
		ft_printf("%s key: %d\n", state ? "Pressed" : "Released", (int)key);
}

void
	mouse_motion(SDL_Event *event, void *arg)
{
	t_data *app;

	app = arg;
	if (SDL_GetRelativeMouseMode())
	{
		app->cam.x_angle += event->motion.xrel * MOUSE_SCALING;
		app->cam.y_angle += event->motion.yrel * MOUSE_SCALING;
		app->sdl.needs_render = true;
	}
}
