/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdarchiv <tdarchiv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 15:16:57 by tdarchiv          #+#    #+#             */
/*   Updated: 2019/03/14 18:48:57 by tdarchiv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void	update(void *arg)
{
	t_data	*app;

	app = arg;
	if (app->cam.move_forward)
		camera_zoom(app, Z_STEP);
	if (app->cam.move_backward)
		camera_zoom(app, -Z_STEP);
	if (app->cam.strafe_right)
		camera_side(app, Z_STEP);
	if (app->cam.strafe_left)
		camera_side(app, -Z_STEP);
	if (app->cam.move_upward)
		camera_height(app, Z_STEP);
	if (app->cam.move_downward)
		camera_height(app, -Z_STEP);
	if (app->cam.rotate_right)
		camera_pan(app, A_STEP);
	if (app->cam.rotate_left)
		camera_pan(app, -A_STEP);
	if (app->cam.rotate_up)
		camera_pitch(app, A_STEP);
	if (app->cam.rotate_down)
		camera_pitch(app, -A_STEP);
}
