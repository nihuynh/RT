/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animate.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 13:05:07 by sklepper          #+#    #+#             */
/*   Updated: 2019/06/10 21:48:07 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtstruct.h"
#include "rt.h"
#include "animate.h"
#include "librt.h"

void	animate_branch(void *res)
{
	t_anim	*anim;

	anim = res;
	anim->anim_obj(anim);
}

void	animate(t_data *app)
{
	t_list	*lst;

	lst = app->scene.lst_anim;
	while (lst)
	{
		animate_branch(lst->content);
		lst = lst->next;
	}
	app->sdl->needs_render = true;
}

void	anim_translate(t_anim *anim)
{
	t_translate	*translate;
	t_vec3		result;

	translate = anim->res;
	result = translate->dir;
	vec3_scalar(&result, translate->speed);
	vec3_add(anim->pos, anim->pos, &result);
}
