/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_camera_tab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 02:36:46 by sklepper          #+#    #+#             */
/*   Updated: 2019/07/09 15:05:30 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"
#include "libft.h"
#include "animate.h"

void
	ui_camera_anim(t_anim *anim, ImVec2 size)
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

static inline void
	ui_lock_obj_list(t_data *app, char *str)
{
	t_list		*current;
	t_obj		*selected;
	t_obj		*tmp;
	bool		is_selected;

	current = app->scene.lst_obj;
	selected = app->cam.obj_lock;
	tmp = current->content;
	if (igBeginCombo(str, selected->name, 0))
	{
		while (current)
		{
			is_selected = (ft_strcmp(selected->name, tmp->name) == 0);
			if (igSelectable(tmp->name, is_selected, 0, (ImVec2){0, 0}))
				app->cam.obj_lock = tmp;
			if (is_selected)
				igSetItemDefaultFocus();
			current = current->next;
			if (current)
				tmp = current->content;
		}
		igEndCombo();
	}
}

static inline void
	ui_camera_lock(t_data *app)
{
	t_cam	cam;

	cam = app->cam;
	if (cam.lock_pos)
	{
		if (igInputFloat3("Lock Position", &cam.pos_lock.x, "%g", 0))
			app->cam = cam;
	}
	else if (cam.lock_obj)
	{
		ui_lock_obj_list(app, "Lock on Object");
	}
}

void
	camera_tab(t_data *app)
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
		if (igRadioButtonBool("Camera lock on position", app->cam.lock_pos))
		{
			app->cam.lock_pos = 1 - app->cam.lock_pos;
			app->cam.lock_obj = false;
			app->cam.lock = ((app->cam.lock_obj) || (app->cam.lock_pos));
		}
		if (app->scene.lst_obj
			&&igRadioButtonBool("Camera lock on object", app->cam.lock_obj))
		{
			app->cam.lock_obj = 1 - app->cam.lock_obj;
			app->cam.lock_pos = false;
			app->cam.lock = ((app->cam.lock_obj) || (app->cam.lock_pos));

		}
		ui_camera_lock(app);
		igSeparator();
		if (!app->cam.anim && igButton("Add Animation",
			(ImVec2){size.x / 3, 0}))
			anim_add_camera(&app->cam);
		igEndTabItem();
	}
}
