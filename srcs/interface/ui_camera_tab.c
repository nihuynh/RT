/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_camera_tab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 02:36:46 by sklepper          #+#    #+#             */
/*   Updated: 2019/06/25 23:24:40 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"
#include "libft.h"
#include "animate.h"

void	ui_camera_anim(t_anim *anim, ImVec2 size)
{
	char	*str_list;
	int		i;

	i = 0;
	while (anim)
	{
		if (!(str_list = ft_strjoini("Movement ", i)))
			ft_error(__func__, __LINE__);
		anim_list(anim, str_list);
		if (anim->ui_anim)
			anim->ui_anim(anim, i);
		igSeparator();
		if (!anim->next)
			if (igButton("Add Another Animation", (ImVec2){size.x / 3, 0}))
				anim_add_another(anim);
		anim = anim->next;
		i++;
	}
}

void	camera_tab(t_data *app)
{
	t_cam	*cam;
	t_cam	tmp;
	ImVec2	size;

	cam = &app->cam;
	tmp = *cam;
	size = igGetWindowSize();
	if (igBeginTabItem("Camera", NULL, 0))
	{
		igSliderInt("Depth Max", &app->settings.depth_max, 0, 10, NULL);
		igSliderFloat("FOV", &app->settings.fov, 30, 110, "%g", 1);
		if (igInputFloat3("Origin (X Y Z)", &tmp.pos.x, "%g", 0))
			cam->pos = tmp.pos;
		if (igSliderFloat3("Normal (X Y Z)", &tmp.dir.x, -1, 1, "%g", 1))
			cam->dir = tmp.dir;
		igSeparator();
		if (!app->cam.anim && igButton("Add Animation",
			(ImVec2){size.x / 3, 0}))
			anim_add_camera(&app->cam);
		igEndTabItem();
	}
}
