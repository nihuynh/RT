/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_cam_win.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 19:47:14 by sklepper          #+#    #+#             */
/*   Updated: 2019/05/29 19:56:40 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"
#include "rtstruct.h"

void	ui_cam_win(t_gui *gui)
{
	t_cam	*cam;
	t_cam	tmp;

	cam = &gui->app->cam;
	tmp = *cam;
	if (!igBegin("Camera Editor", &gui->cam_open,
		ImGuiWindowFlags_AlwaysAutoResize))
		return ;
	if (igInputFloat3("Origin (X Y Z)", &tmp.pos.x, "%g", 0))
		cam->pos = tmp.pos;
	if (igSliderFloat3("Normal (X Y Z)", &tmp.dir.x, -1, 1, "%g", 1))
		cam->dir = tmp.dir;
	igEnd();
}
