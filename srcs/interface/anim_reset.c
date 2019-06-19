/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim_reset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 04:41:15 by sklepper          #+#    #+#             */
/*   Updated: 2019/06/19 05:01:18 by sklepper         ###   ########.fr       */
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

static inline void
	anim_reset_extend(t_list *lst)
{
	t_anim	*anim;

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
}

void
	anim_reset(t_data *app)
{
	if (app->cam.anim)
		anim_reset_cam(app->cam.anim);
	if (app->scene.lst_anim)
		anim_reset_extend(app->scene.lst_anim);
	if (app->scene.lst_anim_light)
		anim_reset_extend(app->scene.lst_anim_light);
	app->gui.animated_frames = 0;
	app->sdl->needs_render = true;
}
