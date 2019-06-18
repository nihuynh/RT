/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim_toolbox.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 18:54:31 by sklepper          #+#    #+#             */
/*   Updated: 2019/06/18 05:46:48 by sklepper         ###   ########.fr       */
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
	t_anim	new;
	t_list	*ptr;

	ft_bzero(&new, sizeof(t_anim));
	new.obj = obj;
	new.origin = *obj->pos;
	new.pos = obj->pos;
	if (obj->n)
	{
		new.x = obj->x;
		new.n = obj->n;
		new.z = obj->z;
		new.x_save = *obj->x;
		new.n_save = *obj->n;
		new.z_save = *obj->z;
	}
	ft_lstaddendnew(&app->scene.lst_anim, &new, sizeof(new));
	obj->animated = true;
	ptr = ft_lstlast(app->scene.lst_anim);
	obj->anim = ptr->content;
}

void	anim_add_another(t_anim *anim)
{
	t_anim	*new;

	if (!(new = malloc(sizeof(t_anim))))
		ft_error(__func__, __LINE__);
	ft_bzero(new, sizeof(t_anim));
	new->obj = anim->obj;
	new->origin = anim->origin;
	new->pos = anim->pos;
	new->x = anim->x;
	new->n = anim->n;
	new->z = anim->z;
	new->x_save = anim->x_save;
	new->n_save = anim->n_save;
	new->z_save = anim->z_save;
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

void
	anim_add_camera(t_cam *cam)
{
	t_anim	*new;

	if (!(new = malloc(sizeof(t_anim))))
		ft_error(__func__, __LINE__);
	ft_bzero(new, sizeof(t_anim));
	new->pos = &cam->pos;
	new->origin = cam->pos;
	new->n = &cam->dir;
	new->n_save = cam->dir;
	cam->anim = new;
}
