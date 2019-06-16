/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim_set.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 17:36:18 by sklepper          #+#    #+#             */
/*   Updated: 2019/06/16 03:41:45 by sklepper         ###   ########.fr       */
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
	anim->export = &export_translate;
	anim->parse = &parse_translate;
}

static inline void
	anim_set_orbit(t_anim *anim)
{
	t_orbit	*orbit;

	if (!(orbit = malloc(sizeof(t_orbit))))
		ft_error(__func__, __LINE__);
	ft_bzero(orbit, sizeof(t_orbit));
	anim->res = orbit;
	anim->anim_obj = &anim_orbit;
	anim->ui_anim = &ui_orbit;
	anim->export = &export_orbit;
	anim->parse = &parse_orbit;

}

static inline void
	anim_set_rotate(t_anim *anim)
{
	t_rotate	*rotate;

	if (!(rotate = malloc(sizeof(t_rotate))))
		ft_error(__func__, __LINE__);
	ft_bzero(rotate, sizeof(t_rotate));
	anim->res = rotate;
	anim->anim_obj = &anim_rotate;
	anim->ui_anim = &ui_rotate;
	anim->export = &export_rotate;
	anim->parse = &parse_rotate;
}

void
	anim_set(t_anim *anim, int type)
{
	if (anim->type == type)
		return ;
	anim_free(anim);
	if (type == 0)
		ft_bzero(anim, sizeof(t_anim));
	else if (type == 1)
		anim_set_translate(anim);
	else if (type == 2)
		anim_set_orbit(anim);
	else if (type == 3)
		anim_set_rotate(anim);
	anim->type = type;
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
		*anim->obj->pos = anim->origin;
		if (anim->obj->n)
		{
			*anim->obj->x = anim->x;
			*anim->obj->n = anim->n;
			*anim->obj->z = anim->z;
		}
		lst = lst->next;
	}
	app->gui.animated_frames = 0;
	app->sdl->needs_render = true;
}
