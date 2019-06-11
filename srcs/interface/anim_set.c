/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim_set.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 17:36:18 by sklepper          #+#    #+#             */
/*   Updated: 2019/06/11 01:14:04 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "animate.h"
#include "stdlib.h"
#include "libft.h"
#include "t_data.h"

static inline void
	anim_set_translate(t_anim *anim)
{
	t_translate *translate;

	if (!(translate = malloc(sizeof(t_translate))))
		ft_error(__func__, __LINE__);
	ft_bzero(translate, sizeof(t_translate));
	anim->res = translate;
	anim->anim_obj = &anim_translate;
	anim->ui_anim = &ui_translate;
}

void
	anim_free(t_anim *anim)
{
	t_translate	*translate;
	t_rotate	*rotate;
	t_orbit		*orbit;

	if (anim->type == 0)
		return ;
	else if (anim->type == 1)
	{
		translate = anim->res;
		if (translate)
			free(translate);
	}
	else if (anim->type == 2)
	{
		rotate = anim->res;
		if (rotate)
			free(rotate);
	}
	else if (anim->type == 3)
	{
		orbit = anim->res;
		if (orbit)
			free(orbit);
	}
	anim->res = NULL;
}

void
	anim_set(t_anim *anim, int type)
{
	if (anim->type == type)
		return ;
	anim_free(anim);
	anim->type = type;
	if (type == 0)
	{
		anim->anim_obj = NULL;
		anim->ui_anim = NULL;
	}
	else if (type == 1)
		anim_set_translate(anim);
}

void
	anim_reset(t_data *app)
{
	t_list	*lst;
	t_anim	*anim;

	lst = app->scene.lst_anim;
	while (lst)
	{
		anim = lst->content;
		*anim->pos = anim->origin;
		lst = lst->next;
	}
	app->gui.animated_frames = 0;
	app->sdl->needs_render = true;
}