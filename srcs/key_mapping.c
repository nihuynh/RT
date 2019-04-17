/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_mapping.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 23:51:14 by sklepper          #+#    #+#             */
/*   Updated: 2019/04/16 17:55:29 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "ftio.h"
#include <SDL.h>
#include "interface.h"

/*
** @brief Key mapping
**
** @param quit	Set to 1 to quit the program
** @param key	Keycode of the pressed key
** @param arg	Data
** @param state	True if key is pressed, False if released
*/

static inline void
	camera(t_cam *cam, SDL_Keycode key, bool state)
{
	(key == SDLK_w) && (cam->move_forward = state);
	(key == SDLK_s) && (cam->move_backward = state);
	(key == SDLK_e) && (cam->move_upward = state);
	(key == SDLK_q) && (cam->move_downward = state);
	(key == SDLK_a) && (cam->strafe_left = state);
	(key == SDLK_d) && (cam->strafe_right = state);
	(key == SDLK_UP) && (cam->rotate_up = state);
	(key == SDLK_DOWN) && (cam->rotate_down = state);
	(key == SDLK_LEFT) && (cam->rotate_left = state);
	(key == SDLK_RIGHT) && (cam->rotate_right = state);
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
	camera(&app->cam, key, state);
}

void
	click_event(SDL_Event *event, void *arg)
{
	t_data	*app;
	int		x;
	int		y;

	app = arg;
	if (event->button.button == SDL_BUTTON_LEFT && event->button.clicks == 2)
	{
		x = event->button.x - app->gui.pos_render.x;
		y = event->button.y - app->gui.pos_render.y;
		if (x >= 0 && x < app->sdl.img.width
		&& y >= 20 && y < app->sdl.img.height)
			app->gui.obj_set = find_obj_at_pixel(app, x, y);
	}
	if (event->button.button == SDL_BUTTON_RIGHT)
	{
		x = event->button.x - app->gui.pos_render.x;
		y = event->button.y - app->gui.pos_render.y;
		if (x >= 0 && x < app->sdl.img.width
			&& y >= 20 && y < app->sdl.img.height)
			process_pixel(x, y, app);
	}
}

void
	mouse_motion(SDL_Event *event, void *arg)
{
	t_data *app;

	app = arg;
	if (SDL_GetRelativeMouseMode())
	{
		app->cam.y_angle += event->motion.xrel * MOUSE_SCALING;
		app->cam.x_angle += event->motion.yrel * MOUSE_SCALING;
		app->sdl.needs_render = true;
	}
}
