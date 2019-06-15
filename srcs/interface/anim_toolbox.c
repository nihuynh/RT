/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim_toolbox.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 18:54:31 by sklepper          #+#    #+#             */
/*   Updated: 2019/06/15 21:29:38 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface.h"
#include "animate.h"
#include "libft.h"
#include "parse.h"

void	anim_delete(t_data *app)
{
	t_list	*ptr;
	t_list	*to_del;

	ptr = app->scene.lst_anim;
	if (!(to_del = ft_lstgetnode_by_content_ptr(ptr, app->gui.anim_set)))
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
	new.origin = *obj->pos;
	if (obj->n)
	{
		new.x = *obj->x;
		new.n = *obj->n;
		new.z = *obj->z;
	}
	new.next = NULL;
	ft_lstpushnew(&app->scene.lst_anim, &new, sizeof(new));
	obj->animated = true;
	obj->anim = app->scene.lst_anim->content;
}

void	anim_add_another(t_anim *anim)
{
	t_anim	*new;

	if (!(new = malloc(sizeof(t_anim))))
		ft_error(__func__, __LINE__);
	new->type = 0;
	new->obj = anim->obj;
	new->anim_obj = NULL;
	new->res = NULL;
	new->ui_anim = NULL;
	new->origin = *anim->obj->pos;
	new->next = NULL;
	anim->next = new;
}

void
	anim_free(t_anim *anim)
{
	if (anim->type == 0)
		return ;
	else
		free(anim->res);
	anim->res = NULL;
}
