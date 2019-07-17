/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_obj.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 15:27:00 by sklepper          #+#    #+#             */
/*   Updated: 2019/07/17 16:53:59 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_data.h"
#include "tools.h"
#include "parse.h"
#include "libft.h"
#include "interface.h"

bool
	check_anims(t_data *app)
{
	t_anim	*anim;
	t_list	*lst_anim;
	t_orbit	*orbit;

	lst_anim = app->scene.lst_anim;
	while (lst_anim)
	{
		anim = lst_anim->content;
		while (anim)
		{
			if (anim->type == 2)
			{
				orbit = anim->res;
				if (app->gui.obj_set == orbit->obj_center)
					return (true);
			}
			anim = anim->next;
		}
		lst_anim = lst_anim->next;
	}
	return (false);
}

void
	delete_obj(t_data *app)
{
	t_list	*to_del;
	t_gui	*gui;

	gui = &(app->gui);
	to_del = ft_lstgetnode_by_content_ptr(app->scene.lst_obj, gui->obj_set);
	if (to_del == NULL || check_anims(app))
	{
		ft_strlcpy(gui->err_msg, "Obj can't be deleted.", sizeof(gui->err_msg));
		gui->err_open = true;
		return ;
	}
	if (gui->obj_set->anim)
	{
		gui->anim_set = gui->obj_set->anim;
		anim_delete(app);
	}
	if (app->cam.obj_lock == gui->obj_set)
	{
		app->cam.obj_lock = NULL;
		app->cam.lock_obj = false;
	}
	app->scene.lst_obj = ft_lstpop(app->scene.lst_obj, to_del, &del_obj);
	gui->obj_set = NULL;
}

void
	delete_light(t_data *app)
{
	void	*ptr;
	t_list	*to_del;

	ptr = app->gui.light_set;
	to_del = ft_lstgetnode_by_content_ptr(app->scene.lst_light, ptr);
	if (to_del == NULL)
		ft_error(__func__, __LINE__);
	if (app->gui.light_set->anim)
	{
		app->gui.anim_set = app->gui.light_set->anim;
		anim_delete(app);
	}
	app->scene.lst_light = ft_lstpop(app->scene.lst_light, to_del, &del_light);
	app->gui.light_set = NULL;
}
