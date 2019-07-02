/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_mapping.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 23:51:14 by sklepper          #+#    #+#             */
/*   Updated: 2019/07/02 23:50:01 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftmath.h"
#include <SDL.h>
#include "t_data.h"
#include "config.h"

/**
** @brief Key mapping
**
** @param quit	Set to 1 to quit the program
** @param key	Keycode of the pressed key
** @param arg	Data
** @param state	True if key is pressed, False if released
** credit : norme - groussel
*/

/*
** TODO : Reduce functions lengths from 27 to 25
*/

static inline bool
	camera(t_cam *cam, SDL_Keycode key, bool state)
{
	if (key == SDLK_w)
		cam->move_forward = state;
	else if (key == SDLK_s)
		cam->move_backward = state;
	else if (key == SDLK_e)
		cam->move_upward = state;
	else if (key == SDLK_q)
		cam->move_downward = state;
	else if (key == SDLK_a)
		cam->strafe_left = state;
	else if (key == SDLK_d)
		cam->strafe_right = state;
	else if (key == SDLK_UP)
		cam->rotate_up = state;
	else if (key == SDLK_DOWN)
		cam->rotate_down = state;
	else if (key == SDLK_LEFT)
		cam->rotate_left = state;
	else if (key == SDLK_RIGHT)
		cam->rotate_right = state;
	else if (key == SDLK_LSHIFT)
		cam->sprint = state;
	else if (key == SDLK_LCTRL)
		cam->walk = state;
	else
		return (false);
	return (true);
}

void
	animation_keybind(t_data *app, SDL_Keycode key, bool state)
{
	if (key == SDLK_k && state == SDL_RELEASED)
		app->gui.animate = true;
	else if (key == SDLK_l && state == SDL_RELEASED)
		app->gui.animate = false;
	else if (key == SDLK_f && state == SDL_RELEASED)
		app->sdl->needs_render = true;
}

void
	key_event(int *quit, SDL_Keycode key, void *arg, bool state)
{
	t_data		*app;
	static bool	mouse_captured;

	app = arg;
	if (key == SDLK_ESCAPE)
		*quit = 1;
	else if (key == SDLK_p && state == SDL_RELEASED)
		save_screenshot(app->sdl, app->arg);
	else if (app->gui.render_focused && state == true)
		return ;
	else if (key == SDLK_SPACE && state == SDL_RELEASED)
	{
		mouse_captured ^= 1;
		SDL_SetRelativeMouseMode(mouse_captured);
	}
	else if (key == SDLK_r && state == SDL_RELEASED
			&& (app->sdl->needs_render = 1))
		app->cam = app->gui.cam_cpy;
	animation_keybind(app, key, state);
	if (camera(&app->cam, key, state))
	{
		app->sdl->sub_sample = SUB_SAMPLE * app->sdl->sub_s
			+ (1 - app->sdl->sub_s);
	}
}

void
	click_event(SDL_Event *ev, void *arg)
{
	t_data	*app;
	int		x;
	int		y;

	app = arg;
	x = ev->button.x - app->gui.pos_render.x;
	y = ev->button.y - app->gui.pos_render.y;
	if (ft_btw(x, 0, app->sdl->img.width) && ft_btw(y, 0, app->sdl->img.height))
	{
		if (ev->button.button == SDL_BUTTON_LEFT && ev->button.clicks == 2)
			app->gui.obj_set = find_obj_at_pixel(app, x, y);
		if (ev->button.button == SDL_BUTTON_RIGHT)
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
		app->sdl->partial_render = false;
		app->sdl->sub_sample = SUB_SAMPLE * app->sdl->sub_s
			+ (1 - app->sdl->sub_s);
		app->sdl->needs_render = true;
	}
}
