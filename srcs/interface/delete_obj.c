/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_obj.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 15:27:00 by sklepper          #+#    #+#             */
/*   Updated: 2019/05/28 15:37:06 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "parse.h"
#include "libft.h"

int
	obj_cmp(void *content, void *key)
{
	return (content == key);
}

void
	delete_obj(t_data *app)
{
	t_list	*ptr;
	t_list	*to_del;

	ptr = app->scene.lst_obj;
	if (!(to_del = ft_lstgetnode(ptr, &obj_cmp, app->gui.obj_set)))
		ft_error(__func__, __LINE__);
	if (ptr == to_del)
	{
		app->scene.lst_obj = to_del->next;
		ft_lstdelone(&to_del, &del_obj);
	}
	else
	{
		while (ptr->next != to_del && ptr->next != NULL)
			ptr = ptr->next;
		if (ptr->next != to_del)
			ft_error(__func__, __LINE__);
		ptr->next = to_del->next;
		ft_lstdelone(&to_del, &del_obj);
	}
	app->gui.obj_set = NULL;
}

void
	delete_light(t_data *app)
{
	t_list	*ptr;
	t_list	*to_del;

	ptr = app->scene.lst_light;
	if (!(to_del = ft_lstgetnode(ptr, &obj_cmp, app->gui.light_set)))
		ft_error(__func__, __LINE__);
	if (ptr == to_del)
	{
		app->scene.lst_light = to_del->next;
		ft_lstdelone(&to_del, &del_light);
	}
	else
	{
		while (ptr->next != to_del && ptr->next != NULL)
			ptr = ptr->next;
		if (ptr->next != to_del)
			ft_error(__func__, __LINE__);
		ptr->next = to_del->next;
		ft_lstdelone(&to_del, &del_light);
	}
	app->gui.light_set = NULL;
}
