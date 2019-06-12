/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animate.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklepper <sklepper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 13:05:07 by sklepper          #+#    #+#             */
/*   Updated: 2019/06/12 01:34:11 by sklepper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtstruct.h"
#include "rt.h"
#include "animate.h"
#include "librt.h"
#include "config.h"
#include "librt.h"

void	animate_branch(void *res)
{
	t_anim	*anim;

	anim = res;
	if (anim->anim_obj)
		anim->anim_obj(anim);
	if (anim->next)
		animate_branch(anim->next);
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
	app->gui.animated_frames += 1;
	app->sdl->sub_sample = 1;
	app->sdl->partial_render = false;
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

void	anim_orbit(t_anim *anim)
{
	t_orbit		*orbit;
	t_vec3		vec;
	t_matrix	mat;
	t_pt3		*center;

	orbit = anim->res;
	center = get_pos(orbit->obj_center);
	vec3_sub(&vec, anim->pos, center);
	mat = mat_orbit(orbit->axis, orbit->deg);
	apply_matrix(&vec, &mat);
	vec3_add(anim->pos, center, &vec);
}
