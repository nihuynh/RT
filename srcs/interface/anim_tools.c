/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 22:05:53 by nihuynh           #+#    #+#             */
/*   Updated: 2019/07/24 18:37:57 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "animate.h"
#include "libft.h"
#include "t_data.h"
#include "interface.h"

int
	anim_free(t_anim *anim)
{
	if (anim->type == 0)
		return (1);
	else
		ft_memdel((void**)&anim->res);
	anim->res = NULL;
	return (1);
}

static inline void
	anim_del_one_first(t_data *app, t_anim *anim, t_anim *to_del)
{
	t_list *lst;

	if (!(lst = ft_lstgetnode_by_content_ptr(app->scene.lst_anim, anim)))
		if (!(lst = ft_lstgetnode_by_content_ptr(app->scene.lst_anim_light,
			anim)))
			if (anim != app->cam.anim)
				ft_error(__func__, __LINE__);
	if (to_del->next == NULL)
		anim_delete(app);
	else
	{
		lst->content = to_del->next;
		app->gui.anim_set = to_del->next;
		(anim_free(to_del)) ? ft_memdel((void**)&to_del) : (void)0;
	}
}

void
	anim_del_one(t_data *app, t_anim *anim, t_anim *to_del)
{
	if (anim == to_del)
		anim_del_one_first(app, anim, to_del);
	else
	{
		while (anim->next != to_del && anim->next)
			anim = anim->next;
		if (anim->next != to_del)
			ft_error(__func__, __LINE__);
		anim->next = anim->next->next;
		(anim_free(to_del)) ? ft_memdel((void**)&to_del) : (void)0;
	}
}
