/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_obj.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 15:27:00 by sklepper          #+#    #+#             */
/*   Updated: 2019/06/19 21:53:44 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "parse.h"
#include "libft.h"
#include "interface.h"

void
	delete_obj(t_data *app)
{
	t_list	*to_del;

	to_del = ft_lstgetnode_by_content_ptr(app->scene.lst_obj, app->gui.obj_set);
	if (to_del == NULL)
		ft_error(__func__, __LINE__);
	if (app->gui.obj_set->anim)
	{
		app->gui.anim_set = app->gui.obj_set->anim;
		anim_delete(app);
	}
	app->scene.lst_obj = ft_lstpop(app->scene.lst_obj, to_del, &del_obj);
	app->gui.obj_set = NULL;
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
