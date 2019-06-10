/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim_toolbox.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 18:54:31 by sklepper          #+#    #+#             */
/*   Updated: 2019/06/10 17:42:12 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"
#include "animate.h"
#include "libft.h"
#include "parse.h"

int
	anim_cmp(void *content, void *key)
{
	return (content == key);
}

void	anim_delete(t_data *app)
{
	t_list	*ptr;
	t_list	*to_del;

	ptr = app->scene.lst_anim;
	if (!(to_del = ft_lstgetnode(ptr, &anim_cmp, app->gui.anim_set)))
		ft_error(__func__, __LINE__);
	app->scene.lst_anim = ft_lstpop(app->scene.lst_anim, to_del, &del_anim);
	app->gui.anim_set = NULL;
}

void	anim_add(t_data *app, t_obj *obj)
{
	t_anim new;

	new.type = 0;
	new.obj = obj;
	new.anim_obj = NULL;
	new.res = NULL;
	new.ui_anim = NULL;
	ft_lstpushnew(&app->scene.lst_anim, &new, sizeof(new));
}
