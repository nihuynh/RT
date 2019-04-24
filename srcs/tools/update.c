/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 15:16:57 by tdarchiv          #+#    #+#             */
/*   Updated: 2019/04/24 17:29:17 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "librt.h"

void	update(void *arg)
{
	t_data *app;

	app = arg;
	update_camera(&app->cam, &app->sdl.needs_render);
}

void	render_gui(void *arg)
{
	t_data *app;

	app = arg;
	update_texture(app->sdl.img, app->gui);
	if (!app->sdl.fullscreen)
		interface(app);
	else
		render_fullscreen(&app->sdl);
}
