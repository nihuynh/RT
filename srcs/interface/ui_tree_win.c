/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_tree_win.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 01:44:16 by sklepper          #+#    #+#             */
/*   Updated: 2019/05/27 18:51:36 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "interface.h"
#include "libft.h"

void	obj_selector(t_gui *gui)
{
	t_list		*lst;
	t_obj		*obj;
	bool		selected;

	igText("Object Selector");
	igBeginChild("Objects Selector", (ImVec2){0, 100}, true, 0);
	lst = gui->app->scene.lst_obj;
	while (lst)
	{
		obj = lst->content;
		selected = (obj == gui->obj_set);
		if (igSelectable(obj->name, selected, 0, (ImVec2){0, 0}))
			gui->obj_set = obj;
		lst = lst->next;
	}
	igEndChild();
}
