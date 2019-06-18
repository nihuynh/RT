/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim_reset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 04:41:15 by sklepper          #+#    #+#             */
/*   Updated: 2019/06/18 04:44:21 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "animate.h"
#include "t_data.h"
#include "ftlist.h"

static inline void
	anim_reset_cam(void *res)
{
	t_anim	*anim;

	anim = res;
	*anim->pos = anim->origin;
	*anim->n = anim->n_save;
}

void
	anim_reset(t_data *app)
{
	t_list	*lst;
	t_anim	*anim;

	lst = app->scene.lst_anim;
	if (app->cam.anim)
		anim_reset_cam(app->cam.anim);
	while (lst)
	{
		anim = lst->content;
		*anim->pos = anim->origin;
		if (anim->x)
			*anim->x = anim->x_save;
		if (anim->n)
			*anim->n = anim->n_save;
		if (anim->z)
			*anim->z = anim->z_save;
		lst = lst->next;
	}
	app->gui.animated_frames = 0;
	app->sdl->needs_render = true;
}
