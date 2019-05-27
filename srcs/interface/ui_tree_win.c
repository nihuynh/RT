/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_tree_win.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 01:44:16 by sklepper          #+#    #+#             */
/*   Updated: 2019/05/24 15:37:10 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "interface.h"
#include "libft.h"

void	tree_obj_win(t_gui *gui)
{
	t_list		*lst;
	t_obj		*obj;
	int			i[5];
	const char	**item;

	igBegin("Objects Tree", &gui->tree_open, ImGuiWindowFlags_AlwaysAutoResize);
	ft_bzero(i, sizeof(int) * 5);
	lst = gui->app->scene.lst_obj;
	item = (const char*[]){"Plane", "Sphere", "Cone", "Cylinder", "Csg"};
	while (lst)
	{
		obj = lst->content;
		if (igTreeNodeStr(item[obj->type]))
		{
			object(gui->app, obj);
			igTreePop();
		}
		lst = lst->next;
	}
	igEnd();
}
